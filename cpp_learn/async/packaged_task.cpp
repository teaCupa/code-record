//
// Created by teagm on 2023/4/19.
//

/*
 * @Author: teaCupa yehu2315272482@Foxmail.com
 * @Date: 2022-03-23 13:29:51
 * @LastEditTime: 2023-04-01 11:42:00
 * @Description:
 *
 * Copyright (c) 2023 by company-A, All Rights Reserved.
 */
//https://cloud.tencent.com/developer/article/1584075

#include <iostream>
#include <future>
#include <thread>

int fun(int x) {
    x++;
    x *= 10;
    std::cout << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    return x;
}


int main()
{
    std::packaged_task<int(int)> pt(fun);         // 将函数打包起来
    std::future<int> fu = pt.get_future();        // 并将结果返回给future
    std::thread t(std::ref(pt), 1);
    std::cout << fu.get() << std::endl;
    std::cout << std::this_thread::get_id() << std::endl;
    t.join();
    return 0;
}