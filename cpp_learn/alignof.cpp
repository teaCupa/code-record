//
// Created by teagm on 2023/4/18.
//

#include <iostream>

struct Foo {
    int   i;
    float f;
    char  c;
};

// Note: `alignas(alignof(long double))` below can be simplified to simply
// `alignas(long double)` if desired.
struct alignas(alignof(long double)) Foo2 {
    // put your definition here
};

struct Empty {};

struct alignas(64) Empty64 {};

int main()
{

    std::cout << "Alignment of \n"
                 "- char             : " << alignof(char)    << "\n"
                 "- pointer          : " << alignof(int*)    << "\n"
                 "- class Foo        : " << alignof(Foo)     << "\n"
                 "- double           : " << alignof(double)  << "\n"
                 "- long double      : " << alignof(long double)    << "\n"
                 "- class Foo2       : " << alignof(Foo2)    << "\n"
                 "- empty class      : " << alignof(Empty)   << "\n"
                 "- alignas(64) Empty: " << alignof(Empty64) << "\n"
                 "- sizeof(empty class)    : " << sizeof(Empty) << "\n"
                 "- sizeof(alignas(64) Empty)    : " << sizeof(Empty64) << "\n";
}
