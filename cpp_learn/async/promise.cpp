//
// Created by teagm on 2023/4/19.
//

#include <iostream>
#include <future>
#include <thread>

int fun(int x, std::promise<int>& p) {
    x++;
    x *= 10;
//    p.set_value(x);   //注释一下
    p.set_value(x);
    std::cout <<"fun():"<< std::this_thread::get_id() << std::endl;
    return x;
}


int main()
{
    std::promise<int> p;
    std::future<int> fu = p.get_future();        // 并将结果返回给future
    std::thread t(fun, 1, std::ref(p));
    std::cout << fu.get() << std::endl;          // 当promise还没有值的时候在此等待
    std::cout << std::this_thread::get_id() << std::endl;
    t.join();
    return 0;
}