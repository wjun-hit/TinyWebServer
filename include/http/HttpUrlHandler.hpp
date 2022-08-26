#ifndef HTTP_URL_HANDLER_HPP
#define HTTP_URL_HANDLER_HPP

#include <HttpResponse.hpp>
#include <HttpRequest.hpp>

namespace http {

class HttpUrlHandler {
public:
    HttpUrlHandler(){}
    virtual void handler(const HttpRequest& resquest, HttpResponse& response) = 0;
};

}

#endif