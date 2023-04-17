//
// Created by teagm on 2023/4/14.
// 字符串、向量和数组

#include <iostream>
#include <string>
#include <vector>
#include <bitset>
using namespace std;

void basic_getline(){
    string line;
    while(getline(cin,line))
        cout << line << endl;
}

void basic_str(){
    string s("hello");
    cout << s.size() << " " << s.empty() <<endl;
    for(string::size_type i=0;i<s.size();++i)
        cout<<s[i];
}

void basic_vector(){
    vector<string> v;
    v.push_back("hello");
    v.push_back("world");
    for(vector<string>::iterator it=v.begin();it!=v.end();++it){
        for(auto& c : *it){
            c = toupper(c);
        }
    }
    for(auto str:v)
        cout << str << endl;
}

void basic_biteset(){
    bitset<16> bitvec1(0xffff);
    string bit_str = "11001";
    bitset<8> bitvec2(bit_str);  //从右到左读取字符串，只能是string对象，不能是字面值
    bitset<8> bitvec3(bit_str,0,3);  // 只要前三位
    cout << bitvec1 << endl
         << bitvec2 << endl
         << bitvec3 << endl
         << bitvec2.test(2) << " " << bitvec2.test(3) << endl
         << bitvec2.to_ulong() << endl;
}

int main(){
//    basic_getline();
//    basic_str();
    basic_vector();
//    basic_biteset();
}
