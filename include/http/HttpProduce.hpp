#ifndef HTTP_PRODUCE_HPP
#define HTTP_PRODUCE_HPP

#include <iostream>

#include "HttpResponse.hpp"
#include "HttpRequest.hpp"
#include "HttpState.hpp"
#include "HttpUrlHandler.hpp"
#include "HttpRegister.hpp"

namespace http {

class HttpProduce {
public:
    bool produceWrite(HTTP_CODE ret, HttpRequest* request, HttpResponse* response);

private:
};

}

#endif