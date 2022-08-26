#include"HttpResponse.hpp"

namespace http {

void HttpResponse::setVersion(const std::string& version_)
{
    version = version_;
}

std::string HttpResponse::getVersion()
{
    return version;
}

void HttpResponse::setStateCode(int stateCode_)
{
    if (StateCodeToText::instance().existCode(stateCode_)) {
        stateCode = stateCode_;
        stateTitle = StateCodeToText::instance().getTitle(stateCode_);
    }
}

int HttpResponse::getStateCode()
{
    return stateCode;
}

std::string HttpResponse::getStateTitle()
{
    return stateTitle;
}

void HttpResponse::appendHeaderContentLength(int len)
{
    headers[CONTENT_LENGTH] = std::to_string(len);
}

void HttpResponse::appendHeaderKeepAlive()
{
    headers[CONNECTION] = KEEP_ALIVE;
}

void HttpResponse::appendHeader(const std::string& headerKey, const std::string& headerValue)
{
    headers[headerKey] = headerValue;
}

std::unordered_map<std::string, std::string> HttpResponse::getHeaders()
{
    return headers;
}

void HttpResponse::setBody(const std::string& body_)
{
    body = body_;
    appendHeaderContentLength(body.size());
}

std::string HttpResponse::getBody()
{
    return body;
}

void HttpResponse::appendBody(const std::string& body_)
{
    body += body_;
    appendHeaderContentLength(body.size());
}

void HttpResponse::setFileSender(FileSender* fileSender_)
{
    fileSender = fileSender_;
    appendHeaderContentLength(fileSender->getFileSize());
}

FileSender* HttpResponse::getFileSender()
{
    return fileSender;
}

void HttpResponse::setFromAbnormalStatusCode(int code)
{
    stateCode = code;
    stateTitle = StateCodeToText::instance().getTitle(code);
    body = StateCodeToText::instance().getForm(code);
    headers[CONTENT_LENGTH] = std::to_string(body.size());
    headers[CONNECTION] = CONN_CLOSE;
}

}