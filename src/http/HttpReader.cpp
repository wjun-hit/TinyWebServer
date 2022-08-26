#include"HttpReader.hpp"

namespace http {

bool HttpReader::readOnce(DataSource* dataSource)
{
    if (readIdx >= READ_BUFFER_SIZE) {
        return false;
    }
    int bytesRead = 0;
    bytesRead = dataSource->read(readBuf + readIdx, READ_BUFFER_SIZE - readIdx);
    if (bytesRead <= 0) {
        return false;
    }
    readIdx += bytesRead;
    return true;
}

LINE_STATUS HttpReader::parseLine()
{
    char temp;
    for (; checkedIdx < readIdx; ++checkedIdx) {
        temp = readBuf[checkedIdx];
        if (temp == '\r') {
            if ((checkedIdx + 1) == readIdx)
                return LINE_OPEN;
            else if (readBuf[checkedIdx + 1] == '\n') {
                readBuf[checkedIdx++] = '\0';
                readBuf[checkedIdx++] = '\0';
                return LINE_OK;
            }
            return LINE_BAD;
        }
        else if (temp == '\n') {
            if (checkedIdx > 1 && readBuf[checkedIdx - 1] == '\r') {
                readBuf[checkedIdx - 1] = '\0';
                readBuf[checkedIdx++] = '\0';
                return LINE_OK;
            }
            return LINE_BAD;
        }
    }
    return LINE_OPEN;
}

LINE_STATUS HttpReader::getLine(char*& line)
{
    LINE_STATUS lineStatus = parseLine();
    if (lineStatus == LINE_OK) {
        line = readBuf + startLine;
        startLine = checkedIdx;
    }
    return lineStatus;
}

LINE_STATUS HttpReader::parseBody(int contentLength)
{
    if (readIdx >= (contentLength + checkedIdx)) {
        if (readIdx != checkedIdx + contentLength) {
            return LINE_BAD;
        }
        checkedIdx += contentLength;
        readBuf[checkedIdx] = '\0';
        return LINE_OK;
    }
    return LINE_OPEN;
}

LINE_STATUS HttpReader::getBody(char*& body, int contentLength)
{
    LINE_STATUS lineStatus = parseBody(contentLength);
    if (lineStatus == LINE_OK) {
        body = readBuf + startLine;
        startLine = checkedIdx;
    }
    return lineStatus;
}

LINE_STATUS HttpReader::getData(char*& text, int contentLength)
{
    if (!isBlankLine) {
        LINE_STATUS lineStatus =  getLine(text);
        if (lineStatus == LINE_OK && text[0] == '\0') {
            isBlankLine = true;
        }
        return lineStatus;
    } else if (contentLength > 0) {
        isBody = true;
        return getBody(text, contentLength);
    } else {
        return LINE_OPEN;
    }
}

bool HttpReader::getIsBody()
{
    return isBody;
}

bool HttpReader::getIsBlankLine()
{
    return isBlankLine;
}

}