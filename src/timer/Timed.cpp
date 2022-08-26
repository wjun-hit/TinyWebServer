#include"Timed.hpp"

namespace timer {

void Timed::start()
{
    workThread = std::make_shared<std::thread>(&Timed::run, this);
}

void Timed::appendTask(const Func& func, int durationSec, bool isCycle)
{
    std::unique_lock<std::mutex> locker(mutex);
    taskPrioQueue.push(TimedEvent(func, durationSec, isCycle));
    hasAdd = true;
    cond.notify_all();
}

void Timed::stop()
{
    std::unique_lock<std::mutex> locker(mutex);
    isStop = true;
    cond.notify_all();
    if (workThread) {
        workThread->join();
    }
}

void Timed::run()
{
    while (!isStop) {
        TimedEvent timedEvent;

        if (true) {
            std::unique_lock<std::mutex> locker(mutex);
            if (taskPrioQueue.size() > 0) {
                timedEvent = taskPrioQueue.top();
            } else {
                cond.wait(locker, [this]()->bool{return hasAdd;});
                continue;
            }
        }
        if (timedEvent.getRemainderTime() > 0) {
            std::unique_lock<std::mutex> locker(mutex);
            cond.wait_for(locker, std::chrono::seconds(timedEvent.getRemainderTime()), [this]()->bool{return hasAdd;});
        } else {
            timedEvent.run();

            std::unique_lock<std::mutex> locker(mutex);
            taskPrioQueue.pop();
            if (timedEvent.getIsCycle()) {
                timedEvent.setNextRunTime();
                taskPrioQueue.push(timedEvent);
            }
        }
    }
}

}