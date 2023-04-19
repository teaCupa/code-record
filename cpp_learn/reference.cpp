//
// Created by teagm on 2023/4/18.
//

#include<iostream>
#include <fstream>
#include<cstring>  //for strlen(s)

/**
 *  see function PutLengthPrefixedSlice(&rep_,Slice(value)),
 *      params rep_ is & refrence pass to call sub_function
 *
 *  updateSlice(&sli);  -> updateSlice(Slice* obj)
    updateSlice2(sli2); -> updateSlice2(Slice& obj)
 *
 *  learn to use
 *          std::string# append("abc",3)
 *          std::string# push_back('a')
 */


const char key[] = "key";
const char *value = "value2";

class Slice{
private:
    const char* data_;
    size_t size_;
public:
    Slice():data_(""),size_(0){}
    explicit Slice(const std::string& s):data_(s.data()),size_(s.size()){}
    explicit Slice(const char* s) : data_(s) { size_ = (s == nullptr) ? 0 : strlen(s); }

    const char* data() const { return data_; }
    size_t size() const { return size_; }
    void setSize(size_t size)  { size_=size;}
};

void updateSlice(Slice* obj){
    obj->setSize(1);
}


void updateSlice2(Slice& obj){
    obj.setSize(1);
}

char* EncodeVarint32(char* dst,uint32_t v){
    // Operate on characters as unsigneds
    unsigned char* ptr = reinterpret_cast<unsigned char*>(dst);
    static const int B = 128;
    if (v < (1 << 7)) {
        *(ptr++) = v;
    } else if (v < (1 << 14)) {
        *(ptr++) = v | B;
        *(ptr++) = v >> 7;
    } else if (v < (1 << 21)) {
        *(ptr++) = v | B;
        *(ptr++) = (v >> 7) | B;
        *(ptr++) = v >> 14;
    } else if (v < (1 << 28)) {
        *(ptr++) = v | B;
        *(ptr++) = (v >> 7) | B;
        *(ptr++) = (v >> 14) | B;
        *(ptr++) = v >> 21;
    } else {
        *(ptr++) = v | B;
        *(ptr++) = (v >> 7) | B;
        *(ptr++) = (v >> 14) | B;
        *(ptr++) = (v >> 21) | B;
        *(ptr++) = v >> 28;
    }
    return reinterpret_cast<char*>(ptr);
}

inline void PutVarint32(std::string* dst, uint32_t v){
    char buf[5];
    char* ptr = EncodeVarint32(buf, v);
    dst->append(buf,static_cast<size_t>(ptr-buf));
}

inline void PutLengthPrefixedSlice(std::string* dst, const Slice& value) {
    PutVarint32(dst, static_cast<uint32_t>(value.size()));
    dst->append(value.data(), value.size());
//   (*dst).append(value.data(), value.size());
}


int main()
{
    std::string rep_;
    rep_.push_back(static_cast<char>(1));
    // rep_.push_back(static_cast<char>(5));    //assic 5 no show when cout<<rep_
    rep_.push_back(static_cast<char>(9));  //'\t'
    rep_.push_back('a');
    rep_.append(key,strlen(key));

    // std::ifstream file("./memcpy.cc",std::ios::in);
    // if (file) {
    //     while (!file.eof()) {
    //         rep_.push_back(file.get());
    //     }
    // }
    PutLengthPrefixedSlice(&rep_,Slice(value));    //understand why refrence? rep_ in stack

    std::cout << rep_ << '\n';

    for(int i=0;i<rep_.size();i++){
        std::cout<<rep_[i]<<"\n";
    }

    Slice sli(key);
    Slice sli2(key);
    //updateSlice need refrence type(&) params, the sub-called function variable point* type to make updated pass to caller!
    updateSlice(&sli);
    updateSlice2(sli2);
    std::cout<<"slice-size:"<<sli.size()<<" "<<sli2.size()<<std::endl;

}
