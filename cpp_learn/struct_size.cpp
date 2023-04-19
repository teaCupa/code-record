//
// Created by teagm on 2023/4/18.
//

#include<iostream>
#include <cstring>

/**
 *  int --  4byte
 *  int* -- 8byte  ,or pointer --- 8byte
 */

struct Node{
    int a;
    int* b[2];   //size: int* b[2] <---> 8byte*2=16byte
    // int c;
    Node *next_[1];
};


int main(){
    Node* p =new Node();
    p->b[0]=new int(1);
    std::cout<<"sizeof(Node*): "<<sizeof(p)<<'\n';    //8
    std::cout<<"sizeof(Node): "<<sizeof(Node)<<'\n';  //32
    std::cout<<"sizeof(void*):"<<sizeof(void*)<<'\n';  //8

    Node* p2 =new Node();
    std::cout<<"sizeof(p2->a): "<<sizeof(p2->a)<<'\n';  //4
    // std::cout<<"sizeof(p2->b): "<<sizeof(p2->b)<<'\n';  //8*2=16
    std::cout<<"sizeof(p2->next_[1]): "<<sizeof(p2->next_[1])<<'\n';  //8
    //std::cout<<p2->next_[0]->a<<" "<<p2->next_[1]<<'\n';  //error! nullptr

    auto* p3 =new Node();
    p3->a=1;
    std::cout<<p3->next_[0]<<"\n";   //nullptr

}
