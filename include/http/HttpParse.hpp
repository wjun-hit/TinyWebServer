#ifndef HTTP_PARSE_HPP
#define HTTP_PARSE_HPP

#include <iostream>
#include <sstream>
#include <cstring>

#include "HttpRequest.hpp"
#include "HttpState.hpp"
#include "HttpReader.hpp"

using namespace std;

namespace http {

const char SPACE_END_CHAR[] = " \t";
const char COLON_END_CHAR[] = ":";

class HttpParse {
public:
	void setRequest(HttpRequest* request_);
	HTTP_CODE parseRequestLine(char* text);
	HTTP_CODE parseHeaders(char* text, HttpReader* reader);
	HTTP_CODE parseContent(char* text);
	char* getNextValue(char*& text, const char* endChar);
	HTTP_CODE parseRead(HttpReader* reader);
	void reset()
	{
		checkState = CHECK_STATE_REQUESTLINE;
	}
private:
	CHECK_STATE checkState {CHECK_STATE_REQUESTLINE};

	HttpRequest* request;
};

};

#endif