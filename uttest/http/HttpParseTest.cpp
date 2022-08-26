#include "gtest/gtest.h"
#include"HttpReader.hpp"
#include"HttpParse.hpp"
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
    int read(char* text)
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

TEST(HttpParseTest, test0)
{
    http::HttpParse httpParse;
    char text1[] = "123";
    char text2[] = "456";
    char text3[] = "789";
    const char endChar[] = " ";
    string split = "____";
    ostringstream oss, expect, result;
    oss << text1 << endChar << text2 << endChar << text3;
    char text[100];
    strcpy(text, oss.str().c_str());
    char* p = text;

    expect << text1 << split << text2 << split << text3 << split;

    result << httpParse.getNextValue(p, endChar) << split;
    result << httpParse.getNextValue(p, endChar) << split;
    result << p << split;
    ASSERT_STREQ(result.str().c_str(), expect.str().c_str());
}

TEST(HttpParseTest, test1)
{
    http::HttpParse httpParse;
    char text1[] = "123";
    char text2[] = "456";
    char text3[] = "789";
    const char endChar[] = " ";
    string split = "____";
    ostringstream oss, expect, result;
    oss << "   " << text1 << endChar << "   " << text2 << endChar << text3;
    char text[100];
    strcpy(text, oss.str().c_str());
    char* p = text;

    expect << text1 << split << text2 << split << text3 << split;

    result << httpParse.getNextValue(p, endChar) << split;
    result << httpParse.getNextValue(p, endChar) << split;
    result << p << split;
    ASSERT_STREQ(result.str().c_str(), expect.str().c_str());
}


TEST(HttpParseTest, test2)
{
    http::HttpParse httpParse;
    string method = "POST";
    string url = "/home/wjun/1.jpg";
    string version = "HTTP/1.1";
    const char endChar[] = " ";
    
    ostringstream oss;
    oss << method << endChar << url << endChar << version << "\0\0";
    char text[100];
    strcpy(text, oss.str().c_str());
    char* p = text;

    http::HTTP_CODE code = httpParse.parseRequestLine(p);
    ASSERT_EQ(code, http::NO_REQUEST);
    http::HttpRequest* request = httpParse.getHttpRequest();
    
    ASSERT_STREQ(request->getMethod().c_str(), method.c_str());
    ASSERT_STREQ(request->getUrl().c_str(), url.c_str());
    ASSERT_STREQ(request->getVersion().c_str(), version.c_str());
}

TEST(HttpParseTest, test3)
{
    http::HttpParse httpParse;
    string method = "POST1";  //不合法的方法
    string url = "/home/wjun/1.jpg";
    string version = "HTTP/1.1";
    const char endChar[] = " ";

    ostringstream oss;
    oss << method << endChar << url << endChar << version;
    char text[100];
    strcpy(text, oss.str().c_str());
    char* p = text;

    http::HTTP_CODE code = httpParse.parseRequestLine(p);
    ASSERT_EQ(code, http::BAD_REQUEST);
}

TEST(HttpParseTest, test4)
{
    http::HttpParse httpParse;
    string method = "POST";
    string url = "/home/wjun/1.jpg";
    string version = "HTTP/1.0";  //只允许1.1版本
    const char endChar[] = " ";

    ostringstream oss;
    oss << method << endChar << url << endChar << version;
    char text[100];
    strcpy(text, oss.str().c_str());
    char* p = text;

    http::HTTP_CODE code = httpParse.parseRequestLine(p);
    ASSERT_EQ(code, http::BAD_REQUEST);
}

TEST(HttpParseTest, test5)
{
    http::HttpParse httpParse;
    string headerKey = "POST";
    string headerValue = "/home/wjun/1.jpg";
    const char endChar[] = ":";

    ostringstream oss;
    oss << headerKey << endChar << headerValue;
    char text[100];
    strcpy(text, oss.str().c_str());
    char* p = text;

    httpParse.setReader(new http::HttpReader());
    http::HTTP_CODE code = httpParse.parseHeaders(p);
    ASSERT_EQ(code, http::NO_REQUEST);

    http::HttpRequest* request = httpParse.getHttpRequest();
    auto header = request->getHeaders();
    
    ASSERT_EQ(header.size(), 1);

    ASSERT_STREQ(header[headerKey].c_str(), headerValue.c_str());
}

TEST(HttpParseTest, test6)
{
    http::HttpParse httpParse;
    string endChar = "\r\n";
    string body = "name=Professionaljax&publisher=Wiley6666444tttgg";
    string headerKey = "Host";
    string headerValue = "img.mukewang.com";
    string header1 = headerKey + "  :  " + headerValue + "  ";
    int contLen = body.size();
    string header2 = "Content-Length:" + to_string(contLen);

    http::HttpReader reader;
    ostringstream dataStream;
    dataStream << header1 << endChar << header2 << endChar << endChar << body;
    reader.setDataSource(new TestDataSource(dataStream));
    httpParse.setReader(&reader);

    char* line;
    bool isBody = false;
    http::LINE_STATUS lineStatus;
    http::HTTP_CODE code;
    while (reader.readOnce()) {
        while (reader.getData(line, contLen) == http::LINE_OK) {
            if (reader.getIsBody()) {
                code = httpParse.parseContent(line);
            } else {
                code = httpParse.parseHeaders(line);
            }
        }
    }
    http::HttpRequest* request = httpParse.getHttpRequest();
    auto header = request->getHeaders();

    ASSERT_EQ(header.size(), 2);

    ASSERT_STREQ(header[headerKey].c_str(), headerValue.c_str());
    ASSERT_STREQ(header["Content-Length"].c_str(), to_string(contLen).c_str());
    ASSERT_STREQ(request->getBody().c_str(), body.c_str());
}

