//
// Created by teagm on 2023/4/18.
//

#include<iostream>
using namespace std;

/**
 * ### 谈谈8进制number-type字符串显示
 *  一个32位的1可以用"\000\001\000"编码显示，涉及内存缩写0（for32: 16位对齐）
 *   实际内存为"\000\001\000\000"(小端存放)
 * 又如16位的16放入字符串显示为"\020",实际内存为"\020\000"
 * 又如8位的1<<7放入字符串显示为"\200",实际内存为"\200"
 * because a number-type string "01" have no difference with "1" for showing
 *    to reader
 */


inline void PutFixed32(std::string* dst, uint32_t value) {
    dst->append(const_cast<const char*>(reinterpret_cast<char*>(&value)),
                sizeof(value));
}

inline void PutFixed16(std::string* dst, uint16_t value) {
    dst->append(const_cast<const char*>(reinterpret_cast<char*>(&value)),
                sizeof(value));
}

inline void PutFixed8(std::string* dst, uint8_t value) {
    dst->append(const_cast<const char*>(reinterpret_cast<char*>(&value)),
                sizeof(value));
}

int main()
{
    string dst;
//   uint32_t value=1<<8;
//   PutFixed32(&dst,value);
//   PutFixed32(&dst,value);

    uint16_t val=1<<4;
    PutFixed16(&dst,val);
    PutFixed16(&dst,val);

//     uint8_t v=1<<7;
//     PutFixed8(&dst,v);
//     PutFixed8(&dst,v);

    cout<<&dst<<endl;
    cout<<dst<<endl;
    cout<<dst.size();

}
