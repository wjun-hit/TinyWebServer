#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include <sstream>
#include <unordered_map>

#include "HttpState.hpp"

namespace http {

class HttpRequest {
public:
	void reset();

	void setMethod(char* method_);
	std::string getMethod();
	bool isValidOfMethod();

	void setUrl(char* url_);
	std::string getUrl();
	bool isValidOfUrl();

	void setVersion(char* version_);
	std::string getVersion();
	bool isValidOfVersion();

	void appendHeader(char* headerKey_, char* headerValue_);
	int getContentLength();
	std::unordered_map<std::string, std::string> getHeaders();

	bool getIsKeepAlive();

	void setBody(char* body_);
	std::string getBody();

	std::string toString() const;

private:
	std::string method;
	std::string url;
	std::string version;
	std::unordered_map<std::string, std::string> headers;
	std::string body;
};

}

#endif