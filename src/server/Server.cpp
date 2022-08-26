#include "Server.hpp"

bool Server::init(int threadNum_, int maxClientNum_, int port_, int timeSlot_, bool listenTrigmode_, bool clientTrigmode_)
{
    threadNum = threadNum_;
    maxClientNum = maxClientNum_;
    port = port_;
    timeSlot = timeSlot_;
    listenTrigmode = listenTrigmode_;
    clientTrigmode = clientTrigmode_;

    // 线程池初始化
    threadPool.init(threadNum, maxClientNum);
    // 定义一个线程池与epoll通信的工具，线程池发送的信息会被epoll监听到，并调用dealTheadPoolMsg方法处理信息
    threadCommutication = new ThreadCommuticationPipe(&threadPool, &epoll, [this](int fd_){this->dealTheadPoolMsg(fd_);});

    // 初始化处理非活动连接的对象，传入删除fd的方法
    inactiveConn.init([this](int fd_){this->delFd(fd_);});
    // 将以下两个方法放入定时器，initInactiveConn 0秒后执行，并且不循环
    // sendInactiveConnMsg，每timeSlot执行一次，发送一个信息
    timed.appendTask([this](){this->initInactiveConn();}, 0, false);
    timed.appendTask([this](){this->sendInactiveConnMsg();}, timeSlot, true);

    // 客户端对象池初始化
    clientPool.init(threadNum, std::bind(&Server::createNewClient, this), maxClientNum);

    // 创建套接字
    int fd = socketServer.createSocket(port);
    if (fd < 0) {
        return false;
    }
    // epoll树上发生套接字fd的时间，则执行dealNewConn，处理一个新的连接
    epoll.appendRdwrFdFuncs(fd, [this](int fd_){this->dealNewConn(fd_);});
    // 出错处理
    epoll.setErrDealFunc([this](int fd_){this->closeFd(fd_);});
    // 普通的读事件，调用dealReadEvent
    epoll.setComReadFunc([this](int fd_){this->dealReadEvent(fd_);});
    // 普通的写事件，调用dealWriteEvent
    epoll.setComWriteFunc([this](int fd_){this->dealWriteEvent(fd_);});

    return true;
}

void Server::start()
{
    isStop = false;
    // 将套接字fd加入epoll中，开始监听事件
    int fd = socketServer.getFd();
    epoll.addFd(fd, true, listenTrigmode, false);
    // 运行线程池
    threadPool.start();
    // 运行与线程池通信的工具
    threadCommutication->start();
    // 运行定时器
    timed.start();
    // 运行服务
    serverMainThread = std::make_shared<std::thread>(&Server::run, this);
    std::cout << "Server begin.." << std::endl;
}

void Server::stop()
{
    threadPool.stop();
    timed.stop();
    isStop = true;
    if (serverMainThread) {
        serverMainThread->join();
    }
}

void Server::run()
{
    while (!isStop) {
        if (epoll.eventDeal() < 0) {
            break;
        }
    }
}

bool Server::initNewConn()
{
    int clientFd = socketServer.acceptNewClientFd();
    if (clientFd < 0) {
        return false;
    }    
    mapFdClient[clientFd] = clientPool.getObject();
    mapFdClient[clientFd]->setFd(clientFd);
    epoll.addFd(clientFd, true, clientTrigmode, true);
    inactiveConn.newActiveFd(clientFd);
    return true;
}

void Server::dealNewConn(int fd)
{
    if (listenTrigmode) {
        while (initNewConn()) ;
    } else {
        initNewConn();
    }
}

void Server::dealReadEvent(int fd)
{
    inactiveConn.newActiveFd(fd);
    threadPool.addTask(std::bind(&HttpClient::processRead, mapFdClient[fd]));
}

void Server::dealWriteEvent(int fd)
{
    inactiveConn.newActiveFd(fd);
    threadPool.addTask(std::bind(&HttpClient::processWrite, mapFdClient[fd]));
}

void Server::dealTheadPoolMsg(int pipeFd) {
    int fd;
    ThreadMsgPipe::MODE_TYPE mode;
    ThreadMsgPipe msg;
    while (true) {
        bool ret = threadCommutication->recvMsg(pipeFd, &msg);
        fd = msg.getFd();
        mode = msg.getMode();
        if (!ret) {
            return;
        }
        switch (mode) {
            case ThreadMsgPipe::READ :
                modFdToRead(fd);
                break;
            case ThreadMsgPipe::WRITE :
                modFdToWrite(fd);
                break;
            case ThreadMsgPipe::DEL :
                closeFd(fd);
                break;
        }
    }
}

void Server::dealInactiveConn(int pipeFd)
{
    ThreadMsgPipe msg;
    while (threadCommutication->recvMsg(pipeFd, &msg)) ;
    inactiveConn.dealInactiveConn();
}

void Server::initInactiveConn()
{
    threadCommutication->append(std::this_thread::get_id());
    int fd = threadCommutication->getReadFd(std::this_thread::get_id());
    epoll.addFd(fd, true, true, false);
    epoll.appendrReadFdFuncs(fd, [this](int fd_){this->dealInactiveConn(fd_);});
}

void Server::sendInactiveConnMsg()
{
    ThreadMsgPipe msg;
    msg.delFd(-1);
    threadCommutication->sendMsg(&msg);
}

void Server::delFd(int fd)
{
    if (mapFdClient.find(fd) == mapFdClient.end()) {
        return;
    }
    mapFdClient[fd]->reset();
    clientPool.returnObject(mapFdClient[fd]);
    mapFdClient.erase(fd);
    epoll.delFd(fd);
    close(fd);  
}

void Server::closeFd(int fd)
{
    inactiveConn.delFd(fd);
    delFd(fd);
}

void Server::modFdToWrite(int fd)
{
    epoll.modFd(fd, false, clientTrigmode, true);
}

void Server::modFdToRead(int fd)
{
    epoll.modFd(fd, true, clientTrigmode, true);
}

HttpClient* Server::createNewClient()
{
    HttpClient* client = new HttpClient(-1, this->clientTrigmode);
    client->setThreadCommutication(this->threadCommutication);
    return client;
}
