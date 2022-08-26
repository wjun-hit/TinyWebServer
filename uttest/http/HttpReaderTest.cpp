#include "gtest/gtest.h"
#include"HttpReader.hpp"
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

TEST(HttpReaderTest, test0)
{
    string split = "____";
    string endChar = "\r\n";
    string requestLine = "GET /root/wjun/1.jpg HTTP/1.1";
    string header1 = "Host:img.mukewang.com";
    string header2 = "Accept-Language:zh-CN";
    string blankLine = "\0";

    ostringstream expect, result;
    expect << requestLine << split << header1 << split << header2 << split << blankLine << split;
    
    http::HttpReader reader;
    ostringstream dataStream;
    dataStream << requestLine << endChar << header1 << endChar << header2 << endChar << endChar;
    reader.setDataSource(new TestDataSource(dataStream));

    char* line;
    while (reader.readOnce()) {
        while (reader.getLine(line) == http::LINE_OK) {
            result << line << split;
        }
    }
    ASSERT_STREQ(result.str().c_str(), expect.str().c_str());
}

TEST(HttpReaderTest, test1)
{
    string split = "____";
    string endChar = "\r\n";
    string requestLine = "POST /root/wjun/1.jpg HTTP/1.1";
    string body = "name=Professionaljax&publisher=Wiley";
    string header1 = "Host:img.mukewang.com";
    int contLen = body.size();
    string header2 = "Content-Length:" + to_string(contLen);
    string blankLine = "\0";

    ostringstream expect, result;
    expect << requestLine << split << header1 << split << header2 << split << blankLine << split << body << split;
    
    http::HttpReader reader;
    ostringstream dataStream;
    dataStream << requestLine << endChar << header1 << endChar << header2 << endChar << endChar << body;
    reader.setDataSource(new TestDataSource(dataStream));

    char* line;
    bool isBody = false;
    http::LINE_STATUS lineStatus;
    while (reader.readOnce()) {
        while ((lineStatus = (isBody ? reader.getBody(line, contLen) : reader.getLine(line))) == http::LINE_OK) {
            result << line << split;
            if (line[0] == '\0') {
                isBody = true;
            }
        }
    }
    ASSERT_STREQ(result.str().c_str(), expect.str().c_str());
}

TEST(HttpReaderTest, test2)
{
    string split = "____";
    string endChar = "\r\n";
    string requestLine = "123456789\r/wjun/1.jpg HTTP/1.1";
    string header1 = "Host:img.mukewang.com";
    string header2 = "Accept-Language:zh-CN";
    string blankLine = "\0";

    ostringstream expect, result;
    expect << requestLine << split << header1 << split << header2 << split << blankLine << split;
    
    http::HttpReader reader;
    ostringstream dataStream;
    dataStream << requestLine << endChar << header1 << endChar << header2 << endChar << endChar;
    reader.setDataSource(new TestDataSource(dataStream));

    char* line;
    http::LINE_STATUS lineStatus;
    while (reader.readOnce()) {
        while ((lineStatus = reader.getLine(line)) == http::LINE_OK) {
            result << line << split;
        }
        if (lineStatus == http::LINE_BAD) {
            ASSERT_TRUE(true);
            return ;
        }
    }
    ASSERT_TRUE(false);
}

TEST(HttpReaderTest, test3)
{
    string split = "____";
    string endChar = "\r\n";
    string requestLine = "POST /root/wjun/1.jpg HTTP/1.1";
    string body = "name=Professionaljax&publisher=Wiley";
    string header1 = "Host:img.mukewang.com";
    int contLen = body.size() + 1;
    string header2 = "Content-Length:" + to_string(contLen);
    string blankLine = "\0";

    ostringstream expect, result;
    // 若Content-Length比实际的body大，会导致读不到body
    expect << requestLine << split << header1 << split << header2 << split << blankLine << split;
    
    http::HttpReader reader;
    ostringstream dataStream;
    dataStream << requestLine << endChar << header1 << endChar << header2 << endChar << endChar << body;
    reader.setDataSource(new TestDataSource(dataStream));

    char* line;
    bool isBody = false;
    http::LINE_STATUS lineStatus;
    while (reader.readOnce()) {
        while ((lineStatus = (isBody ? reader.getBody(line, contLen) : reader.getLine(line))) == http::LINE_OK) {
            result << line << split;
            if (line[0] == '\0') {
                isBody = true;
            }
        }
    }
    ASSERT_STREQ(result.str().c_str(), expect.str().c_str());
}

