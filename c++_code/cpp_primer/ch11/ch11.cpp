//
// Created by teagm on 2023/4/14.
// 输入单词计数，使用map

#include <iostream>
#include <map>
#include <string>
#include <algorithm>  //std::remove_if

using std::string;

void word_count(std::map<string,int>& m){
    string word;
    while(std::cin >> word && word!="quit"){
        for(auto& c : word)
            c = toupper(c);
        //ispunct() 函数用来检测一个字符是否为标点符号或特殊字符
        word.erase(std::remove_if(word.begin(),word.end(),ispunct)
                  ,word.end());
        ++m[word];
    }
    for(auto& e:m) std::cout << e.first <<" "<<e.second <<std::endl;
}

int main(){
    std::map<string,int> m;
//    m["hello"];  //将"hello"添加到m中
//    std::cout <<m.size();  //1
    word_count(m);
}

