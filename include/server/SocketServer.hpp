#ifndef SOCKET_SERVER_HPP
#define SOCKET_SERVER_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <iostream>

#include"Log.hpp"

class SocketServer {
public:
    SocketServer()
    {}
    ~SocketServer()
    {
        close(listenFd);
    }
    int createSocket(int port_ = 6666);
    int getFd();
    int acceptNewClientFd();

private:
    int listenFd;
    int port;
};

#endif