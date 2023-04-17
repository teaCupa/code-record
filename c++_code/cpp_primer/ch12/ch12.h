//
// Created by teagm on 2023/4/15.
//

#ifndef CPP_PRIMER_CH12_H
#define CPP_PRIMER_CH12_H

#include <map>
#include <set>
#include <string>
#include <fstream>
#include <utility>
#include <vector>
#include <memory>   //shared_ptr

class QueryResult;

class TextQuery {
public:
    explicit TextQuery(std::ifstream&);

    QueryResult query(std::string& s);
private:
    std::vector<std::string> file;     ///默认构造,  用智能指针的优势是堆空间比栈大
    // 每个单词到它所在的行号的集合的映射
    std::map<std::string,std::shared_ptr<std::set<unsigned>> > wm;
};

class QueryResult{
public:
    friend std::ostream& print(std::ostream&,const QueryResult&);

    QueryResult(std::string s,std::shared_ptr<std::set<unsigned>> linenos)
         : query_word(std::move(s)), linenos_(std::move(linenos)) { }

private:
    std::string query_word;
    std::shared_ptr<std::set<unsigned> > linenos_;
};

std::ostream& print(std::ostream&,const QueryResult&);

#endif //CPP_PRIMER_CH12_H
