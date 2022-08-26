#include"TimedEvent.hpp"

namespace timer {

TimedEvent::TimedEvent(const Func& func_, int durationSec_, bool isCycle_) 
                    : func(func_), durationSec(durationSec_), isCycle(isCycle_)
{
    setNextRunTime();
}

void TimedEvent::run()
{
    func();
}

bool TimedEvent::getIsCycle()
{
    return isCycle;
}

// sort从小到大排序
bool TimedEvent::operator < (const TimedEvent& b) 
{
    return nextRunTime < b.nextRunTime;
}

void TimedEvent::setNextRunTime()
{
    nextRunTime = durationSec + utils::ExactTime::currentTimeSec();
}

int TimedEvent::getRemainderTime()
{
    std::time_t currentTime = utils::ExactTime::currentTimeSec();
    if (currentTime < nextRunTime) {
        return nextRunTime - currentTime;
    }
    return 0;
}

}