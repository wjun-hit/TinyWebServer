#include "gtest/gtest.h"
#include"HttpReader.hpp"
#include"HttpParse.hpp"
#include"HttpProcess.hpp"
#include"HttpState.hpp"
#include"HttpResponse.hpp"
#include"HttpRequest.hpp"
#include"DataDestination.hpp"
#include"DataSource.hpp"
#include<vector>
#include<cstring>
#include<sstream>

using namespace std;

#ifndef TESTDATASOURCE
#define TESTDATASOURCE
class TestDataSource : public DataSource {
public:
    TestDataSource(ostringstream& dataStream)
    {
        strcpy(data, dataStream.str().c_str());
    }
    int read(char* text, int limitLength)
    {
        int bytesRead = (readIdx + 10 > strlen(data)) ? strlen(data) - readIdx : 10;
        strncpy(text, data + readIdx, bytesRead);
        readIdx += bytesRead;
        return bytesRead;
    }
    bool isFinish()
    {
        return readIdx >= strlen(data);
    }
    char data[1000];
    int readIdx {0};
};
#endif

#ifndef TESTDATDESTINATION
#define TESTDATDESTINATION
class TestDataDestination : public DataDestination {
public:
    bool write(const char* text, const char* fileName)
    {
        // cout << text;
        dataStream << text;
        if (fileName) {
            dataStream << fileName;
        }
        return true;
    }
    std::string getData()
    {
        return dataStream.str();
    }
    ostringstream dataStream;
    int readIdx {0};
};
#endif

TEST(HttpProcessTest, test0)
{
    string endChar = "\r\n";
    string method = "POST";
    string url = "/home/wjun/1.jpg";
    string version = "HTTP/1.1"; 
    string body = "name=Professionaljax&publisher=Wiley6666444tttgg";
    string headerKey = "Host";
    string headerValue = "img.mukewang.com";
    string header1 = headerKey + "  :  " + headerValue + "  ";
    int contLen = body.size();
    string header2 = "Content-Length:" + to_string(contLen);

    
    ostringstream dataStream;
    dataStream << method << " " << url << " " << version << endChar;
    dataStream << header1 << endChar << header2 << endChar;
    dataStream << endChar << body;

    http::HttpProcess hp;

    http::HttpParse parser;
    http::HttpProduce producer;
    
    http::HttpReader reader;
    http::HttpWriter writer;

    http::HttpRequest request;
    http::HttpResponse response;
    
    TestDataSource testDataSource(dataStream);
    TestDataDestination dataDst;

    hp.init(&parser, &producer, &reader, &writer, &request, &response, &testDataSource, &dataDst);
    
    while (!testDataSource.isFinish()) {
        hp.processRead();
        if (hp.getIsClose()) {
            break;
        }
    }
    hp.processWrite();

    ostringstream expect;
    int statusCode = 404;
    expect << version << " " << statusCode << " " << http::StateCodeToText::instance().getTitle(statusCode) << endChar;
    expect << CONNECTION << ":" << CONN_CLOSE << endChar;
    expect << CONTENT_LENGTH << ":" << http::StateCodeToText::instance().getForm(statusCode).size() << endChar;
    expect << endChar << http::StateCodeToText::instance().getForm(statusCode);

    ASSERT_STREQ(expect.str().c_str(), dataDst.getData().c_str());
}

