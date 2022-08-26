#include"HttpWriter.hpp"

namespace http {

void HttpWriter::setResponse(HttpResponse* response_)
{
    response = response_;
}

bool HttpWriter::addLine(const char *format, ...)
{
    if (writeIdx >= WRITE_BUFFER_SIZE) {
        return false;
    }
    va_list args;
    va_start(args, format);
    int len = vsnprintf(writeBuf + writeIdx, WRITE_BUFFER_SIZE - 1 - writeIdx, format, args);
    if (len >= (WRITE_BUFFER_SIZE - 1 - writeIdx)) {
        va_end(args);
        return false;
    }
    LOG_INFO("write text: " << writeBuf + writeIdx);
    writeIdx += len;
    va_end(args);

    return true;
}

bool HttpWriter::addStatusLine()
{
    return addLine("%s %d %s\r\n", response->getVersion().c_str(), response->getStateCode(), response->getStateTitle().c_str());
}

bool HttpWriter::addHeaders()
{
    bool ret = true;
    auto headers = response->getHeaders();
    for (auto& header : headers) {
        ret = ret && addLine("%s:%s\r\n", header.first.c_str(), header.second.c_str());
    }
    return ret;
}

bool HttpWriter::addBlankLine()
{
    return addLine("%s", "\r\n");
}

bool HttpWriter::addBody()
{
    std::string body = response->getBody();
    if (body.size() > 0) {
        return addLine("%s", body.c_str());
    }
    return true;
}

bool HttpWriter::write(DataDestination* dataDestination)
{
    addStatusLine();
    addHeaders();
    addBlankLine();
    addBody();

    return dataDestination->write(writeBuf, response->getFileSender());
}

void HttpWriter::writeFinish()
{
    writeIdx = 0;
}

}