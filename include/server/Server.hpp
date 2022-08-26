#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <mutex>
#include <thread>
#include <memory>
#include <unordered_map>

#include "ThreadPool.hpp"
#include "Epoll.hpp"
#include "SocketServer.hpp"
#include "Log.hpp"
#include "HttpClient.hpp"
#include "ObjectPool.hpp"
#include "Timed.hpp"
#include "ThreadCommutication.hpp"
#include "InactiveConn.hpp"
#include "ThreadMsg.hpp"

class Server {
public:
    Server()
    {}
    bool init(int threadNum_ = 8, int maxClientNum_ = 10000, int port_ = 6666, int timeSlot_ = 5, 
                bool listenTrigmode_ = true, bool clientTrigmode_ = true);
    void start(); 
    void stop();
private:
    void run();  // 服务会一直在该方法运行，指导服务被stop
    bool initNewConn();        // 初始化所有新的连接客户端
    void dealNewConn(int fd);  // 有新连接事件，调用initNewConn
    void dealReadEvent(int fd);// 有读事件，将要处理的读事件加入到线程池
    void dealWriteEvent(int fd);// 有写事件，将要处理的写事件加入到线程池
    void dealTheadPoolMsg(int pipeFd); // 线程池处理完，在该方法收信息并处理
    void dealInactiveConn(int pipeFd); // 定时到，处理非活动的客户端连接
    void initInactiveConn();   // 初始化非活动连接
    void sendInactiveConnMsg(); // 该方法会在定时器内定时循环执行，给管道发信息，会触发epoll读事件，然后执行上述的dealInactiveConn
    void delFd(int fd);  // 删除fd
    void closeFd(int fd); // 删除fd，并删除非活动连接里的fd
    void modFdToWrite(int fd); // 将fd的监听事件改为写
    void modFdToRead(int fd);  // 将fd的监听事件改为读
    HttpClient* createNewClient(); // 创建一个客户端，在客户端池里面用改函数创建对象
    
private:
    bool listenTrigmode;  // 套接字监听模式，true：ET模式， false:LT
    bool clientTrigmode;  // 客户端监听模式，true：ET模式， false:LT

    bool isStop {false}; 

    int threadNum;   // 线程池数
    int maxClientNum; // 最大客户端数量
    int port;   // 监听端口
    int timeSlot;  // 定时时间，处理非活动客户端

    std::shared_ptr<std::thread> serverMainThread;  // 运行线程

    timer::Timed timed; // 定时器

    Epoll epoll;
    SocketServer socketServer;

    ThreadPool threadPool;  // 线程池
    ThreadCommutication* threadCommutication;  // 线程池通知主线程对象

    InactiveConn inactiveConn;   // 处理非活动连接对象

    std::unordered_map<int, HttpClient*> mapFdClient; // 正在处理的fd与客户端的map
    ObjectPool<HttpClient> clientPool;  // 客户端池
};

#endif