TEST(HttpParseTest, test7)
{
    http::HttpParse httpParse;
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

    http::HttpReader reader;
    ostringstream dataStream;
    dataStream << method << " " << url << " " << version << endChar;
    dataStream << header1 << endChar << header2 << endChar;
    dataStream << endChar << body;

    reader.setDataSource(new TestDataSource(dataStream));
    httpParse.setReader(&reader);

    http::HTTP_CODE code;
    while (reader.readOnce()) {
        code = httpParse.processRead();
        ASSERT_NE(code, http::BAD_REQUEST);
    }
    ASSERT_EQ(code, http::GET_REQUEST);

    http::HttpRequest* request = httpParse.getHttpRequest();

    ASSERT_STREQ(request->getMethod().c_str(), method.c_str());
    ASSERT_STREQ(request->getUrl().c_str(), url.c_str());
    ASSERT_STREQ(request->getVersion().c_str(), version.c_str());

    auto header = request->getHeaders();
    ASSERT_EQ(header.size(), 2);
    ASSERT_STREQ(header[headerKey].c_str(), headerValue.c_str());
    ASSERT_STREQ(header["Content-Length"].c_str(), to_string(contLen).c_str());

    ASSERT_STREQ(request->getBody().c_str(), body.c_str());
}

// 各字段之间增加空格测试
TEST(HttpParseTest, test8)
{
    http::HttpParse httpParse;
    string endChar = "\r\n";
    string method = "POST";
    string url = "/home/wjun/1.jpg";
    string version = "HTTP/1.1"; 
    string body = "name=Professionaljax&publisher=Wiley6666444tttgg";
    string headerKey = "Host";
    string headerValue = "img.mukewang.com";
    string header1 = headerKey + "  :  " + headerValue + "  ";
    int contLen = body.size();
    string header2 = "Content-Length  :" + to_string(contLen);

    http::HttpReader reader;
    ostringstream dataStream;
    dataStream << method << "   " << url << "   " << version << "  " << endChar;
    dataStream << "  " << header1 << endChar << header2 << endChar;
    dataStream << endChar << body;

    reader.setDataSource(new TestDataSource(dataStream));
    httpParse.setReader(&reader);

    http::HTTP_CODE code;
    while (reader.readOnce()) {
        code = httpParse.processRead();
        ASSERT_NE(code, http::BAD_REQUEST);
    }
    ASSERT_EQ(code, http::GET_REQUEST);

    http::HttpRequest* request = httpParse.getHttpRequest();

    ASSERT_STREQ(request->getMethod().c_str(), method.c_str());
    ASSERT_STREQ(request->getUrl().c_str(), url.c_str());
    ASSERT_STREQ(request->getVersion().c_str(), version.c_str());

    auto header = request->getHeaders();
    ASSERT_EQ(header.size(), 2);
    ASSERT_STREQ(header[headerKey].c_str(), headerValue.c_str());
    ASSERT_STREQ(header["Content-Length"].c_str(), to_string(contLen).c_str());

    ASSERT_STREQ(request->getBody().c_str(), body.c_str());
}

TEST(HttpParseTest, test9)
{
    http::HttpParse httpParse;
    string endChar = "\r\n";
    string method = "GET";
    string url = "/home/wjun/1.jpg";
    string version = "HTTP/1.1"; 
    string headerKey = "Host";
    string headerValue = "img.mukewang.com";
    string header1 = headerKey + "  :  " + headerValue + "  ";

    http::HttpReader reader;
    ostringstream dataStream;
    dataStream << method << " " << url << " " << version << endChar;
    dataStream << header1 << endChar;
    dataStream << endChar;

    reader.setDataSource(new TestDataSource(dataStream));
    httpParse.setReader(&reader);

    http::HTTP_CODE code;
    while (reader.readOnce()) {
        code = httpParse.processRead();
        ASSERT_NE(code, http::BAD_REQUEST);
    }
    ASSERT_EQ(code, http::GET_REQUEST);

    http::HttpRequest* request = httpParse.getHttpRequest();

    ASSERT_STREQ(request->getMethod().c_str(), method.c_str());
    ASSERT_STREQ(request->getUrl().c_str(), url.c_str());
    ASSERT_STREQ(request->getVersion().c_str(), version.c_str());

    auto header = request->getHeaders();
    ASSERT_EQ(header.size(), 1);
    ASSERT_STREQ(header[headerKey].c_str(), headerValue.c_str());
}