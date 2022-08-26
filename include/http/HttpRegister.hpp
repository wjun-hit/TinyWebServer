#ifndef HTTP_REGISTER_HPP
#define HTTP_REGISTER_HPP

#include <iostream>
#include <unordered_map>

#include "HttpUrlHandler.hpp"

namespace http {

class HttpRegister {
public:
    static HttpRegister& instance()
    {
        static HttpRegister reg;
        return reg;
    }
    bool isExistUrl(std::string url)
    {
        return registerCentre.find(url) != registerCentre.end();
    }
    void append(const std::string& url, HttpUrlHandler* handler)
    {
        registerCentre[url] = handler;
    }
    HttpUrlHandler* getHttpUrlHandler(const std::string& url)
    {
        if (isExistUrl(url)) {
            return registerCentre[url];
        }
        return nullptr;
    }
private:
    HttpRegister(){}  

private:
    std::unordered_map<std::string, HttpUrlHandler*> registerCentre;
};

}

#endif