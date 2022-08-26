#ifndef HTTP_PROCESS_HPP
#define HTTP_PROCESS_HPP

#include <iostream>
#include "HttpReader.hpp"
#include "HttpParse.hpp"
#include "HttpWriter.hpp"
#include "HttpProduce.hpp"
#include "HttpState.hpp"
#include "HttpResponse.hpp"
#include "HttpRequest.hpp"
#include "DataDestination.hpp"
#include "DataSource.hpp"

namespace http {

class HttpProcess {
public:
    HttpProcess(){}

    void init(HttpParse* parser_ = nullptr, HttpProduce* producer_ = nullptr, 
                HttpReader* reader_ = nullptr, HttpWriter* writer_ = nullptr,
                HttpRequest* request_ = nullptr, HttpResponse* response_ = nullptr, 
                DataSource* dataSource_ = nullptr, DataDestination* dataDestination_ = nullptr);

    PROCESS_STATUS processRead();
    PROCESS_STATUS processWrite();

    void setParser(HttpParse* parser_);
    void setProducer(HttpProduce* dealer_);
    void setReader(HttpReader* reader_);
    void setWriter(HttpWriter* writer_);
    void setResponse(HttpResponse* response_);
    void setRequest(HttpRequest* request_);
    void setDataDestination(DataDestination* dataDestination_);
    void setDataSource(DataSource* dataSource_);

    bool getIsClose();

    void reset()
    {
        parser->reset();
        reader->readFinish();
        writer->writeFinish();
        request->reset();
        response->reset();
        isClose = KEEP_ALIVE_SOCKET;
    }

private:
    bool isClose{KEEP_ALIVE_SOCKET};  // 发送完数据是否关闭

    HttpReader* reader;
    HttpParse* parser;
    HttpWriter* writer;
    HttpProduce* producer;
    HttpResponse* response;
    HttpRequest* request;
    DataDestination* dataDestination;
    DataSource* dataSource;
};

}

#endif