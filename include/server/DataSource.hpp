#ifndef DATA_SOURCR_HPP
#define DATA_SOURCR_HPP

#include <sys/types.h>
#include <sys/socket.h>

#include <iostream>

#include "Log.hpp"

class DataSource {
public:
    DataSource() {}
    virtual ~DataSource() {}
    virtual int read(char* data, int limitLength) = 0;
    virtual void setFd(int fd) = 0;
};

class SocketDataSource : public DataSource {
public:
    SocketDataSource(int fd, bool isET_ = false) : sockfd(fd), isET(isET_)
    {}
    ~SocketDataSource() {}
    void setFd(int fd)
    {
        sockfd = fd;
    }
    int read(char* data, int limitLength)
    {
        int bytesRead = 0;
        if (isET) {
            while (true) {
                int ret = recv(sockfd, data + bytesRead, limitLength - bytesRead, 0);
                if (ret == -1) {
                    if (errno == EAGAIN || errno == EWOULDBLOCK) {
                        break;
                    }
                    return -1;
                } else if (ret == 0) {
                    return 0;
                }
                bytesRead += ret;
            }
        } else {
            bytesRead = recv(sockfd, data, limitLength, 0);
            if (bytesRead <= 0) {
                return -1;
            }
        }
        return bytesRead;
    }
private:
    int sockfd;
    bool isET;
};

#endif