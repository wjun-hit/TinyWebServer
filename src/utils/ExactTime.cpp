#include"ExactTime.hpp"

namespace utils {

std::time_t ExactTime::currentTimeSec()
{
    ExactTime currentTime;
    return currentTime.usecSinceEpoch / 1000000;
}

ExactTime::ExactTime() 
{
    refreshTime();
}

ExactTime::ExactTime(time_t usecSinceEpoch_) : usecSinceEpoch(usecSinceEpoch_)
{
    init();
}

ExactTime& ExactTime::refreshTime()
{
    std::chrono::system_clock::time_point time_point_now  = std::chrono::system_clock::now();
    std::chrono::system_clock::duration duration_since_epoch  = time_point_now.time_since_epoch();

    usecSinceEpoch = std::chrono::duration_cast<std::chrono::microseconds>(duration_since_epoch).count();

    init();
    return *this;
}

std::string ExactTime::toString()
{
    char temp[30];
    sprintf(temp, "%04d-%02d-%02d %02d:%02d:%02d.%03d%03d", 
            tm_year + 1900, tm_mon + 1, tm_mday, tm_hour, tm_min, tm_sec, tm_msec, tm_usec);
    return std::string(temp);
}

std::string ExactTime::toStringForFilenameExectDay()
{
    char temp[30];
    sprintf(temp, "%04d-%02d-%02d", tm_year + 1900, tm_mon + 1, tm_mday);
    return std::string(temp);
}

void ExactTime::init()
{
    time_t secSinceEpoch = usecSinceEpoch / 1000000;
    localtime_r(&secSinceEpoch, this);
    tm_msec = usecSinceEpoch / 1000 % 1000; 
    tm_usec = usecSinceEpoch % 1000; 
}

}