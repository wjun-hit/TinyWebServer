#include"HttpProduce.hpp"

namespace http {

bool HttpProduce::produceWrite(HTTP_CODE ret, HttpRequest* request, HttpResponse* response)
{
    int statusCode;
    switch (ret) {
    case INTERNAL_ERROR:
        statusCode = 500;
        response->setFromAbnormalStatusCode(statusCode);
        return NEED_TO_CLOSE_SOCKET;
        break;
    
    case BAD_REQUEST:
        statusCode = 400;
        response->setFromAbnormalStatusCode(statusCode);
        return NEED_TO_CLOSE_SOCKET;
        break;
    
    case FORBIDDEN_REQUEST:
        statusCode = 403;
        response->setFromAbnormalStatusCode(statusCode);
        return NEED_TO_CLOSE_SOCKET;
        break;
    
    case GET_REQUEST:
        if (HttpRegister::instance().isExistUrl(request->getUrl())) {
            statusCode = 200;
            response->setStateCode(statusCode);

            HttpUrlHandler* urlHandler = HttpRegister::instance().getHttpUrlHandler(request->getUrl());
            urlHandler->handler(*request, *response);

            if (request->getIsKeepAlive()) {
                response->appendHeaderKeepAlive();
                return KEEP_ALIVE_SOCKET;
            } else {
                return NEED_TO_CLOSE_SOCKET;
            }
        } else {
            statusCode = 404;
            response->setFromAbnormalStatusCode(statusCode);
            return NEED_TO_CLOSE_SOCKET;
        }
        break;

    default:
        break;
    }
    return NEED_TO_CLOSE_SOCKET;
}

}