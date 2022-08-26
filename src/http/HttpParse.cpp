#include"HttpParse.hpp"

namespace http {

void HttpParse::setRequest(HttpRequest* request_)
{
    request = request_;
}

char* HttpParse::getNextValue(char*& text, const char* endChar)
{
    text += strspn(text, " \t");   //去掉字符串前面空格
    char* nextValue = text;
    char* tmp = strpbrk(text, endChar);
    if (!tmp) {
        return nextValue;
    }
    text =  tmp;
    *text++ = '\0';
    while (*(--tmp) == ' ') {   //去掉字符串结尾空格
        *tmp = '\0';
    }
    return nextValue;
}

HTTP_CODE HttpParse::parseRequestLine(char* text)
{
    char* method = getNextValue(text, SPACE_END_CHAR);
    request->setMethod(method);
    if (!request->isValidOfMethod()) {
        return BAD_REQUEST;
    }
    char* url = getNextValue(text, SPACE_END_CHAR);
    request->setUrl(url);
    if (!request->isValidOfUrl()) {
        return BAD_REQUEST;
    }
    char* version = getNextValue(text, SPACE_END_CHAR);
    request->setVersion(version);
    if (!request->isValidOfVersion()) {
        return BAD_REQUEST;
    }
    checkState = CHECK_STATE_HEADER;
	return NO_REQUEST;
}

HTTP_CODE HttpParse::parseHeaders(char* text, HttpReader* reader)
{
    if (reader->getIsBlankLine()) {
        if (request->getContentLength() != 0) {
            checkState = CHECK_STATE_CONTENT;
            return NO_REQUEST;
        }
        return GET_REQUEST;
    } else {
        char* headerKey = getNextValue(text, COLON_END_CHAR);
        if (!headerKey) {
            return BAD_REQUEST;
        }
        char* headerValue = getNextValue(text, SPACE_END_CHAR);
        request->appendHeader(headerKey, headerValue);
    }
    return NO_REQUEST;
}

HTTP_CODE HttpParse::parseContent(char* text)
{
    request->setBody(text);
    return GET_REQUEST;
}

HTTP_CODE HttpParse::parseRead(HttpReader* reader)
{
    HTTP_CODE ret = NO_REQUEST;
    char* text = 0;
    LINE_STATUS lineStatus;
    while ((lineStatus = reader->getData(text, request->getContentLength())) == LINE_OK) {
        LOG_INFO("recv text: " << text);
        switch (checkState) {
            case CHECK_STATE_REQUESTLINE: {
                ret = parseRequestLine(text);
                if (ret == BAD_REQUEST)
                    return BAD_REQUEST;
                break;
            }
            case CHECK_STATE_HEADER: {
                ret = parseHeaders(text, reader);
                if (ret == BAD_REQUEST)
                    return BAD_REQUEST;
                else if (ret == GET_REQUEST) {
                    return GET_REQUEST;
                }
                break;
            }
            case CHECK_STATE_CONTENT: {
                ret = parseContent(text);
                if (ret == GET_REQUEST) {
                    return GET_REQUEST;
                }
                break;
            }
            default:
                return INTERNAL_ERROR;
        }
    }
    if (lineStatus == LINE_BAD) {
        return BAD_REQUEST;
    }
    return NO_REQUEST;
}

}