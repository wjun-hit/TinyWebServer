#ifndef EPOLL_HPP
#define EPOLL_HPP

#include <sys/epoll.h>
#include <fcntl.h>

#include <iostream>
#include <functional>
#include <unordered_map>

#include "Log.hpp"

const int MAX_EVENT_NUMBER = 10000;

class Epoll {
public:
    using event_type = unsigned int;
    using Func = std::function<void(int)>;
    Epoll();
    int getFd();

    void addFd(int fd, bool isRead, bool isET, bool isOneShot, bool isNonBlock = true);
    void modFd(int fd, bool isModToRead, bool isET, bool isOneShot);
    void delFd(int fd);

    void appendRdwrFdFuncs(int fd, Func func);
    void appendrReadFdFuncs(int fd, Func func);
    void appendrWriteFdFuncs(int fd, Func func);
    void setComReadFunc(Func func);
    void setComWriteFunc(Func func);
    void setErrDealFunc(Func func);

    int eventDeal();
private:
    int setNonBlocking(int fd);
    epoll_event createEvent(int fd, bool isModToRead, bool isET, bool isOneShot);

private:
    int epollFd;
    epoll_event events[MAX_EVENT_NUMBER];

    std::unordered_map<int, Func> rdwrFdFuncs;
    std::unordered_map<int, Func> readFdFuncs;
    std::unordered_map<int, Func> writeFdFuncs;
    Func comReadFunc;
    Func comWriteFunc;
    Func errDealFunc;
};

#endif