#include"HttpProcess.hpp"

namespace http {

void HttpProcess::init(HttpParse* parser_, HttpProduce* producer_, HttpReader* reader_, HttpWriter* writer_,
    HttpRequest* request_, HttpResponse* response_, DataSource* dataSource_, DataDestination* dataDestination_)
{
    setParser(parser_);
    setProducer(producer_);
    setReader(reader_);
    setWriter(writer_);
    setRequest(request_);
    setResponse(response_);
    setDataSource(dataSource_);
    setDataDestination(dataDestination_);
}

void HttpProcess::setParser(HttpParse* parser_)
{
    parser = parser_;
}

void HttpProcess::setProducer(HttpProduce* producer_)
{
    producer = producer_;
}

void HttpProcess::setReader(HttpReader* reader_)
{
    reader = reader_;
}

void HttpProcess::setWriter(HttpWriter* writer_)
{
    writer = writer_;
}

void HttpProcess::setRequest(HttpRequest* request_)
{
    request = request_;
    parser->setRequest(request);
}

void HttpProcess::setResponse(HttpResponse* response_)
{
    response =response_;
    writer->setResponse(response);
}

void HttpProcess::setDataSource(DataSource* dataSource_)
{
    dataSource = dataSource_;
}

void HttpProcess::setDataDestination(DataDestination* dataDestination_)
{
    dataDestination = dataDestination_;
}

bool HttpProcess::getIsClose()
{
    return isClose;
}

PROCESS_STATUS HttpProcess::processRead()
{
    if (reader->readOnce(dataSource)) {
        HTTP_CODE code = parser->parseRead(reader);
        if (code == NO_REQUEST) {
            return CONTINUE;  //继续监听
        } else {
            // LOG_INFO("request :\n" << request->toString());
            isClose = producer->produceWrite(code, request, response);
            reader->readFinish();
            return FINISH;
        }
    } else {
        return SHUTDOWN;
    }
}

PROCESS_STATUS HttpProcess::processWrite()
{
    writer->write(dataDestination);
    writer->writeFinish();
    if (isClose == NEED_TO_CLOSE_SOCKET) {
        return SHUTDOWN;
    }
    return FINISH;
}

}