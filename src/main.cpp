#include <iostream>
#include <fstream>

#include "Server.hpp"
#include "HttpUrlHandler.hpp"
#include "FileSender.hpp"
#include "FactoryFileSender.hpp"
#include "Log.hpp"
#include "Config.hpp"

using namespace std;

class HttpHandlerTest : public http::HttpUrlHandler {
public:
    void handler(const http::HttpRequest& resquest, http::HttpResponse& response)
    {
        response.setFileSender(FactoryFileSender::instance().getFileSender(_ROOT_DIR + std::string("/root/judge.html")));
    }

};

int main()
{
    string url = "/";
    HttpHandlerTest* handler = new HttpHandlerTest();
    http::HttpRegister::instance().append(url, handler);
    /* 上述代码为业务部分，可通过注册url的方式来实现对不同url的处理  */
    Config config(_ROOT_DIR + std::string("/config.json"));
    config.print();

    Log::isOpenLog = config.log.isOpenLog;
    Log::instance().init(config.log.logDir, config.log.splitLine, config.log.queueNum, config.log.maxQueueSize);

    Server server;
    int ret = server.init(config.server.threadNum, config.server.maxClientNum, 
                            config.server.port, config.server.timeSlot,
                            config.server.listenTrigmode, config.server.clientTrigmode);
    if (!ret) {
        return 0;
    }
    server.start();
    while(true) {
        string s;
        cin >> s;
        if (s == "end") {
            break;
        }
    }
    server.stop();
    return 0;
}