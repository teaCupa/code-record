//
// Created by teagm on 2023/4/14.
// 函数

#include "chapter6.h"
#include <iostream>
using namespace std;

int fact(int n){
    return n>1 ? n * fact(n-1) : 1;
}

int fact2(int n) {
    int res=1;
    while(n>1)
        res *= n--;
    return res;
}

int interactive_fact(){
    cout << "Enter a number within [1, 13) :\n";
    int n;
    std::cin>> n;
    if(n<1 || n>12)
        cout << "Out of range, please try again.\n";
    return fact2(n);
}

