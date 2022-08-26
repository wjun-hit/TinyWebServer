#ifndef EXACTIME_HPP
#define EXACTIME_HPP

#include <ctime>
#include <chrono>
#include <string>

namespace utils {

class ExactTime : public std::tm 
{
public:
    static std::time_t currentTimeSec();

    ExactTime();
    ExactTime(time_t usecSinceEpoch_);
    ExactTime& refreshTime();
    std::string toString();
    std::string toStringForFilenameExectDay();

private:
    void init();

public:
    int tm_msec; 
	int tm_usec; 
    time_t usecSinceEpoch;  // 从1900-01-01 00:00:00到当前时间点的微秒数
};

}

#endif