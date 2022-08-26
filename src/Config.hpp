#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <json/json.h>
#include <iostream>

class Config {
public:
    Config(std::string configFileName)
    {
        Json::Reader reader;
        Json::Value value;
        ifstream configFile(_ROOT_DIR + std::string("/config.json"), ios::binary);
        if (!configFile.is_open())
        {
            std::cout << "Fail to open config.json" << std::endl;
            return ;
        }
        if (reader.parse(configFile, value)) {
            if (value["server"].type() != Json::nullValue) {
                Json::Value jsonServer = value["server"];
                if (jsonServer["threadNum"].type() != Json::nullValue) {
                    server.threadNum = jsonServer["threadNum"].asInt();
                }
                if (jsonServer["maxClientNum"].type() != Json::nullValue) {
                    server.maxClientNum = jsonServer["maxClientNum"].asInt();
                }
                if (jsonServer["port"].type() != Json::nullValue) {
                    server.port = jsonServer["port"].asInt();
                }
                if (jsonServer["timeSlot"].type() != Json::nullValue) {
                    server.timeSlot = jsonServer["timeSlot"].asInt();
                    
                }
                if (jsonServer["listenTrigmode"].type() != Json::nullValue) {
                    if (jsonServer["listenTrigmode"].asString() == "ET") {
                        server.listenTrigmode = true;
                    } else {
                        server.listenTrigmode = false;
                    }
                }
                if (jsonServer["clientTrigmode"].type() != Json::nullValue) {
                    if (jsonServer["clientTrigmode"].asString() == "ET") {
                        server.clientTrigmode = true;
                    } else {
                        server.clientTrigmode = false;
                    }
                }
            }
            if (value["log"].type() != Json::nullValue) {
                Json::Value jsonLog = value["log"];
                if (jsonLog["logDir"].type() != Json::nullValue) {
                    log.logDir = _ROOT_DIR + std::string("/") + jsonLog["logDir"].asString();
                }
                if (jsonLog["isOpenLog"].type() != Json::nullValue) {
                    if (jsonLog["isOpenLog"].asString() == "true") {
                        log.isOpenLog = true;
                    } else {
                        log.isOpenLog = false;
                    }
                }  
                if (jsonLog["splitLine"].type() != Json::nullValue) {
                    log.splitLine = jsonLog["splitLine"].asInt();
                    
                }
                if (jsonLog["queueNum"].type() != Json::nullValue) {
                    log.queueNum = jsonLog["queueNum"].asInt();
                    
                }
                if (jsonLog["maxQueueSize"].type() != Json::nullValue) {
                    log.maxQueueSize = jsonLog["maxQueueSize"].asInt();
                }
            }     
        }
    }
    void print()
    {
        std::cout << "server: " << std::endl;
        std::cout << "  threadNum: " << server.threadNum << std::endl;
        std::cout << "  maxClientNum: " << server.maxClientNum << std::endl;
        std::cout << "  port: " << server.port << std::endl;
        std::cout << "  timeSlot: " << server.timeSlot << std::endl;
        std::cout << "  listenTrigmode: " << server.listenTrigmode << std::endl;
        std::cout << "  clientTrigmode: " << server.clientTrigmode << std::endl;

        std::cout << " log: " << std::endl;
        std::cout << "  isOpenLog: " << log.isOpenLog << std::endl;
        std::cout << "  logDir: " << log.logDir << std::endl;
        std::cout << "  splitLine: " << log.splitLine << std::endl;
        std::cout << "  queueNum: " << log.queueNum << std::endl;
        std::cout << "  maxQueueSize: " << log.maxQueueSize << std::endl;
    }
    struct {
        bool isOpenLog {true};
        std::string logDir {_ROOT_DIR + std::string("/log")};
        int splitLine {100000};
        int queueNum {8};
        int maxQueueSize {100000};
    } log;
    struct {
        bool listenTrigmode {true}; 
        bool clientTrigmode {true};  
        int threadNum {8};   
        int maxClientNum {10000}; 
        int port {6666};   
        int timeSlot {5}; 
    } server;
};

#endif