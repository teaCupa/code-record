//
// Created by teagm on 2023/4/18.
//

#include<iostream>
#include<cstring>   //memcpy

/**
 *   understand function:
 *           void *memcpy(void *dest, const void *src, size_t n);
 *   man memcpy:
 *          The  memcpy()  function  copies  n bytes from memory area src to memory
            area dest.  The memory areas must not overlap (内存重叠)
 */

bool uint32tox(const uint32_t input, char *str);

bool uint32tox(const uint32_t input, char *str)
{
    uint32_t val = input;
    int16_t  i;
    uint16_t  j = 0;

    if (str == NULL) return false;

    for (i = 28; i >= 0; i -= 4) {
        uint8_t sval = (val >> i) & 0x0F;
        str[j++] = (sval < 10u) ? sval + '0' : sval - 10 + 'A';
    }
    str[j]='\0';
    return true;
}

void fun(const char* ptr){  //0x7fffffffdf98 "rld!"
    char result;
    uint32_t addr_ptr;
    char hexAddr[8+1];   //note , char* hexAddr is wrong!!!

    char str[10];
    char *chs=(char*)"aaa";
    strcpy(str,chs);
    std::cout << "str: "<< str << std::endl;
    //gdb:  x /4b[x] ptr
    memcpy(&result,ptr,strlen(ptr)+1);  //strlen(ptr)+1 考虑'\0',  copy the bytes from where ptr pointing to &result
    std::cout<<&ptr<<std::endl;
    std::cout<<"&ptr-1:"<<&ptr-1<<std::endl;

    uint32_t value=0x11111111;
    memcpy(&addr_ptr,&value,sizeof(addr_ptr));
    std::cout<<"addr_ptr: hex "<< std::hex << addr_ptr<<std::endl;

    uint32tox(addr_ptr,hexAddr);

    std::cout<<"hexAddr:0x"<< hexAddr<<std::endl;
//    std::cout<< "result:"<< reinterpret_cast<char*>(&result) << std::endl;
    std::cout<< "result:"<< &result << std::endl;
}

int main()
{
    std::string rep ="hello world!";
    std::cout << rep.size() <<std::endl; //12
    fun(rep.data()+8);   //0x7fffffffdf90 "hello world!"
}
