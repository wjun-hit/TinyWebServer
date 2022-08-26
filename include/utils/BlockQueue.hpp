#ifndef BLOCK_QUEUE_HPP
#define BLOCK_QUEUE_HPP

#include <iostream>
#include <memory>
#include <functional>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <list>

namespace utils {

template<class Task>
class BlockQueue {
public:
    BlockQueue()
    {}
    BlockQueue(int threadNum_, int maxSz = 100000);
    void init(int threadNum_, int maxSz = 100000);

    bool pushTask(Task& task);
    bool popTask(Task& task);
    void stop();
    int size();

private:
    bool isNotFull(int n);
    bool isNotEmpty(int n);

private:
    std::vector<std::list<Task>> queues;
    std::vector<std::mutex> mutexs;
    std::vector<std::condition_variable> notEmpty; 
    std::vector<std::condition_variable> notFull; 

    int threadNum;
    int maxSize;
    bool isStop{false};

    std::atomic_char32_t popCursor{0};
    std::atomic_char32_t pushCursor{0};
    std::atomic_char32_t dataNum{0};
};

template<class Task>
BlockQueue<Task>::BlockQueue(int threadNum_, int maxSz)
{
    init(threadNum_, maxSz);
}

template<class Task>
void BlockQueue<Task>::init(int threadNum_, int maxSz)
{
    threadNum = threadNum_;
    maxSize = maxSz;
    queues = std::vector<std::list<Task>>(threadNum);
    mutexs = std::vector<std::mutex>(threadNum);
    notEmpty = std::vector<std::condition_variable>(threadNum);
    notFull = std::vector<std::condition_variable>(threadNum);
}

template<class Task>
bool BlockQueue<Task>::pushTask(Task& task)
{
    int n = pushCursor++;
    n = n % threadNum;
    std::unique_lock<std::mutex> locker(mutexs[n]);
    notFull[n].wait(locker, [this, n]()->bool {return isNotFull(n); });
    if (isStop) {
        return false;
    }
    queues[n].push_back(task);
    notEmpty[n].notify_one();
    dataNum++;
    return true;
}

template<class Task>
bool BlockQueue<Task>::popTask(Task& task)
{
    int n = popCursor++;
    n = n % threadNum;
    std::unique_lock<std::mutex> locker(mutexs[n]);
    notEmpty[n].wait(locker, [this, n]()->bool {return isNotEmpty(n); });
    if (isStop) {
        return false;
    }
    task = queues[n].front();
    queues[n].pop_front();
    notFull[n].notify_one();
    dataNum--;
    return true;
}

template<class Task>
void BlockQueue<Task>::stop()
{
    isStop = true;
    for (int i = 0; i < threadNum; i++) {
        notFull[i].notify_all();
        notEmpty[i].notify_all();
    }
}

template<class Task>
int BlockQueue<Task>::size()
{
    return dataNum;
    int sum = 0;
    for (int i = 0; i < threadNum; i++) {
        sum += queues[i].size();
    }
    return sum;
}

template<class Task>
bool BlockQueue<Task>::isNotFull(int n)
{
    return queues[n].size() < maxSize || isStop;
}

template<class Task>
bool BlockQueue<Task>::isNotEmpty(int n)
{
    return !queues[n].empty() || isStop;
}

}

#endif