TEST(HttpReaderTest, test4)
{
    string split = "____";
    string endChar = "\r\n";
    string requestLine = "POST /root/wjun/1.jpg HTTP/1.1";
    string body = "name=Professionaljax&publisher=Wiley";
    string header1 = "Host:img.mukewang.com";
    int contLen = body.size() - 1;
    string header2 = "Content-Length:" + to_string(contLen);
    string blankLine = "\0";

    ostringstream expect, result;
    expect << requestLine << split << header1 << split << header2 << split << blankLine << split << body << split;
    
    http::HttpReader reader;
    ostringstream dataStream;
    dataStream << requestLine << endChar << header1 << endChar << header2 << endChar << endChar << body;
    reader.setDataSource(new TestDataSource(dataStream));

    char* line;
    bool isBody = false;
    http::LINE_STATUS lineStatus;
    while (reader.readOnce()) {
        while ((lineStatus = (isBody ? reader.getBody(line, contLen) : reader.getLine(line))) == http::LINE_OK) {
            result << line << split;
            if (line[0] == '\0') {
                isBody = true;
            }
        }
        if (lineStatus == http::LINE_BAD) {
            ASSERT_TRUE(true);
            return ;
        }
    }
    ASSERT_TRUE(false);
}

TEST(HttpReaderTest, test5)
{
    string split = "____";
    string endChar = "\r\n";
    string requestLine = "GET /root/wjun/1.jpg HTTP/1.1";
    string header1 = "Host:img.mukewang.com";
    string header2 = "Accept-Language:zh-CN";
    string blankLine = "\0";

    ostringstream expect, result;
    expect << requestLine << split << header1 << split << header2 << split << blankLine << split;
    
    http::HttpReader reader;
    ostringstream dataStream;
    dataStream << requestLine << endChar << header1 << endChar << header2 << endChar << endChar;
    reader.setDataSource(new TestDataSource(dataStream));

    char* line;
    while (reader.readOnce()) {
        while (reader.getData(line) == http::LINE_OK) {
            result << line << split;
        }
    }
    ASSERT_STREQ(result.str().c_str(), expect.str().c_str());
}

TEST(HttpReaderTest, test6)
{
    string split = "____";
    string endChar = "\r\n";
    string requestLine = "POST /root/wjun/1.jpg HTTP/1.1";
    string body = "name=Professionaljax&publisher=Wiley";
    string header1 = "Host:img.mukewang.com";
    int contLen = body.size();
    string header2 = "Content-Length:" + to_string(contLen);
    string blankLine = "\0";

    ostringstream expect, result;
    expect << requestLine << split << header1 << split << header2 << split << blankLine << split << body << split;
    
    http::HttpReader reader;
    ostringstream dataStream;
    dataStream << requestLine << endChar << header1 << endChar << header2 << endChar << endChar << body;
    reader.setDataSource(new TestDataSource(dataStream));

    char* line;
    bool isBody = false;
    http::LINE_STATUS lineStatus;
    while (reader.readOnce()) {
        while (reader.getData(line, contLen) == http::LINE_OK) {
            result << line << split;
        }
    }
    ASSERT_STREQ(result.str().c_str(), expect.str().c_str());
}

TEST(HttpReaderTest, test7)
{
    string split = "____";
    string endChar = "\r\n";
    string requestLine = "POST /root/wjun/1.jpg HTTP/1.1";
    string body = "name=Professionaljax&publisher=Wiley6666444tttgg";
    string header1 = "Host:img.mukewang.com";
    int contLen = body.size();
    string header2 = "Content-Length:" + to_string(contLen);
    string blankLine = "\0";

    ostringstream expect, result;
    expect << requestLine << split << header1 << split << header2 << split << blankLine << split << body << split << split;
    
    http::HttpReader reader;
    ostringstream dataStream;
    dataStream << requestLine << endChar << header1 << endChar << header2 << endChar << endChar << body;
    reader.setDataSource(new TestDataSource(dataStream));

    char* line;
    bool isBody = false;
    http::LINE_STATUS lineStatus;
    while (reader.readOnce()) {
        while (reader.getData(line, contLen) == http::LINE_OK) {
            result << line << split;
            if (reader.getIsBody()) {
                result << split;
            }
        }
    }
    ASSERT_STREQ(result.str().c_str(), expect.str().c_str());
}