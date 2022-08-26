#ifndef FILE_SENDER_HPP
#define FILE_SENDER_HPP

#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/uio.h>

#include <cstring>

#include "Log.hpp"

class FileSender {
public:
    FileSender(){}
    virtual bool sendData(int sockfd) = 0;
    virtual int getFileSize() = 0;
};

class HtmlFileSender : public FileSender {
public:
    HtmlFileSender(std::string fileName_) : fileName(fileName_), fileSize(0)
    {
        struct stat fileStat;
        if (stat(fileName.c_str(), &fileStat) < 0) {
            LOG_ERROR("file not exits, file name=" << fileName);
            return;
        }
        if (!(fileStat.st_mode & S_IROTH)) {
            LOG_ERROR(fileName << " does not have read permission, file=");
            return;
        }
        if (S_ISDIR(fileStat.st_mode)) {
            LOG_ERROR(fileName << " is a directory");
            return;
        }
        fileSize = fileStat.st_size;
    }
    void openMmap()
    {
        int fd = open(fileName.c_str(), O_RDONLY);
        fileAddress = (char *)mmap(0, fileSize, PROT_READ, MAP_PRIVATE, fd, 0);
        close(fd);
    }
    bool sendData(int sockfd)
    {
        openMmap();
        int temp = 0;
        int bytesSend = fileSize;
        while (true) {
            temp = send(sockfd, fileAddress + temp, bytesSend, 0);
            if (temp < 0) {
                munmap(fileAddress, fileSize);
                if (errno == EAGAIN) {
                    return true;
                }
                return false;
            }
            bytesSend -= temp;
            if (bytesSend == 0) {
                munmap(fileAddress, fileSize);
                return true;
            }
        }
    }
    int getFileSize()
    {
        return fileSize;
    }
private:
    int fileSize;
    std::string fileName;
    char* fileAddress;
};

#endif