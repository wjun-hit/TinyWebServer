#ifndef TIMED_EVENT_HPP
#define TIMED_EVENT_HPP

#include <iostream>
#include <functional>
#include <thread>
#include <ctime>

#include "ExactTime.hpp"

namespace timer {

class TimedEvent {
public:
    using Func = std::function<void()>;
    TimedEvent()
    {}
    TimedEvent(const Func& func_, int durationSec_, bool isCycle_);

    void run();
    bool getIsCycle();
    // sort从小到大排序
    bool operator < (const TimedEvent& b);
    // 优先队列 小顶堆
    friend bool operator < (const TimedEvent& a, const TimedEvent& b)
    {
        return a.nextRunTime > b.nextRunTime;
    }
    void setNextRunTime();
    int getRemainderTime();

private:
    Func func;
    int durationSec;
    bool isCycle;
    std::time_t nextRunTime;
};

}

#endif