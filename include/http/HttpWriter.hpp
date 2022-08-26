#ifndef HTTP_WRITER_HPP
#define HTTP_WRITER_HPP

#include <stdarg.h>
#include <iostream>
#include <cstring>
#include <cstdio>

#include "DataDestination.hpp"
#include "HttpResponse.hpp"

namespace http {

class HttpWriter {
public:
    static const int WRITE_BUFFER_SIZE = 2048;

    void setResponse(HttpResponse* response_);

    bool addLine(const char *format, ...);
    bool addStatusLine();
    bool addHeaders();
    bool addBlankLine();
    bool addBody();
    bool write(DataDestination* dataDestination);
    void writeFinish();

private:
    HttpResponse* response;

    char writeBuf[WRITE_BUFFER_SIZE];
    int writeIdx{ 0 };
};

} // namespace http


#endif