#include"ThreadMsg.hpp"

void ThreadMsgPipe::init(int fd_, MODE_TYPE mode_)
{
    fd = fd_;
    mode = mode_;
}

char* ThreadMsgPipe::encode()
{
    data[0] = mode;
    sprintf(data+1,"%07d",fd);
    return data;
}

void ThreadMsgPipe::decode()
{
    mode = data[0];
    fd = std::stoi(data + 1);
}

void ThreadMsgPipe::modFdToRead(int fd_)
{
    fd = fd_;
    mode = READ;
}

void ThreadMsgPipe:: modFdToWrite(int fd_)
{
    fd = fd_;
    mode = WRITE;
}

void ThreadMsgPipe::delFd(int fd_)
{
    fd = fd_;
    mode = DEL;
}

char* ThreadMsgPipe::getData()
{
    return data;
}

int ThreadMsgPipe::getLength()
{
    return length;
}

int ThreadMsgPipe::getFd()
{
    return fd;
}

ThreadMsgPipe::MODE_TYPE ThreadMsgPipe::getMode()
{
    return mode;
}