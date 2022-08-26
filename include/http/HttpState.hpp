#ifndef HTTP_STATE_HPP
#define HTTP_STATE_HPP

#include <unordered_map>

namespace http {

#define CONTENT_LENGTH "Content-Length"
#define CONNECTION "Connection"
#define KEEP_ALIVE "keep-alive"
#define CONN_CLOSE "close"

#define NEED_TO_CLOSE_SOCKET true
#define KEEP_ALIVE_SOCKET false

enum LINE_STATUS
{
	LINE_OK = 0,
	LINE_BAD,
	LINE_OPEN
};

enum HTTP_CODE
{
	NO_REQUEST = 0,
	GET_REQUEST,
	BAD_REQUEST,
	NO_RESOURCE,
	FORBIDDEN_REQUEST,
	FILE_REQUEST,
	INTERNAL_ERROR,
	CLOSED_CONNECTION
};

enum CHECK_STATE
{
	CHECK_STATE_REQUESTLINE = 0,
	CHECK_STATE_HEADER,
	CHECK_STATE_CONTENT
};

enum PROCESS_STATUS
{
	CONTINUE = 0,
	FINISH,
	SHUTDOWN
};

class StateCodeToText {
public:
	static StateCodeToText& instance()
	{
		static StateCodeToText ins;
		return ins;
	}
	bool existCode(int code)
	{
		return codeToTitle.find(code) != codeToTitle.end();
	}
	std::string getTitle(int code)
	{
		if (codeToTitle.find(code) != codeToTitle.end()) {
			return codeToTitle[code];
		}
		return "";
	}
	std::string getForm(int code)
	{
		if (codeToForm.find(code) != codeToForm.end()) {
			return codeToForm[code];
		}
		return "";
	}
private:
	StateCodeToText()
	{
		codeToTitle[200] = "OK";

		codeToTitle[400] = "Bad Request";
		codeToForm[400] = "Your request has bad syntax or is inherently impossible to staisfy.\n";

		codeToTitle[403] = "Forbidden";
		codeToForm[403] = "You do not have permission to get file form this server.\n";

		codeToTitle[404] = "Not Found";
		codeToForm[404] = "The requested file was not found on this server.\n";

		codeToTitle[500] = "Internal Error";
		codeToForm[500] = "There was an unusual problem serving the request file.\n";
	}
	std::unordered_map<int, std::string> codeToTitle;
	std::unordered_map<int, std::string> codeToForm;
};

}

#endif // !HTTPSTATE
