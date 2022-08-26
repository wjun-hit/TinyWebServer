#include"HttpClient.hpp"

HttpClient::HttpClient(int fd, bool clientTrigmode) : sockfd(fd)
{
    dataSource = new SocketDataSource(fd, clientTrigmode);
    dataDestination = new SocketDataDestination(fd);

    parser = new http::HttpParse();
    producer = new http::HttpProduce();
    reader = new http::HttpReader();
    writer = new http::HttpWriter();
    request = new http::HttpRequest();
    response = new http::HttpResponse();
    httpProcess = new http::HttpProcess();

    httpProcess->init(parser, producer, reader, writer, request, response, dataSource, dataDestination);
}

HttpClient::~HttpClient()
{
    delete dataSource;
    delete dataDestination;

    delete parser;
    delete producer;
    delete reader;
    delete writer;
    delete request;
    delete response;
    delete httpProcess;
}

void HttpClient::setDataSource(DataSource* dataSource_)
{
    dataSource = dataSource_;
    httpProcess->setDataSource(dataSource);
}

void HttpClient::setDataDestination(DataDestination* dataDestination_)
{
    dataDestination = dataDestination_;
    httpProcess->setDataDestination(dataDestination);
}

void HttpClient::setThreadCommutication(ThreadCommutication* threadCommutication_)
{
    threadCommutication = threadCommutication_;
}

void HttpClient::setFd(int fd)
{
    sockfd = fd;
    dataSource->setFd(fd);
    dataDestination->setFd(fd);
}

void HttpClient::reset()
{
    httpProcess->reset();
}

void HttpClient::processRead()
{
    http::PROCESS_STATUS ret = httpProcess->processRead();
    ThreadMsgPipe msg;
    if (ret == http::CONTINUE) {
        msg.modFdToRead(sockfd);
    } else if (ret == http::FINISH) {
        msg.modFdToWrite(sockfd);
    } else if (ret == http::SHUTDOWN) {
        msg.delFd(sockfd);
    }
    threadCommutication->sendMsg(&msg);
}

void HttpClient::processWrite()
{
    http::PROCESS_STATUS ret = httpProcess->processWrite();
    ThreadMsgPipe msg;
    if (ret == http::FINISH) {
        msg.modFdToRead(sockfd);
    } else if (ret == http::SHUTDOWN) {
        msg.delFd(sockfd);
    }
    threadCommutication->sendMsg(&msg);
}