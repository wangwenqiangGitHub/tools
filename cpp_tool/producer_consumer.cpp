//=====================================================================
//
// producer_consumer.cpp - 
//
// Created by wwq on 2023/12/22
// Last Modified: 2023/12/22 17:25:46
// notify_all：notify_all会唤醒所有等待该条件变量的线程。如果有多个线程在等待条件变量，
//			   调用notify_all会唤醒它们所有，让它们有机会重新竞争锁并检查条件是否满足。
//			   这在某些情况下可能会导致更多的上下文切换和竞争，但能确保所有等待的线程都有机会被唤醒
//notify_one：notify_one只会唤醒一个等待该条件变量的线程。如果有多个线程在等待条件变量，
//            调用notify_one只会唤醒其中一个，具体唤醒哪一个是不确定的。这在某些情况下可能会更高效，
//            因为只有一个线程会被唤醒，减少了竞争和上下文切换的开销，但无法保证所有等待的线程都会被唤醒。
//=====================================================================
#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

std::queue<std::string> messages;
std::mutex mtx;
std::condition_variable cv;

void producer() {
    while (true) {
        std::string message = "Message " + std::to_string(messages.size() + 1);
        {
            std::lock_guard<std::mutex> lock(mtx);
            messages.push(message);
        }
        cv.notify_all();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void consumer(int id) {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, []{ return !messages.empty(); });
        std::string message = messages.front();
        messages.pop();
        lock.unlock();
        std::cout << "Consumer " << id << " received: " << message << std::endl;
    }
}

int main() {
    std::thread producerThread(producer);
    std::vector<std::thread> consumerThreads;
    for (int i = 0; i < 3; ++i) {
        consumerThreads.emplace_back(consumer, i);
    }
    producerThread.join();
    for (auto& thread : consumerThreads) {
        thread.join();
    }
    return 0;
}
