//
// Created by teagm on 2023/4/18.
//

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

std::mutex m;
std::condition_variable cv;
std::string data;
bool ready = false;
bool processed = false;

void worker_thread()
{
    // Wait until main() sends data
    std::unique_lock<std::mutex> lk(m);
    std::cout<<"work...\n";
    cv.wait(lk, []{return ready;});

    // after the wait, we own the lock.
    std::cout << "Worker thread is processing data\n";
    data += " after processing";

    // Send data back to main()
    processed = true;
    std::cout << "Worker thread signals data processing completed\n";

    // Manual unlocking is done before notifying, to avoid waking up
    // the waiting thread only to block again (see notify_one for details)
    lk.unlock();
    cv.notify_one();

}

//g++ -o a condition_variable.cc -lpthread
int main()
{
    std::thread worker(worker_thread); //start worker_thread
    data = "Example data";
    // send data to the worker thread
    {
        std::lock_guard<std::mutex> lk(m);   //acquire lk,RAII scope范围{}
        ready = true;   //true for cv.wait(lk, []{return ready;}) to pass through

        std::cout << "main() sleep 3s to release lk\n";
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }  //release lk
    cv.notify_one();    //make sure worker thread to be waked up

    // wait for the worker
    {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, []{return processed;});
    }
    std::cout << "Back in main(), data = " << data << '\n';

    worker.join();    //block current_thread(main) until worker finished
}
