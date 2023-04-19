//
// Created by teagm on 2023/4/18.
//

/** 该程序在linux下是ok的，运行结果如下：  （但在Windows下是运行失败的
b:虚函数表的地址：0x7ffdc2fa1950
b:虚函数表的第0个函数地址：0x55889663cd40
Base f() .
b:虚函数表的第1个函数地址：0x55889663cd48
Base print() .
b1:虚函数表的地址：0x7ffdc2fa1958
b1:虚函数表的第0个函数地址：0x55889663cd40
Base f() .
b1:虚函数表的第1个函数地址：0x55889663cd48
Base print() .
d:虚函数表的地址：0x7ffdc2fa1960
d:虚函数表的第0个函数地址：0x55889663cd20
Base f() .
d:虚函数表的第1个函数地址：0x55889663cd28
Derive print() .
*/

#include <iostream>
using namespace std;

class Base
{
public:
    virtual void f();
    virtual void print();
};

void Base::f() { cout << "Base f() ." << endl; }
void Base::print() { cout << "Base print() ." << endl; }

class Derive : public Base
{
public:
    void f1();
    virtual void print();
};
void Derive::f1() { cout << "Derive f1() ." << endl; }
void Derive::print() { cout << "Derive print() ." << endl; }

typedef void (*Fun)();

int main()
{
    Base b;
    // cout << sizeof(char*)<<" "<<sizeof(unsigned long*)<< endl;
    cout << "b:虚函数表的地址：" << (int *)(&b) << endl;
    for (int i = 0; i < 2; i++)
    {
        unsigned long *vtbl = (unsigned long *)(*(unsigned long *)&b) + i;  //*(unsigned long *)&b =b
        cout << "b:虚函数表的第" << i << "个函数地址：" << vtbl << endl;
        Fun pFun = (Fun) * (vtbl);
        pFun();
    }
    Base b1;
    cout << "b1:虚函数表的地址：" << (int *)(&b1) << endl;
    for (int i = 0; i < 2; i++)
    {
        unsigned long *vtbl = (unsigned long *)(*(unsigned long *)&b1) + i;
        cout << "b1:虚函数表的第" << i << "个函数地址：" << vtbl << endl;
        Fun pFun = (Fun) * (vtbl);
        pFun();
    }
    Derive d;
    cout << "d:虚函数表的地址：" << (int *)(&d) << endl;
    for (int i = 0; i < 2; i++)
    {
        unsigned long *vtbl = (unsigned long *)(*(unsigned long *)&d) + i;
        cout << "d:虚函数表的第" << i << "个函数地址：" << vtbl << endl;
        Fun pFun = (Fun) * (vtbl);
        pFun();
    }
    return 0;
}
