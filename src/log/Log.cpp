#include"Log.hpp"

bool Log::isOpenLog = true;

#ifdef _START_LOG
bool startLog = Log::instance().init(_ROOT_DIR + std::string("/log"));
#endif

bool Log::init(const std::string& logPath_, int splitLine_, int queueNum_, int maxQueueSize_)
{
    closeLog();
    isStop = false;
    today = sysTime.tm_mday;
    logPath = logPath_;
    splitLine = splitLine_;
    queueNum = queueNum_;
    maxQueueSize = maxQueueSize_;

    blockQueue = new utils::BlockQueue<std::string>(queueNum, maxQueueSize);

    std::filesystem::path path(logPath);
    if (!std::filesystem::exists(path)) {
        std::filesystem::create_directory(path);
    } 
    std::string logFullName = getLogName();

    ofs.open(logFullName, std::ios::app);
    if (!ofs.is_open()) {
        isInit = false;
        return false;
    }
    asyncThread = std::make_shared<std::thread>(&Log::asyncWriteLog, this);
    isInit = true;
    return true;
}

void Log::closeLog()
{
    if (isInit) {
        isStop = true;
        blockQueue->stop();
        if (asyncThread) {
            asyncThread->join();
        }
        ofs.flush();
        ofs.close();
        delete blockQueue;
        isInit = false;
    }
}

void Log::writeLog(std::string line)
{
    if (isInit) {
        blockQueue->pushTask(line);
    } else {
        std::cout << "error!! log has not init" << std::endl;
    }
}

void Log::flush()
{
    ofs.flush();
}

Log::~Log()
{
    closeLog();
}

std::string Log::getLogName()
{
    std::ostringstream logFullName;
    logFullName << logPath << "/trace_" << sysTime.toStringForFilenameExectDay() << "_" << lineNum / splitLine << ".log";
    return logFullName.str();
}

void Log::asyncWriteLog()
{
    std::string line;
    while(!isStop && blockQueue->popTask(line)) {
        ofs << line;
        ofs.flush();
        lineNum++;

        if (lineNum % splitLine == 0 || today != sysTime.refreshTime().tm_mday) {
            ofs.close();

            if (today != sysTime.refreshTime().tm_mday) {
                lineNum = 0;
                today = sysTime.refreshTime().tm_mday;
            }
            std::string logFullName = getLogName();
            ofs.open(logFullName, std::ios::app);
        }
    }
}