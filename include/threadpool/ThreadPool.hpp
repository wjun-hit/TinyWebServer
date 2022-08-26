#ifndef THREAD_POLL_HPP
#define THREAD_POLL_HPP

#include <iostream>
#include <memory>
#include <functional>
#include <thread>
#include <list>

#include "BlockQueue.hpp"

class ThreadPool {
public:
    using Task = std::function<void()>;
    ThreadPool()
    {}
    ThreadPool(int threadNum_, int maxSz_ = 10000) : threadNum(threadNum_), blockQueue(threadNum_, maxSz_)
    {}
    void init(int threadNum_ = 8, int maxSz_ = 10000);
    void start();
    std::list<std::shared_ptr<std::thread>>& getThreadGroup();
    bool addTask(Task&& task);
    void runInThread();
    void stop();
    int size();

private:
    int threadNum;
    bool isStop {false};
    bool isNeedCommutication {false};
    utils::BlockQueue<Task> blockQueue;

    std::list<std::shared_ptr<std::thread>> threadGroup;//线程组
};

#endif