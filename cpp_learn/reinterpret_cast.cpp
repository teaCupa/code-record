//
// Created by teagm on 2023/4/18.
//

#include <cassert>   //assert
#include <iostream>

int f() { return 42; }

int main()
{
    int i = 7;

    // 指针到整数并转回
    std::uintptr_t v1 = reinterpret_cast<std::uintptr_t>(&i); // static_cast 为错误
    std::cout << "The value of &i is 0x" << std::hex << v1 << '\n';
    int* p1 = reinterpret_cast<int*>(v1);
    std::cout << p1 <<" "<<*p1<<'\n';
    assert(p1 == &i);

    // 到另一函数指针并转回
    void(*fp1)() = reinterpret_cast<void(*)()>(f);
    // fp1(); 未定义行为
    int(*fp2)() = reinterpret_cast<int(*)()>(fp1);
    std::cout << std::dec << fp2() << '\n'; // 安全

    // 通过指针的类型别名化
    char* p2 = reinterpret_cast<char*>(&i);
    if(p2[0] == '\007')
        std::cout << "This system is little-endian\n";
    else
        std::cout << "This system is big-endian\n";

    // 通过引用的类型别名化
    i = 1<<31;
    unsigned int& j= reinterpret_cast<unsigned int&>(i);
    std::cout << i << '\n';
    std::cout << "j= " << j << '\n';

    [[maybe_unused]] const int &const_iref = i;
    // int &iref = reinterpret_cast<int&>(const_iref); // 编译错误——不能去除 const
    int &iref = const_cast<int&>(const_iref);
}