TEST(HttpProcessTest, test1)
{
    string endChar = "\r\n";
    string method = "POST1";
    string url = "/home/wjun/1.jpg";
    string version = "HTTP/1.1"; 
    string body = "name=Professionaljax&publisher=Wiley6666444tttgg";
    string headerKey = "Host";
    string headerValue = "img.mukewang.com";
    string header1 = headerKey + "  :  " + headerValue + "  ";
    int contLen = body.size();
    string header2 = "Content-Length:" + to_string(contLen);

    
    ostringstream dataStream;
    dataStream << method << " " << url << " " << version << endChar;
    dataStream << header1 << endChar << header2 << endChar;
    dataStream << endChar << body;

    http::HttpProcess hp;

    http::HttpParse parser;
    http::HttpProduce producer;
    
    http::HttpReader reader;
    http::HttpWriter writer;

    http::HttpRequest request;
    http::HttpResponse response;
    
    TestDataSource testDataSource(dataStream);
    TestDataDestination dataDst;

    hp.init(&parser, &producer, &reader, &writer, &request, &response, &testDataSource, &dataDst);
    
    while (!testDataSource.isFinish()) {
        hp.processRead();
        if (hp.getIsClose()) {
            break;
        }
    }
    hp.processWrite();

    ostringstream expect;
    int statusCode = 400;
    expect << version << " " << statusCode << " " << http::StateCodeToText::instance().getTitle(statusCode) << endChar;
    expect << CONNECTION << ":" << CONN_CLOSE << endChar;
    expect << CONTENT_LENGTH << ":" << http::StateCodeToText::instance().getForm(statusCode).size() << endChar;
    expect << endChar << http::StateCodeToText::instance().getForm(statusCode);

    ASSERT_STREQ(expect.str().c_str(), dataDst.getData().c_str());
}

TEST(HttpProcessTest, test2)
{
    string endChar = "\r\n";
    string method = "POST";
    string url = "/home/wjun/1.jpg";
    string version = "HTTP/1"; 
    string body = "name=Professionaljax&publisher=Wiley6666444tttgg";
    string headerKey = "Host";
    string headerValue = "img.mukewang.com";
    string header1 = headerKey + "  :  " + headerValue + "  ";
    int contLen = body.size();
    string header2 = "Content-Length:" + to_string(contLen);

    
    ostringstream dataStream;
    dataStream << method << " " << url << " " << version << endChar;
    dataStream << header1 << endChar << header2 << endChar;
    dataStream << endChar << body;

    http::HttpProcess hp;

    http::HttpParse parser;
    http::HttpProduce producer;
    
    http::HttpReader reader;
    http::HttpWriter writer;

    http::HttpRequest request;
    http::HttpResponse response;
    
    TestDataSource testDataSource(dataStream);
    TestDataDestination dataDst;

    hp.init(&parser, &producer, &reader, &writer, &request, &response, &testDataSource, &dataDst);
    
    while (!testDataSource.isFinish()) {
        hp.processRead();
        if (hp.getIsClose()) {
            break;
        }
    }
    hp.processWrite();

    ostringstream expect;
    int statusCode = 400;
    expect << "HTTP/1.1" << " " << statusCode << " " << http::StateCodeToText::instance().getTitle(statusCode) << endChar;
    expect << CONNECTION << ":" << CONN_CLOSE << endChar;
    expect << CONTENT_LENGTH << ":" << http::StateCodeToText::instance().getForm(statusCode).size() << endChar;
    expect << endChar << http::StateCodeToText::instance().getForm(statusCode);

    ASSERT_STREQ(expect.str().c_str(), dataDst.getData().c_str());
}

TEST(HttpProcessTest, test3)
{
    string endChar = "\r\n";
    string method = "POST";
    string url = "/home/wjun/1.jpg";
    string version = "HTTP/1.1"; 
    string body = "name=Professionaljax&publisher=Wiley6666444tttgg";
    string headerKey = "Host";
    string headerValue = "img.mukewang.com";
    string header1 = headerKey + "  :  " + headerValue + "  ";
    int contLen = body.size();
    string header2 = "Content-Length:" + to_string(contLen);

    
    ostringstream dataStream;
    dataStream << method << " " << url << " " << version << "\r";
    dataStream << header1 << endChar << header2 << endChar;
    dataStream << endChar << body;

    http::HttpProcess hp;

    http::HttpParse parser;
    http::HttpProduce producer;
    
    http::HttpReader reader;
    http::HttpWriter writer;

    http::HttpRequest request;
    http::HttpResponse response;
    
    TestDataSource testDataSource(dataStream);
    TestDataDestination dataDst;

    hp.init(&parser, &producer, &reader, &writer, &request, &response, &testDataSource, &dataDst);
    
    while (!testDataSource.isFinish()) {
        hp.processRead();
        if (hp.getIsClose()) {
            break;
        }
    }
    hp.processWrite();

    ostringstream expect;
    int statusCode = 400;
    expect << "HTTP/1.1" << " " << statusCode << " " << http::StateCodeToText::instance().getTitle(statusCode) << endChar;
    expect << CONNECTION << ":" << CONN_CLOSE << endChar;
    expect << CONTENT_LENGTH << ":" << http::StateCodeToText::instance().getForm(statusCode).size() << endChar;
    expect << endChar << http::StateCodeToText::instance().getForm(statusCode);

    ASSERT_STREQ(expect.str().c_str(), dataDst.getData().c_str());
}

