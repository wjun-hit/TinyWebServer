#include "gtest/gtest.h"
#include"Server.hpp"
#include"HttpUrlHandler.hpp"
#include"HttpRequest.hpp"
#include"HttpResponse.hpp"
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include<iostream>
#include<chrono>
#include"FileSender.hpp"

using namespace std;

#ifndef HTTPHANDLERTEST
#define HTTPHANDLERTEST

class HttpHandlerTest : public http::HttpUrlHandler {
public:
    void handler(const http::HttpRequest& resquest, http::HttpResponse& response)
    {
        // LOG_INFO("request :\n" << resquest.toString());
        response.setFileSender(new HtmlFileSender("/home/wjun/code/tinyWeb/root/judge.html"));
        response.appendHeaderKeepAlive();
        

        // response.appendHeader("123", "456");
        // response.setBody("hello world");

    }

};

#endif

TEST(ServerTest, test0)
{
    string url = "/";
    http::HttpRegister::instance().append(url, new HttpHandlerTest());

    Server server;
    server.start();
    this_thread::sleep_for(std::chrono::seconds(20));
    server.stop();
    ASSERT_TRUE(true);
}
