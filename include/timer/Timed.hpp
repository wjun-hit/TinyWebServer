#ifndef TIMED_HPP
#define TIMED_HPP

#include <iostream>
#include <thread>
#include <memory>
#include <functional>
#include <queue>
#include <condition_variable>
#include <chrono>

#include "TimedEvent.hpp"

namespace timer {

class Timed {
public:
    using Func = std::function<void()>;
    Timed()
    {}
    void start();
    void appendTask(const Func& func, int durationSec, bool isCycle);
    void stop();
    void run();

private:
    std::priority_queue<TimedEvent> taskPrioQueue;
    std::shared_ptr<std::thread> workThread;
    bool isStop{false};
    std::mutex mutex;
    std::condition_variable cond; 
    bool hasAdd{false};
};

}

#endif