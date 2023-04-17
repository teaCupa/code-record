//
// Created by teagm on 2023/4/15.
//

#include "ch12.h"
#include <sstream>

using namespace std;

TextQuery::TextQuery(std::ifstream& is)   /** shared_ptr :file(new vector<string>) */
{
    string line;
    while(getline(is,line)){
        file.push_back(line);
        unsigned lineno = file.size();
        istringstream ss(line);
        string word;
        while(ss >> word){
            auto& p = wm[word];    //wm[word]: 将单词添加到wm中
            if(!p){
                p.reset(new set<unsigned>);
            }
            p->insert(lineno);
        }
    }
}

QueryResult TextQuery::query(string &s) {
    std::shared_ptr<std::set<unsigned> > nodata(new std::set<unsigned>);
    // 使用find而不是下标运算符来查找单词，避免将单词添加到wm中
//    auto& p=wm[s]; xxxxxxxx
    auto loc=wm.find(s);
    if(loc == wm.end())
        return QueryResult(s,nodata);
    return QueryResult(s,loc->second);
}

std::ostream& print(std::ostream& os,const QueryResult& qr){
    os << qr.query_word << " occurs times: " << qr.linenos_->size() << endl;
    for(auto& e: *qr.linenos_){
        os << e << " ";
    }
    return os;
}
