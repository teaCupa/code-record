# 博客
https://www.cnblogs.com/gyan083/p/16339017.html

# using std::swap 与 C++ ADL 机制
## 问题引入

STL std::pair 中的 swap 函数是这样实现的：（来自 stl_pair.h，仅展示部分源代码）
```cpp
namespace std
{
  template<typename _T1, typename _T2>
    struct pair
    {
      _T1 first;                 ///< The first member
      _T2 second;                ///< The second member

      /// Swap the first members and then the second members.
      void swap(pair& __p)
      {
	using std::swap;
	swap(first, __p.first);
	swap(second, __p.second);
      }
    }
}
```
显然这里是想对 pair 中的两个元素依次调用我们熟知的 std::swap 函数。那为什么要提前写一句 ``using std::swap;`` 而不是直接使用 std::swap(first, __p.first); 的写法呢？

其实这里 STL 选择的写法是必须的。

ADL 机制的介绍
来看一个例子：
```cpp
#include <iostream>  // for std::cout
int main() {
    std::cout << "Hello World!\n";
    return 0;
}
```
一段很平凡的代码。

但仔细想想，std::ostream 重载的 << 流运算符是定义在标准命名空间 std 中的，也就是说按上面的写法，本该是因为找不到流运算符的定义而编译失败的，似乎下面这种写法才是正确的：
```cpp
#include <iostream>  // for std::cout
int main() {
    std::operator<<(std::cout, "Hello World!\n");
    return 0;
}
```
即，使用 作用域解析运算符 ::。

那么，第一种写法为什么可以？

这是因为，第一种写法中，编译器发现流运算符的左参数 std::cout 是隶属于命名空间 std 中的，同时又因为编译器没有在全局中找到流运算符的定义，于是编译器就会把搜查范围扩展到命名空间 std ，继续搜索流运算符的定义，当然就成功找到了。也就是说，下面这种写法也是可以的：
```cpp
#include <iostream>  // for std::cout
int main() {
    operator<<(std::cout, "Hello World!\n");
    return 0;
}
```
不使用 作用域解析运算符。

这种根据函数参数所属作用域，来扩展所调用的函数的查找范围的机制，称为参数依赖查找（Argument-Dependent Lookup，ADL）。ADL 机制可以帮助提升 C++ namespace 场景中模板的适应性，同时简化了我们的代码编写。

这时候再来看std::pair 中的 swap 函数，你就会知道，如果用 std::swap(first, __p.first); 的写法，swap 函数就被限定在了命名空间 std 中；而如果使用 STL 中 using std::swap; 的写法，则会触发 ADL 机制，编译器会在全局范围（包括通过 using 引入的 std 命名空间）内查找 swap 函数。
## 为什么要触发 ADL 机制？
如果你使用的是一般的数据类型，那么这里是否触发 ADL 机制都毫无区别。

这里的“一般”指诸如以下几种：
```cpp
#include <utility> for std::pair
std::pair<int, int*> pii;
std::pair<long long, double> pld;
std::pair<char, unsigned short> pcs;
```
等等。

但如果是用户定义的某些复杂的类、结构体呢？

std::swap 会把这些数据类型中的所有数据逐个复制、拷贝三次，进行交换操作，同时还会进行构造、析构等操作，这就会造成许多时间上和空间上的浪费。

通常，对于数据量大的类，我们会采取一些特殊方法来实现交换操作。特别实现的交换操作可以节约很多空间和时间。但是，std::swap 并不知道它可以调用我们已实现的交换操作，所以我们每次使用不同的类时，就必须调用不同的专门的函数。这显然是不符合模板化的“通用性”的精神的。

为了解决这个问题，我们可以针对自己的类重载 swap 函数，但不必在标准命名空间 std 中。由于 std::pair 中的 swap 触发了 ADL，编译器就会同时搜索到 std::swap 和我们的 swap。因为一系列重载函数的参数匹配原则，编译器就会优先调用我们特化过的 swap，而不是使用了模板的 std::swap。

同样的原理，除了 std::pair 中的 swap 函数，STL 也在许多其他地方使用了 ADL 机制进行相应的优化。

## 验证 ADL 的触发
我写了一个短程序来模拟验证 STL 的写法触发了 ADL 机制，并实现了上中所说的我们想要的效果。

程序的大体思路：

在命名空间中，定义一个模板函数 fun，模拟 std::swap。

全局中，定义一个特殊类型 myType。

定义针对 myType 的函数 fun 的特化版本。

定义模板类 test，模拟 std::pair。

在 test 中定义函数 fun1 和 fun2，分别用两种写法调用 fun 函数。

主函数中，依次调用 fun1 和 fun2，输出查看两种写法实际调用的是哪个版本的 fun 函数。

程序如下：
```cpp
#include <iostream>  // for std::cout

namespace _std
{
	/// 模拟 std 中的模板函数
  template<typename Tp>
	void fun(const Tp&) {
		std::cout << "Call fun() in _std.\n";
	}
}

/// 一个特殊的类型
struct myType { };

/// 对 myType 进行特化
void fun(const myType&) {
	std::cout << "Call fun() specially for myType.\n";
}

template<typename T>
struct test {

	T x;
  /// 不使用 using 技法
	void fun1() {
		std::cout << "fun1, without 'using':\t";
		_std::fun(x);
	}

  /// 使用 using 技法
	void fun2() {
		std::cout << "fun2, with 'using':\t";
		using _std::fun;    ///注释它，会报错
		fun(x);
	}
};

int main()
{
	test<int> t_int;       /// 用于对照
	test<myType> t_myType;

	std::cout << "t_int:\n";
	t_int.fun1();
	t_int.fun2();

	std::cout << "\nt_myType:\n";
	t_myType.fun1();
	t_myType.fun2();

	return 0;
}
```
运行结果
```cpp
t_int:
fun1, without 'using':  Call fun() in _std.
fun2, with 'using':     Call fun() in _std.

t_myType:
fun1, without 'using':  Call fun() in _std.
fun2, with 'using':     Call fun() specially for myType.
```
不难发现，STL 的写法是十分有效的。

我们自己进行模板化编程时，也应当注意使用 ADL 进行优化。