//
// Created by teagm on 2023/4/18.
//

#include <thread>
#include <atomic>
#include <cassert>

/**
 *  Release-Acquire ordering:
 *      1. 限制 CPU 指令的重排
 *             在store()之前的所有读写操作，不允许被移动到这个store()的后面。
 *                   A 不允许被移动到 B 的后面。
 *             在load()之后的所有读写操作，不允许被移动到这个load()的前面。
 *                   D 也不允许被移动到 C 的前面
 *      2. 内存可见
 *         假设 Thread-1 store()的那个值，成功被 Thread-2 load()到了，
 *         那么 Thread-1 在store()之前对内存的写入，此时对 Thread-2 来说，是可见的
 *             当 C 从 while 循环中退出了，说明 C 读取到了 B store()的那个值，此时，Thread-2 保证能够看见 Thread-1
 *             执行 B 之前的所有写入操作（也即是 A）
 */

std::atomic<bool> ready{ false };
int data = 0;

void producer()
{
    data = 100; // A
    ready.store(true, std::memory_order_release); // B    setReady(ready)
}

void consumer()
{
    while (!ready.load(std::memory_order_acquire)) // C   getReady()
             ;
    assert(data == 100); // never failed // D
}

int main()    //g++ -o a threads_producer_consumer.cc -lpthread
{
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();

    return 0;
}