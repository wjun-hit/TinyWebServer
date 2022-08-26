#ifndef FACTORY_FILE_SENDER_HPP
#define FACTORY_FILE_SENDER_HPP

#include"FileSender.hpp"
#include<unordered_map>

class FactoryFileSender {
public:
    static FactoryFileSender& instance()
    {
        static FactoryFileSender ins;
        return ins;
    }
    ~FactoryFileSender()
    {
        for (auto urlSender : mapUrlFileSender) {
            delete urlSender.second;
        }
        mapUrlFileSender.clear();
    }
    std::string getFileType(const std::string& url)
    {
        return "html";
    }
    FileSender* getFileSender(const std::string& url)
    {
        if (getFileType(url) == "html") {
            if (mapUrlFileSender.find(url) != mapUrlFileSender.end()) {
                return mapUrlFileSender[url];
            }
            FileSender * sender = new HtmlFileSender(url);
            mapUrlFileSender[url] = sender;
            return sender;
        }
        return nullptr;
    }
private:
    std::unordered_map<std::string, FileSender*> mapUrlFileSender;
};


#endif