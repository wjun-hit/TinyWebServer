#ifndef HTTP_RESPONSE_HPP
#define HTTP_RESPONSE_HPP

#include <iostream>
#include <unordered_map>

#include "HttpState.hpp"
#include "Log.hpp"
#include "FileSender.hpp"

namespace http {

class HttpResponse {
public:
    void setVersion(const std::string& version_);
    std::string getVersion();

    void setStateCode(int stateCode_);
    int getStateCode();
    std::string getStateTitle();

    void appendHeaderContentLength(int len);
    void appendHeaderKeepAlive();
    void appendHeader(const std::string& headerKey, const std::string& headerValue);
    std::unordered_map<std::string, std::string> getHeaders();
    void setBody(const std::string& body_);

    std::string getBody();
    void appendBody(const std::string& body_);

    void setFileSender(FileSender* fileSender_);
    FileSender* getFileSender();

    void setFromAbnormalStatusCode(int code);

    void reset()
    {
        headers.clear();
        body.clear();
    }

private:
    std::string version {"HTTP/1.1"};
    int stateCode;
    std::string stateTitle;
    std::unordered_map<std::string, std::string> headers;
    std::string body;
    FileSender* fileSender;
};

}

#endif