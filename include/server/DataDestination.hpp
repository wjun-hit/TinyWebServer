#ifndef DATA_DESTINATION_HPP
#define DATA_DESTINATION_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <unistd.h>

#include "FileSender.hpp"
#include "Log.hpp"

class DataDestination {
public:
    DataDestination() {}
    virtual ~DataDestination() {}
    virtual bool write(char* data, FileSender* fileSender) = 0;
    virtual void setFd(int fd) = 0;
};

class SocketDataDestination : public DataDestination {
public:
    SocketDataDestination(int fd) : sockfd(fd) {}
    ~SocketDataDestination() {}
    void setFd(int fd)
    {
        sockfd = fd;
    }
    bool write(char* data, FileSender* fileSender)
    {
        int bytesHaveSend = 0;
        int bytesNeedSend = strlen(data);
        while (true) {
            int ret = send(sockfd, data + bytesHaveSend, bytesNeedSend - bytesHaveSend, 0);
            if (ret <= 0) {
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
        if (fileSender) {
            fileSender->sendData(sockfd);
        }
        return true;
    }
private:
    int sockfd;
};

#endif