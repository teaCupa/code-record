# 保存db数据到磁盘（序列化，二进制）

- 函数 static int rdbSave(char *filename)

## redis为节省空间，将数字进行变长编码，共4种

- 00|000000   数字小于6bit，用1字节保存
- 01|000000 00000000  数字小于14bit，用2字节保存
- 10|000000 [32bit]  当数字大于14bit时，用5字节保存变长数字
- 11|000000  ，11开头的后6位用于指定特殊对象编码

```c
static int rdbSaveLen(FILE *fp, uint32_t len) {
    unsigned char buf[2];

    if (len < (1<<6)) {
        /* Save a 6 bit len */
        buf[0] = (len&0xFF)|(REDIS_RDB_6BITLEN<<6);       //00[低6位len]
        if (fwrite(buf,1,1,fp) == 0) return -1;           //写1个1字节
    } else if (len < (1<<14)) {
        /* Save a 14 bit len */
        buf[0] = ((len>>8)&0xFF)|(REDIS_RDB_14BITLEN<<6);    //高6位 01[高6位]
        buf[1] = len&0xFF;                                   //低8位 [ 低8位 ]
        if (fwrite(buf,2,1,fp) == 0) return -1;              //写1个2字节
    } else {
        /* Save a 32 bit len */
        buf[0] = (REDIS_RDB_32BITLEN<<6);                  //10000000
        if (fwrite(buf,1,1,fp) == 0) return -1;
        len = htonl(len);                                 //转网络大端序
        if (fwrite(&len,4,1,fp) == 0) return -1;
    }
    return 0;
}
```

## rdbsave写入磁盘内容

1）**写入**"REDIS0001"    (Redis版本+版本号0001)

2）遍历数据库   for j in [0-15]

- **写入**REDIS_SELECTDB+数据库编号*j*

     - 遍历数据库*j*的哈希表, 获取键key,值对象valObj,过期时间expiretime

       > 写入REDIS_EXPIRETIME+expiretime
       
       > 写入值对象的类型+key字符串
       
       > 写入值对象（string类型 或 List 或 Set)

- **写入**REDIS_EOF

写入key字符串`rdbSaveStringObject`，写入key的长度和具体key内容

- rdbTryIntegerEncoding

  1. 如果key是整数，比如"9876","-100"等，根据其大小只需要2,3或5字节存储

  2. key不是整数，并且长度>20,采用`rdbSaveLzfStringObject`压缩。否则直接写入

```c
static int rdbSaveStringObject(FILE *fp, robj *obj) {
    size_t len = sdslen(obj->ptr);
    int enclen;

    /* Try integer encoding */
    if (len <= 11) {
        unsigned char buf[5];
        if ((enclen = rdbTryIntegerEncoding(obj->ptr,buf)) > 0) {
            if (fwrite(buf,enclen,1,fp) == 0) return -1;
            return 0;
        }
    }

    /* Try LZF compression - under 20 bytes it's unable to compress even
     * aaaaaaaaaaaaaaaaaa so skip it */
    if (1 && len > 20) {
        int retval;

        retval = rdbSaveLzfStringObject(fp,obj);
        if (retval == -1) return -1;
        if (retval > 0) return 0;
        /* retval == 0 means data can't be compressed, save the old way */
    }

    /* Store verbatim */
    if (rdbSaveLen(fp,len) == -1) return -1;
    if (len && fwrite(obj->ptr,len,1,fp) == 0) return -1;
    return 0;
}
```

- 字符串压缩 rdbSaveLzfStringObject

  压缩至少4字节。写入**11|000011**，comprlen，sdslen(obj->ptr)，压缩后的字符串内容out。
  
  对于1字节、2字节、4字节的可转为数字的字符串对应写入11|000000、11|000001、11|000010

