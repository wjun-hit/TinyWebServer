#ifndef HTTP_CLIENT_HPP
#define HTTP_CLIENT_HPP

#include <iostream>

#include "DataDestination.hpp"
#include "DataSource.hpp"
#include "HttpProcess.hpp"
#include "HttpReader.hpp"
#include "HttpWriter.hpp"
#include "HttpParse.hpp"
#include "HttpProduce.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "HttpState.hpp"
#include "ThreadMsg.hpp"
#include "ThreadCommutication.hpp"

class HttpClient {
public:
    HttpClient(int fd, bool clientTrigmode = true);
    ~HttpClient();

    void setFd(int fd);

    void setDataSource(DataSource* dataSource_);
    void setDataDestination(DataDestination* dataDestination_);
    void setThreadCommutication(ThreadCommutication* threadCommutication_);

    void processRead();
    void processWrite();

    void reset();

private:
    int sockfd;

    DataSource* dataSource;
    DataDestination* dataDestination;

    http::HttpParse* parser;
    http::HttpProduce* producer; 
    http::HttpReader* reader;
    http::HttpWriter* writer;
    http::HttpRequest* request;
    http::HttpResponse* response;
    http::HttpProcess* httpProcess;

    ThreadCommutication* threadCommutication;
};

#endif