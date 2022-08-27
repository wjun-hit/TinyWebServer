#include "InactiveConn.hpp"
#include "Server.hpp"

void InactiveConn::init(DelFunc delFunc_)
{
    delFunc = delFunc_;
} 

void InactiveConn::newActiveFd(int fd)
{
    activeFd.insert(fd);
    if (lastActive.count(fd)) {
        lastActive.erase(fd);
    }
}

void InactiveConn::delFd(int fd)
{
    if (lastActive.count(fd)) {
        lastActive.erase(fd);
    } else if (activeFd.count(fd)) {
        activeFd.erase(fd);
    }
}

void InactiveConn::dealInactiveConn()
{
    for (auto fd : lastActive) {
        LOG_INFO("deal inactive connection, fd: " << fd);
        delFunc(fd);
    }
    lastActive.clear();
    swap(lastActive, activeFd);
}
