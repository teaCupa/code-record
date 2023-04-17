//
// Created by teagm on 2023/4/15.
// 作用域与函数模版匹配

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