TEST(HttpProcessTest, test4)
{
    string endChar = "\r\n";
    string method = "POST";
    string url = "/home/wjun/1.jpg";
    string version = "HTTP/1.1"; 
    string body = "name=Professionaljax&publisher=Wiley6666444tttgg";
    string headerKey = "Host";
    string headerValue = "img.mukewang.com";
    string header1 = headerKey + "  :  " + headerValue + "  ";
    int contLen = body.size();
    string header2 = "Content-Length:" + to_string(contLen);

    
    ostringstream dataStream;
    dataStream << method << " " << url << " " << version << "\n";
    dataStream << header1 << endChar << header2 << endChar;
    dataStream << endChar << body;

    http::HttpProcess hp;

    http::HttpParse parser;
    http::HttpProduce producer;
    
    http::HttpReader reader;
    http::HttpWriter writer;

    http::HttpRequest request;
    http::HttpResponse response;
    
    TestDataSource testDataSource(dataStream);
    TestDataDestination dataDst;

    hp.init(&parser, &producer, &reader, &writer, &request, &response, &testDataSource, &dataDst);
    
    while (!testDataSource.isFinish()) {
        hp.processRead();
        if (hp.getIsClose()) {
            break;
        }
    }
    hp.processWrite();

    ostringstream expect;
    int statusCode = 400;
    expect << "HTTP/1.1" << " " << statusCode << " " << http::StateCodeToText::instance().getTitle(statusCode) << endChar;
    expect << CONNECTION << ":" << CONN_CLOSE << endChar;
    expect << CONTENT_LENGTH << ":" << http::StateCodeToText::instance().getForm(statusCode).size() << endChar;
    expect << endChar << http::StateCodeToText::instance().getForm(statusCode);

    ASSERT_STREQ(expect.str().c_str(), dataDst.getData().c_str());
}

TEST(HttpProcessTest, test5)
{
    string endChar = "\r\n";
    string method = "POST";
    string url = "/home/wjun/1.jpg";
    string version = "HTTP/1.1"; 
    string body = "name=Professionaljax&publisher=Wiley6666444tttgg";
    string headerKey = "Host";
    string headerValue = "img.mukewang.com";
    string header1 = headerKey + "  :  " + headerValue + "  ";
    int contLen = body.size();
    string header2 = "Content-Length:" + to_string(contLen);

    
    ostringstream dataStream;
    dataStream << method << " " << url << " " << version << endChar;
    dataStream << header1 << endChar << header2 << endChar;
    dataStream << "\r" << body;

    http::HttpProcess hp;

    http::HttpParse parser;
    http::HttpProduce producer;
    
    http::HttpReader reader;
    http::HttpWriter writer;

    http::HttpRequest request;
    http::HttpResponse response;
    
    TestDataSource testDataSource(dataStream);
    TestDataDestination dataDst;

    hp.init(&parser, &producer, &reader, &writer, &request, &response, &testDataSource, &dataDst);
    
    while (!testDataSource.isFinish()) {
        hp.processRead();
        if (hp.getIsClose()) {
            break;
        }
    }
    hp.processWrite();

    ostringstream expect;
    int statusCode = 400;
    expect << "HTTP/1.1" << " " << statusCode << " " << http::StateCodeToText::instance().getTitle(statusCode) << endChar;
    expect << CONNECTION << ":" << CONN_CLOSE << endChar;
    expect << CONTENT_LENGTH << ":" << http::StateCodeToText::instance().getForm(statusCode).size() << endChar;
    expect << endChar << http::StateCodeToText::instance().getForm(statusCode);

    ASSERT_STREQ(expect.str().c_str(), dataDst.getData().c_str());
}

