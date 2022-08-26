#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>
#include <thread>
#include <memory>
#include <fstream>
#include <filesystem>

#include "BlockQueue.hpp"
#include "ExactTime.hpp"

class Log {
public:
    static bool isOpenLog;
    static Log& instance()
    {
        static Log ins;
        return ins;
    }
    ~Log();
    bool init(const std::string& logPath_, int splitLine_ = 100000, int queueNum_ = 8, int maxQueueSize_ = 10000);
    void writeLog(std::string line);
    void closeLog();

private:
    Log()
    {}
    void flush();
    std::string getLogName();
    void asyncWriteLog();
private:
    int lineNum{0};
    int splitLine;  //日志最大行数
    int queueNum;
    int maxQueueSize;

    bool isStop {false};
    bool isInit {false};

    std::string logPath;

    utils::ExactTime sysTime;
    int today;

    utils::BlockQueue<std::string>* blockQueue;

    std::shared_ptr<std::thread> asyncThread;
    std::ofstream ofs;
};

#define LOG_CONCAT(LEVAL, ...) \
if (Log::isOpenLog) { \
    std::ostringstream oss; \
    utils::ExactTime exactTime; \
    oss << "thread: " << std::setfill('0') << std::setw(3) << std::this_thread::get_id() << ": "; \
    oss << exactTime.toString() << LEVAL << __FILE__ << ":" << __LINE__ << ": " << __VA_ARGS__ << std::endl;  \
    Log::instance().writeLog(oss.str()); \
}

#define LOG_DEBUG(...)  LOG_CONCAT(" [debug] ", __VA_ARGS__)
#define LOG_INFO(...)   LOG_CONCAT(" [info] ", __VA_ARGS__)
#define LOG_WARN(...)   LOG_CONCAT(" [warn] ", __VA_ARGS__)
#define LOG_ERROR(...)  LOG_CONCAT(" [erro] ", __VA_ARGS__)

#endif