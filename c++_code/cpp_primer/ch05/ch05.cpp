//
// Created by teagm on 2023/4/14.
// 语句

#include <iostream>
using namespace std;

int divide(int a,int b){
    if(b==0)
        throw runtime_error("b can not be 0!");
    else
        return a/b;
}

int main(){
    int a=1,b=0,res;
    try{
        res = divide(a,b);
        cout << res << endl;
    } catch (runtime_error& err) {
        cout << err.what() << endl;
    }
}




