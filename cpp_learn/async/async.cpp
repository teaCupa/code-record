//
// Created by teagm on 2023/4/19.
//

#include <iostream>
#include <future>
#include <thread>

int fun(int x) {
    x++;
    x *= 10;
    std::cout <<"fun():" << std::this_thread::get_id() << std::endl;
    return x;
}


int main()
{
    // std::launch::deferred 当执行到fu.get才开始创建线程
    std::future<int> fu = std::async(std::launch::deferred, fun, 1);
    std::cout << fu.get() << std::endl;
    std::cout << std::this_thread::get_id() << std::endl;
    return 0;
}