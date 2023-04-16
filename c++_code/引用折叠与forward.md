```cpp
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

//#include <type_traits>
using std::move;
using std::forward;
using std::is_lvalue_reference;
using std::is_rvalue_reference;
using std::is_reference;

template<typename T> void print_type(T&& t) { cout << "Rvalue\n"; }
template<typename T> void print_type(T& t) { cout << "Lvalue\n"; }
template<typename T> void print_type(const T&) { cout << "Const Lvalue\n"; }

template<typename T>
inline void print_type() {
    if (is_lvalue_reference<T>::value)
        cout << "is_lvalue_reference\n";
    else if (is_rvalue_reference<T>::value)
        cout << "is_rvalue_reference\n";
    else if (is_reference<T>::value)
        cout << "is_reference\n";
    else cout << "other type\n";
}

template<typename T>
void test(T&& x) {
    cout << "---Test start:\n";
    cout << "T:\t";
    print_type<T>();    //if type(x) is int& => T is int&,   if type(x) is int&& => T is int
    cout << "T&&:\t";
    print_type<T&&>(); //int& && => int&  ,        int &&  => int&
    cout << "x:\t";
    print_type(x);  //x: int&  ,   int&&  ? 总是左值
    cout << "decltype(x):\t";
    print_type<decltype(x)>();
    cout << "forward(x):\t";
    print_type(forward<T&&>(x));   //forward转发
    cout << "static_cast<decltype(x)>(x):\t";
    print_type(static_cast<decltype(x)>(x));
    cout << "---Test end.\n" << endl;
}

int main() {

    int x = 114514;

    print_type(x);      //x类型为int&
    print_type(move(x)); //move(x)类型为int&&
    print_type(1919810); //1919810类型为int&&
    cout << endl;

    test(x);
    test(move(x));

    return 0;
}
```
template<typename T>
void test(T&& x) {...}

通过传入的x类型以及引用折叠规则判断T的类型

- type(T) + && => type(x)
- T& && => T&
- T  && => T&&

如果x类型是int&, 反推出T类型是int&
；如果x类型是int&&, 反推出T类型是int