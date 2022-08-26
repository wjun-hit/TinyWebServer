#include"HttpRequest.hpp"

namespace http {

void HttpRequest::reset()
{
    headers.clear();
    body.clear();
}

void HttpRequest::setMethod(char* method_)
{
    if (method_ != nullptr) {
        method = method_;
    }
}

std::string HttpRequest::getMethod()
{
    return method;
}

bool HttpRequest::isValidOfMethod()
{
    if (method == "GET" || method == "POST") {
        return true;
    }
    return false;
}

void HttpRequest::setUrl(char* url_)
{
    if (url_ != nullptr) {
        url = url_;
    }
}

std::string HttpRequest::getUrl()
{
    return url;
}

bool HttpRequest::isValidOfUrl()
{
    if (url.size() > 0) {
        return true;
    }
    return false;
}

void HttpRequest::setVersion(char* version_)
{
    if (version_ != nullptr) {
        version = version_;
    }
}

std::string HttpRequest::getVersion()
{
    return version;
}

bool HttpRequest::isValidOfVersion()
{
    if (version == "HTTP/1.1" || version == "HTTP/1.0") {
        return true;
    }
    return false;
}

void HttpRequest::appendHeader(char* headerKey_, char* headerValue_)
{
    if (headerKey_ != nullptr && headerValue_ != nullptr) {
        std::string headerKey = headerKey_;
        std::string headerValue = headerValue_;
        headers[headerKey] = headerValue;
    } 
}

bool HttpRequest::getIsKeepAlive()
{
    return (headers.find(CONNECTION) != headers.end()) && (headers[CONNECTION] == KEEP_ALIVE);
}

int HttpRequest::getContentLength()
{
    if (headers.find(CONTENT_LENGTH) == headers.end()) {
        return 0;
    }
    return std::stoi(headers[CONTENT_LENGTH]);
}

std::unordered_map<std::string, std::string> HttpRequest::getHeaders()
{
    return headers;
}

void HttpRequest::setBody(char* body_)
{
    body = body_;
}

std::string HttpRequest::getBody()
{
    return body;
}

std::string HttpRequest::toString() const
{
    std::ostringstream oss;
    oss << "method: " << method << std::endl;
    oss << "url: " << url << std::endl;
    oss << "version: " << version << std::endl;
    for (auto& header : headers) {
        oss << header.first << ": " << header.second << std::endl;
    }
    if (body.size() > 0) {
        oss << "body: " << body << std::endl;
    }
    return oss.str();
}

}