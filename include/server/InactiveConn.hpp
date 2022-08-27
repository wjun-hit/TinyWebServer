#ifndef INACTIVE_CONN_HPP
#define INACTIVE_CONN_HPP

#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <mutex>
#include <memory>
#include <functional>

#include "ThreadMsg.hpp"
#include "ThreadCommutication.hpp"

class InactiveConn {
public:
    using DelFunc = std::function<void(int)>;
    void init(DelFunc delFunc_);
    void newActiveFd(int fd);
    void delFd(int fd);
    void dealInactiveConn();

private:
    std::unordered_set<int> activeFd;
    std::unordered_set<int> lastActive;
    DelFunc delFunc;
};

#endif
