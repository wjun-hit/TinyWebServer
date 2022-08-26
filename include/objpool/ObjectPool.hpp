#ifndef OBJECT_POOL_HPP
#define OBJECT_POOL_HPP

#include <functional>
#include <unordered_set>

#include "BlockQueue.hpp"

template<class Object>
class ObjectPool {
public:
    using CreateObject = std::function<Object*()>;
    ObjectPool()
    {}
    ~ObjectPool()
    {
        blockQueue.stop();
        for (auto objectPtr : libObject) {
            delete objectPtr;
        }
        libObject.clear();
    }
    void init(int queueNum_, CreateObject createObject_, int objectNum_ = 10000)
    {
        objectNum = objectNum_;
        createObject = createObject_;

        blockQueue.init(queueNum_, objectNum_);

        libObject.clear();
        Object* object;
        for (int i = 0; i < objectNum; i++) {
            object = createObject();
            blockQueue.pushTask(object);
            libObject.insert(object);
        }
    }
    void incObject(int incNum)
    {
        Object* object;
        for (int i = 0; i < incNum; i++) {
            object = createObject();
            blockQueue.pushTask(object);
            libObject.insert(object);
            objectNum++;
        }
    }
    void decObject(int decNum)
    {
        Object* object;
        for (int i = 0; i < decNum; i++) {
            blockQueue.popTask(object);
            libObject.erase(object);
            delete object;
            objectNum--;
        }
    }
    Object* getObject()
    {
        Object* object = nullptr;
        blockQueue.popTask(object);
        return object;
    }
    void returnObject(Object* object)
    {
        blockQueue.pushTask(object);
    }
    int size()
    {
        return blockQueue.size();
    }
private:
    utils::BlockQueue<Object*> blockQueue;
    std::unordered_set<Object*> libObject;
    int objectNum;
    CreateObject createObject;
};

#endif