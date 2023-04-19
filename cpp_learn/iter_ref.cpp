//
// Created by teagm on 2023/4/18.
//

#include<iostream>
#include<vector>

struct foo{
    int i;
    foo(int i_):i(i_){
        std::cout<<"foo:"<< i <<std::endl;
    }
};

int main()
{
    std::vector<foo> vecs;
    vecs.emplace_back(1);
    vecs.emplace_back(2);

    //reference promise update sync everywhere
    std::vector<foo>& v2 = vecs;
    //copy
    //std::vector<foo>v2 = vecs;

    std::vector<foo>::iterator it;
    for(it=v2.begin(); it!=v2.end();it++){
        it->i=3;
    }

    for(it=vecs.begin(); it!=vecs.end();it++){
        std::cout<< it->i <<std::endl;
    }
}


