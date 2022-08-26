#include"ThreadPool.hpp"

void ThreadPool::init(int threadNum_, int maxSz_)
{
    threadNum = threadNum_;
    blockQueue.init(threadNum_, maxSz_);
}

void ThreadPool::start()
{
    for (int i = 0; i < threadNum; i++) {
        threadGroup.push_back(std::make_shared<std::thread>(&ThreadPool::runInThread, this));
    }
}

std::list<std::shared_ptr<std::thread>>& ThreadPool::getThreadGroup()
{
    return threadGroup;
}

bool ThreadPool::addTask(Task&& task)
{
    return blockQueue.pushTask(task);
}

void ThreadPool::runInThread()
{
    while (!isStop) {
        Task task;
        if (blockQueue.popTask(task)) {
            task();
        }
    }
}

void ThreadPool::stop()
{
    isStop = true;
    blockQueue.stop();
    for (auto& th : threadGroup) {
        if (th) {
            th->join();
        }
    }
    threadGroup.clear();
}

int ThreadPool::size()
{
    return blockQueue.size();
}