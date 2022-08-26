#include"SocketServer.hpp"

int SocketServer::createSocket(int port_)
{
    port = port_;

    listenFd = socket(PF_INET, SOCK_STREAM, 0);
    if (listenFd == -1) {
        LOG_ERROR("create socket failed!");
        return -1;
    }
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);

    int flag = 1;
    setsockopt(listenFd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));
    int ret = bind(listenFd, (struct sockaddr *)&addr, sizeof(addr)); 
    if (ret == -1) {
        LOG_ERROR("bind failed!");
        listenFd = -1;
        return -1;
    }
    ret = listen(listenFd, 5); 
    if (ret == -1) {
        LOG_ERROR("listen failed!");
        listenFd = -1;
        return -1;
    }
    LOG_INFO("begin listen....  port: " << port);
    return listenFd;
}

int SocketServer::getFd()
{
    return listenFd;
}

int SocketServer::acceptNewClientFd()
{
    struct sockaddr_in cliaddr;
    int addrlen = sizeof(cliaddr);
    int clientFd = accept(listenFd, (struct sockaddr *)&cliaddr, (socklen_t*)&addrlen);
    if (clientFd == -1) {
        if (errno == EWOULDBLOCK || errno==ECONNABORTED || errno==EPROTO || errno==EINTR) {
            return -1;
        }
        LOG_ERROR("accept failed!");
        return -1;
    }
    LOG_INFO("success accept a new client, IP: " << inet_ntoa(cliaddr.sin_addr) << 
                                    "  port: " << cliaddr.sin_port << "  fd: " << clientFd);
    return clientFd;
}