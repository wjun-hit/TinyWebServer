#include "gtest/gtest.h"
#include"SocketServer.hpp"
#include"Epoll.hpp"
#include<unordered_map>
#include"DataSource.hpp"
#include"DataDestination.hpp"

#define SIZE 1024
using namespace std;

class EpollSocketTest {
public:
    void newConn(int fd)
    {
        while (true) {
            int clientFd = socketServer->acceptNewClientFd();
            if (clientFd < 0) {
                break;
            }
            epoll->addFd(clientFd, true, true, true);
            umap[clientFd] = {new SocketDataSource(clientFd, true), new SocketDataDestination(clientFd)};
        }  
    }
    void readTest(int fd)
    {
        int ret = umap[fd].first->read(buf, SIZE-1);
        if (ret < 0) {
            cout << "ret: " << ret << endl;
            return;
        }
        cout << "fd: " << fd << "  read: " << buf << endl;
        epoll->modFd(fd, false, true, true);
    }
    void writeTest(int fd)
    {
        cout << "请输入发送给" << fd << "的： ";
        string str;
        cin >> str;
		strcpy(buf, str.c_str());
		// write(fd, buf, strlen(buf));
        umap[fd].second->write(buf, "33");
        epoll->modFd(fd, true, true, true);
    }
    char buf[SIZE];
    SocketServer* socketServer;
    Epoll* epoll;
    unordered_map<int, pair<SocketDataSource*, SocketDataDestination*>> umap;
};

TEST(SocketServer, test1)
{
    Log::instance().init("/home/wjun/code/tinyWeb/log");
    SocketServer socketServer(6666);
    int fd = socketServer.getFd();
    Epoll epoll;

    EpollSocketTest epollSocketTest;
    epollSocketTest.socketServer = &socketServer;
    epollSocketTest.epoll = &epoll;
    epoll.appendRdwrFdFuncs(fd, [&epollSocketTest](int fd_){epollSocketTest.newConn(fd_);});
    epoll.setComReadFunc([&epollSocketTest](int fd_){epollSocketTest.readTest(fd_);});
    epoll.setComWriteFunc([&epollSocketTest](int fd_){epollSocketTest.writeTest(fd_);});

    epoll.addFd(fd, true, true, false);
    while (true) {
        if (epoll.eventDeal() < 0) {
            break;
        }
    }
    ASSERT_TRUE(true);
}
// TEST(SocketServer, test0)
// {
//     Log::instance().init("/home/wjun/code/tinyWeb/log");
//     SocketServer socketServer(6666);
//     int fd = socketServer.getFd();
//     cout << "fd: " << fd << endl;

// 	char buf[SIZE] = {0};
// 	int client_socket = socketServer.acceptNewClientFd();
//     cout << "client_socket: " << client_socket << endl;
//     // this_thread::sleep_for(std::chrono::seconds(1));
// 	while(1)        //向服务器发送数据，并接收服务器转换后的大写字母
// 	{
//         memset(buf, 0, SIZE);
        
//         int ret = read(client_socket, buf, SIZE-1);
//         if (ret <= 0) {
//             cout << "ret: " << ret << endl;
//             break;
//         }
//         cout << "read: " << buf << endl;

//         memset(buf, 0, SIZE);
//         cout << "请输入你xian输入的: " << endl;
//         string str;
//         cin >> str;
// 		strcpy(buf, str.c_str());
// 		write(client_socket, buf, strlen(buf));
// 	}
// 	close(fd);

//     Log::instance().flush();
//     ASSERT_TRUE(true);
// }