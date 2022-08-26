#ifndef THREAD_COMMUTICATION_HPP
#define THREAD_COMMUTICATION_HPP

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <sys/stat.h>

#include <iostream>
#include <unordered_map>
#include <cstring>
#include <thread>
#include <functional>

#include "Log.hpp"
#include "ThreadPool.hpp"
#include "Epoll.hpp"
#include "ThreadMsg.hpp"

class ThreadCommutication {
public:
    virtual void start() = 0;
    virtual bool sendMsg(ThreadMsg* msg) = 0;
    virtual bool recvMsg(int pipeFd, ThreadMsg* msg) = 0;
    virtual bool append(std::thread::id threadIndex) = 0;
    virtual int getReadFd(std::thread::id threadIndex) = 0;
};

class ThreadCommuticationPipe : public ThreadCommutication {
public:
    ThreadCommuticationPipe(ThreadPool* pool_, Epoll* epoll_, std::function<void(int)> dealFunc_)
    : pool(pool_), epoll(epoll_), dealFunc(dealFunc_)
    {}
    void start();
    bool sendMsg(ThreadMsg* msg);
    bool recvMsg(int pipeFd, ThreadMsg* msg);

    bool append(std::thread::id threadIndex);
    int getReadFd(std::thread::id threadIndex);
    
    bool writePipe(char* data, std::thread::id threadIndex);
    bool readPipe(int fd, char* data, int limitLen);
    
private:
    std::unordered_map<std::thread::id, int> readFd;
    std::unordered_map<std::thread::id, int> writeFd; 

    ThreadPool* pool;
    Epoll* epoll;

    std::function<void(int)> dealFunc;
};

#endif