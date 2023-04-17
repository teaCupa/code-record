//
// Created by teagm on 2023/4/14.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

//去重
void elimdups(std::vector<std::string>& v){
    std::sort(v.begin(),v.end());
    auto new_end=std::unique(v.begin(),v.end());  //重复的元素被后续位置的新元素替换
    v.erase(new_end,v.end());   //该区间大小即重复的元素数量，需要回收
}

//重要的事物
void biggies(std::vector<std::string>& v,size_t sz){
    using std::string;
    elimdups(v);

    // sort by size, but maintain alphabetical order for same size.
    //按字符串大小排序，相同大小的字符串按字母序排序
    std::stable_sort(v.begin(),v.end(),[](string const& lhs,string const& rhs){
          return lhs.size()<rhs.size();
    });

    // get an iterator to the first one whose size() is >= sz
    auto wc = std::find_if(v.begin(),v.end(),[sz](string const& s){
         return s.size()>=sz;
    });

    // print the biggies
    std::for_each(wc,v.end(),[](const string& s){
        std::cout << s << " ";
    });
}

int main(){
    std::vector<std::string> v{
        "1234","1234","1234","hi~", "alan", "alan", "cp"
    };
    biggies(v,3);
}