```c
static int rdbSaveLzfStringObject(FILE *fp, robj *obj) {
    unsigned int comprlen, outlen;
    unsigned char byte;
    void *out;

    /* We require at least four bytes compression for this to be worth it */
    outlen = sdslen(obj->ptr)-4;
    if (outlen <= 0) return 0;
    if ((out = zmalloc(outlen+1)) == NULL) return 0;
    comprlen = lzf_compress(obj->ptr, sdslen(obj->ptr), out, outlen);
    if (comprlen == 0) {
        zfree(out);
        return 0;
    }
    /* Data compressed! Let's save it on disk */
    byte = (REDIS_RDB_ENCVAL<<6)|REDIS_RDB_ENC_LZF;
    if (fwrite(&byte,1,1,fp) == 0) goto writeerr;
    if (rdbSaveLen(fp,comprlen) == -1) goto writeerr;
    if (rdbSaveLen(fp,sdslen(obj->ptr)) == -1) goto writeerr;
    if (fwrite(out,comprlen,1,fp) == 0) goto writeerr;
    zfree(out);
    return comprlen;

writeerr:
    zfree(out);
    return -1;
}
```

# 从磁盘加载数据到db

- 函数 static int rdbLoad(char *filename)

  以读字符串为例。

```c
static robj *rdbLoadStringObject(FILE*fp, int rdbver) {
    int isencoded;
    uint32_t len;
    sds val;

    len = rdbLoadLen(fp,rdbver,&isencoded);
    if (isencoded) {
        switch(len) {
        case REDIS_RDB_ENC_INT8:
        case REDIS_RDB_ENC_INT16:
        case REDIS_RDB_ENC_INT32:
            return tryObjectSharing(rdbLoadIntegerObject(fp,len));
        case REDIS_RDB_ENC_LZF:
            return tryObjectSharing(rdbLoadLzfStringObject(fp,rdbver)); //使用共享池哈希表，共享robj对象
        default:                                                        //基于引用计数的原理
            assert(0!=0);
        }
    }

    if (len == REDIS_RDB_LENERR) return NULL;
    val = sdsnewlen(NULL,len);
    if (len && fread(val,len,1,fp) == 0) {
        sdsfree(val);
        return NULL;
    }
    return tryObjectSharing(createObject(REDIS_STRING,val));
}
```

tryObjectSharing考虑到一个字符串会被多次使用，使用sharingpool哈希表进行基于引用计数的共享

```c
dictAdd(server.sharingpool,o,(void*)1)    //向sharingpool存储key为o,值为1的共享键，o的类型为Redis字符串
```

- 函数rdbLoadLen对应rdbSaveLen

```c
/* isencoded is set to 1 if the readed length is not actually a length but
 * an "encoding type", check the above comments for more info */
static uint32_t rdbLoadLen(FILE *fp, int rdbver, int *isencoded) {
    unsigned char buf[2];
    uint32_t len;

    if (isencoded) *isencoded = 0;
    if (rdbver == 0) {
        if (fread(&len,4,1,fp) == 0) return REDIS_RDB_LENERR;
        return ntohl(len);
    } else {
        int type;

        if (fread(buf,1,1,fp) == 0) return REDIS_RDB_LENERR;
        type = (buf[0]&0xC0)>>6;
        if (type == REDIS_RDB_6BITLEN) {
            /* Read a 6 bit len */
            return buf[0]&0x3F;
        } else if (type == REDIS_RDB_ENCVAL) {
            /* Read a 6 bit len encoding type */
            if (isencoded) *isencoded = 1;
            return buf[0]&0x3F;
        } else if (type == REDIS_RDB_14BITLEN) {
            /* Read a 14 bit len */
            if (fread(buf+1,1,1,fp) == 0) return REDIS_RDB_LENERR;
            return ((buf[0]&0x3F)<<8)|buf[1];
        } else {
            /* Read a 32 bit len */
            if (fread(&len,4,1,fp) == 0) return REDIS_RDB_LENERR;
            return ntohl(len);     //网络序转主机序
        }
    }
}
```