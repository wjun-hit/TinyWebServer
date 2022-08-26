#ifndef HTTP_READER_HPP
#define HTTP_READER_HPP

#include <iostream>
#include <cstring>

#include "HttpState.hpp"
#include "DataSource.hpp"

namespace http {

class HttpReader {
public:
	static const int READ_BUFFER_SIZE = 2048;

    bool readOnce(DataSource* dataSource);
    void readFinish()
    {
        readIdx = 0;
        checkedIdx = 0;
        startLine = 0;
        isBody = false;
        isBlankLine = false;
    }
    LINE_STATUS parseLine();
    LINE_STATUS getLine(char*& line);
    LINE_STATUS parseBody(int contentLength);
    LINE_STATUS getBody(char*& body, int contentLength);
    LINE_STATUS getData(char*& body, int contentLength = 0);
    bool getIsBody();
    bool getIsBlankLine();

private:
	char readBuf[READ_BUFFER_SIZE];
	int readIdx{ 0 };
	int checkedIdx{ 0 };
    int startLine{ 0 };
    bool isBody {false};
    bool isBlankLine {false};
};

}

#endif