TEST(HttpProcessTest, test6)
{
    string endChar = "\r\n";
    string method = "GET";
    string url = "/home/wjun/1.jpg";
    string version = "HTTP/1.1"; 
    string body = "name=Professionaljax&publisher=Wiley6666444tttgg";
    string headerKey = "Host";
    string headerValue = "img.mukewang.com";
    string header1 = headerKey + "  :  " + headerValue + "  ";
    int contLen = body.size();
    string header2 = "Content:" + to_string(contLen);

    
    ostringstream dataStream;
    dataStream << method << " " << url << " " << version << endChar;
    dataStream << header1 << endChar << header2 << endChar;
    dataStream << "\r\n";

    http::HttpProcess hp;

    http::HttpParse parser;
    http::HttpProduce producer;
    
    http::HttpReader reader;
    http::HttpWriter writer;

    http::HttpRequest request;
    http::HttpResponse response;
    
    TestDataSource testDataSource(dataStream);
    TestDataDestination dataDst;

    hp.init(&parser, &producer, &reader, &writer, &request, &response, &testDataSource, &dataDst);
    
    while (!testDataSource.isFinish()) {
        hp.processRead();
        if (hp.getIsClose()) {
            break;
        }
    }
    hp.processWrite();

    ostringstream expect;
    int statusCode = 404;
    expect << "HTTP/1.1" << " " << statusCode << " " << http::StateCodeToText::instance().getTitle(statusCode) << endChar;
    expect << CONNECTION << ":" << CONN_CLOSE << endChar;
    expect << CONTENT_LENGTH << ":" << http::StateCodeToText::instance().getForm(statusCode).size() << endChar;
    expect << endChar << http::StateCodeToText::instance().getForm(statusCode);

    ASSERT_STREQ(expect.str().c_str(), dataDst.getData().c_str());
}

#ifndef HTTPHANDLERTEST
#define HTTPHANDLERTEST

class HttpHandlerTest : public http::HttpUrlHandler {
public:
    void handler(const http::HttpRequest& resquest, http::HttpResponse& response)
    {
        response.appendHeader("123", "456");
        response.setBody("hello world");
    }
};

#endif

TEST(HttpProcessTest, test7)
{
    string endChar = "\r\n";
    string method = "POST";
    string url = "/home/wjun/1.jpg";
    string version = "HTTP/1.1"; 
    string body = "name=Professionaljax&publisher=Wiley6666444tttgg";
    string headerKey = "Host";
    string headerValue = "img.mukewang.com";
    string header1 = headerKey + "  :  " + headerValue + "  ";
    int contLen = body.size();
    string header2 = "Content-Length:" + to_string(contLen);

    http::HttpRegister::instance().append(url, new HttpHandlerTest());
    
    ostringstream dataStream;
    dataStream << method << " " << url << " " << version << endChar;
    dataStream << header1 << endChar << header2 << endChar;
    dataStream << endChar << body;

    http::HttpProcess hp;
    
    http::HttpParse parser;
    http::HttpProduce producer;
    
    http::HttpReader reader;
    http::HttpWriter writer;

    http::HttpRequest request;
    http::HttpResponse response;
    
    TestDataSource testDataSource(dataStream);
    TestDataDestination dataDst;

    hp.init(&parser, &producer, &reader, &writer, &request, &response, &testDataSource, &dataDst);
    
    while (!testDataSource.isFinish()) {
        hp.processRead();
        if (hp.getIsClose()) {
            break;
        }
    }
    hp.processWrite();

    ostringstream expect;
    int statusCode = 200;
    expect << version << " " << statusCode << " " << http::StateCodeToText::instance().getTitle(statusCode) << endChar;
    body = "hello world";
    expect << CONTENT_LENGTH << ":" << body.size() << endChar;
    expect << "123:456" << endChar;
    expect << endChar << body;

    ASSERT_STREQ(expect.str().c_str(), dataDst.getData().c_str());
}