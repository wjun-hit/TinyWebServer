#include "gtest/gtest.h"
#include"HttpReader.hpp"
#include"HttpParse.hpp"
#include"HttpProcess.hpp"
#include"HttpWriter.hpp"
#include"DataDestination.hpp"
#include"HttpResponse.hpp"
#include<vector>
#include<cstring>
#include<sstream>

using namespace std;

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


TEST(HttpWriterTest, test0)
{
    string version = "HTTP/1.1";
    int status = 200;
    string title = "OK";
    string hk1 = "123";
    string hv1 = "111";
    string hk2 = "567";
    string hv2 = "222"; 

    http::HttpResponse response;
    response.setVersion(version);
    response.setStateCode(status);
    response.appendHeader(hk1, hv1);
    response.appendHeader(hk2, hv2);

    TestDataDestination dataDst;
    http::HttpWriter writer;
    writer.setDataDestination(&dataDst);
    writer.setHttpResponse(&response);

    ostringstream expect;
    expect << version << " " << status << " " << title << "\r\n";
    expect << hk2 << ":" << hv2 << "\r\n";
    expect << hk1 << ":" << hv1 << "\r\n";
    expect << "\r\n";

    writer.write();

    ASSERT_STREQ(expect.str().c_str(), dataDst.getData().c_str());
}

TEST(HttpWriterTest, test1)
{
    string version = "HTTP/1.1";
    int status = 200;
    string title = "OK";
    string hk1 = "123";
    string hv1 = "111";
    string hk2 = "567";
    string hv2 = "222"; 
    string body = "qwertyyy";

    http::HttpResponse response;
    response.setVersion(version);
    response.setStateCode(status);
    response.appendHeader(hk1, hv1);
    response.appendHeader(hk2, hv2);
    response.setBody(body);

    TestDataDestination dataDst;
    http::HttpWriter writer;
    writer.setDataDestination(&dataDst);
    writer.setHttpResponse(&response);

    ostringstream expect;
    expect << version << " " << status << " " << title << "\r\n";
    expect << hk2 << ":" << hv2 << "\r\n";
    expect << hk1 << ":" << hv1 << "\r\n";
    expect << "\r\n" << body;

    writer.write();

    ASSERT_STREQ(expect.str().c_str(), dataDst.getData().c_str());
}

TEST(HttpWriterTest, test2)
{
    string version = "HTTP/1.1";
    int status = 200;
    string title = "OK";
    string hk1 = "123";
    string hv1 = "111";
    string hk2 = "567";
    string hv2 = "222"; 
    string body = "qwertyyy";
    string file = "home/1.jpg";

    http::HttpResponse response;
    response.setVersion(version);
    response.setStateCode(status);
    response.appendHeader(hk1, hv1);
    response.appendHeader(hk2, hv2);
    response.setBody(body);
    response.setFileName(file);

    TestDataDestination dataDst;
    http::HttpWriter writer;
    writer.setDataDestination(&dataDst);
    writer.setHttpResponse(&response);

    ostringstream expect;
    expect << version << " " << status << " " << title << "\r\n";
    expect << hk2 << ":" << hv2 << "\r\n";
    expect << hk1 << ":" << hv1 << "\r\n";
    expect << "\r\n" << body << file;

    writer.write();

    ASSERT_STREQ(expect.str().c_str(), dataDst.getData().c_str());
}