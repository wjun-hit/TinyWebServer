#include"ThreadCommutication.hpp"

void ThreadCommuticationPipe::start()
{
    std::list<std::shared_ptr<std::thread>> threadGroup = pool->getThreadGroup();
    for (auto& th : threadGroup) {
        append(th->get_id());
    }

    for (auto threadFd : readFd) {
        int fd = threadFd.second;
        epoll->addFd(fd, true, true, false);
        epoll->appendrReadFdFuncs(fd, dealFunc);
    }
}

bool ThreadCommuticationPipe::sendMsg(ThreadMsg* msg)
{
    return writePipe(msg->encode(), std::this_thread::get_id());
}

bool ThreadCommuticationPipe::recvMsg(int pipeFd, ThreadMsg* msg)
{
    if (readPipe(pipeFd, msg->getData(), msg->getLength())) {
        msg->decode();
        return true;
    }
    return false;
}

bool ThreadCommuticationPipe::append(std::thread::id threadIndex)
{
    int fd[2];
    int ret = socketpair(AF_UNIX, SOCK_STREAM, 0, fd);
    if (ret < 0) {
        LOG_ERROR("pipe error!");
        return false;
    }
    readFd[threadIndex] = fd[0];
    writeFd[threadIndex] = fd[1];
    return true;
}

int ThreadCommuticationPipe::getReadFd(std::thread::id threadIndex)
{
    if (readFd.find(threadIndex) == readFd.end()) {
        return -1;
    }
    return readFd[threadIndex];
}

bool ThreadCommuticationPipe::writePipe(char* data, std::thread::id threadIndex)
{
    if (writeFd.find(threadIndex) == writeFd.end()) {
        LOG_ERROR("write pipe error! data: " << data << "  threadIndex: " << threadIndex);
        return false;
    }
    int fd = writeFd[threadIndex];
    int bytesHaveSend = 0;
    int bytesNeedSend = strlen(data);
    while (true) {
        int ret = write(fd, data + bytesHaveSend, bytesNeedSend - bytesHaveSend);
        if (ret <= 0) {
            std::cout << "writePipe: fd=" << fd << "  data:" << data << std::endl;
            if (errno == EAGAIN) {
                return true;
            }
            return false;
        }
        bytesHaveSend += ret;
        if (bytesNeedSend == bytesHaveSend) {
            break;
        }
    }
    return true;
}

bool ThreadCommuticationPipe::readPipe(int fd, char* data, int limitLen)
{
    int bytesNeedRecv = limitLen;
    int bytesHaveRecv = 0;
    while (true) {
        int ret = read(fd, data + bytesHaveRecv, bytesNeedRecv - bytesHaveRecv);
        if (ret < 0) {
            if (errno == EAGAIN) {
                return false;
            }
            std::cout << "readPipe: fd=" << fd << std::endl;
            return false;
        }
        bytesHaveRecv += ret;
        if (bytesHaveRecv == bytesNeedRecv) {
            break;
        }
    }  
    return true; 
}