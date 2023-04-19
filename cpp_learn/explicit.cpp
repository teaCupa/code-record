//
// Created by teagm on 2023/4/18.
//

#include<iostream>

class MyClass{
public:
    //if explicit, definately require params type is int,not allow
    // fun(3) cast to fun(MyClass(3)), cause ERROR: could not convert ‘3’ from ‘int’ to ‘MyClass’
     explicit MyClass(int i){std::cout<<"MyClass(int): "<<i <<std::endl;};
//    MyClass(int i){std::cout<<"MyClass(int): "<<i <<std::endl;};

    //MyClass(int i) 优先级 高于 MyClass(char c), fun('a') 会cast to fun(97) 以优先匹配 MyClass(int i){}
    MyClass(char c) { std::cout << "explicit MyClass(char): " << c << std::endl; }

    char ch;
    int i=1;
};

void fun(MyClass cla){}

int main()
{
//    fun(3);
    fun('a'); //优先 cast to fun(97) 去匹配
}
