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
    print_type(x);  //x: int&  ,   int&&  ? 总是左值？对比forward<T>(x)
    cout << "decltype(x):\t";
    print_type<decltype(x)>();
    cout << "forward(x):\t";
    print_type(forward<T>(x));   //forward完美转发，左值转左值，右值转右值
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

## forward完美转发
std::forward的正确运作的前提，是引用折叠机制，为``T &&``类型的万能引用中的模板参数T赋了一个恰到好处的值。我们用T去指明std::forward的模板参数，从而使得std::forward返回的是正确的类型
```cpp
 /**
   *  @brief  Forward an lvalue.
   *  @return The parameter cast to the specified type.
   *
   *  This function is used to implement "perfect forwarding".
   */
  template<typename _Tp>
    constexpr _Tp&&
    forward(typename std::remove_reference<_Tp>::type& __t) noexcept
    { return static_cast<_Tp&&>(__t); }

 /**
   *  @brief  Forward an rvalue.
   *  @return The parameter cast to the specified type.
   *
   *  This function is used to implement "perfect forwarding".
   */
  template<typename _Tp>
    constexpr _Tp&&
    forward(typename std::remove_reference<_Tp>::type&& __t) noexcept
    {
      static_assert(!std::is_lvalue_reference<_Tp>::value, "template argument"
		    " substituting _Tp is an lvalue reference type");
      return static_cast<_Tp&&>(__t);
    }
```
从move.h源码中看到_Tp&& forward(int& _t)和 _Tp&& forward(int&& _t)分别匹配参数为左值和右值的forward函数调用。参数_t为左值就进行forward返回左值类型，参数_t为右值就forward返回右值类型。

## forward作用：
看上述``print_type(x)``和``print_type(forward<T>(x))``运行结果对比
```cpp
template<typename T>
void test(T&& x) {
    .......
    print_type(x);  //x: int&  ,   int&&  ? 总是左值？对比 forward<T>(x)
    ......
    print_type(forward<T>(x));   //forward完美转发，左值转左值，右值转右值
    .....
}
```
