#ifndef THREAD_MSG_HPP
#define THREAD_MSG_HPP

#include <cstdio>
#include <iostream>

class ThreadMsg {
public:
    virtual char* encode() = 0;
    virtual void decode() = 0;
    virtual char* getData() = 0;
    virtual int getLength() = 0;

};

class ThreadMsgPipe : public ThreadMsg {
public:
    using MODE_TYPE = char;
    static const char READ = 'r';
    static const char WRITE = 'w';
    static const char DEL = 'd';

    ThreadMsgPipe()
    {}
    ThreadMsgPipe(int fd_, MODE_TYPE mode_) : fd(fd_), mode(mode_)
    {}
    void init(int fd_, MODE_TYPE mode_);
    char* encode();
    void decode();
    void modFdToRead(int fd_);
    void modFdToWrite(int fd_);
    void delFd(int fd_);
    char* getData();
    int getLength();
    int getFd();
    MODE_TYPE getMode();

private:
    int fd;
    MODE_TYPE mode;
    char data[8];
    int length {8};
};

#endif