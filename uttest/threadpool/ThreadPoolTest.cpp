#include "gtest/gtest.h"
#include"HttpReader.hpp"
#include"HttpParse.hpp"
#include"HttpProcess.hpp"
#include"HttpState.hpp"
#include"ThreadPool.hpp"
// #include"TaskQueue.hpp"
// #include"TaskQueueAllToOne.hpp"
// #include"TaskQueueOneToOne.hpp"
// #include"TaskQueueOneToOneVec.hpp"
// #include"TaskQueueAllLockToOne.hpp"
#include<vector>
#include<cstring>
#include<sstream>
#include<ctime>
#include<unordered_set>
#include<ctime>
#include <cstdio>
#include<sstream>
#include <chrono>
#include"ExactTime.hpp"
#include"Log.hpp"
#include"BlockQueue.hpp"
// #include <windows.h>

using namespace std;


class Foo {
public:
    Foo(){}
    void f1()
    {
        // cout << std::this_thread::get_id() << " " << x << endl;
        // testString();
        LOG_INFO("x:" << x);
        LOG_INFO("x1:" << x);
        // x = g--;
        // x = g.fetch_add(1);
        x++;
        int n = 0;
        for (int i = 0; i < 10000; i++) {
            n++;
        }
    }
    int x{0};
};


TEST(ThreadPool, test0)
{
    utils::ExactTime e;
    cout << e.toString() << endl;
    Log::instance().init("/home/wjun/code/tinyWeb/log");
    int taskSize = 1000;
    int threadNum = 8;
    LOG_INFO("12345");
    // Log::instance().flush();

    LOG_INFO("12345: " << threadNum);
    // Log::instance().flush();

    LOG_INFO("12345: " << threadNum+1);
    // Log::instance().flush();
    this_thread::sleep_for(std::chrono::seconds(1));
    return ;

    clock_t start, end;

    Foo f;
    std::vector<Foo> foo(taskSize);
    for (int i = 0; i < taskSize; i++) {
        foo[i].x = i;
    }
    // // using Task = std::function<void()>;
    // // TaskQueue<Task>* tq = new TaskQueueAllToOne<Task>(taskSize);
    // // TaskQueue<Task>* tq = new TaskQueueAllLockToOne<Task>(taskSize);
    // // TaskQueue<Task>* tq = new TaskQueueOneToOne<Task>(threadNum, 10000);
    // // TaskQueue* tq = new TaskQueueOneToOneVec(threadNum, 10000);
    // // BlockQueue<Task>* tq = new BlockQueue<Task>(threadNum, 1000000);
    ThreadPool pool(threadNum);
    // // pool.setTaskQueue(tq);
    pool.start();

    start = clock();
    for (int i = 0; i < taskSize; i++) {
        if (!pool.addTask(std::bind(&Foo::f1, &foo[i]))) {
            i--;
        }
        // if (!pool.addTask([&foo, i](){foo[i].f1();}, i%threadNum)) i--;
        // for (int j = 0; j < 10; j++) f.f1();
    }
    while (pool.size() > 0) ;
    // while(!Log::instance().isFinish());
    end = clock();
    pool.stop();
    utils::ExactTime e1;
    cout << e1.toString() << endl;
    cout << "taskSize: " << taskSize << "  threadNum: " << threadNum << " cost time: " << (end - start)/10000 << "ms" << endl;

    unordered_set<int> uset;
    for (int i = 0; i < taskSize; i++) {
        uset.insert(foo[i].x);
    }
    int res = uset.size();
    ASSERT_EQ(res, taskSize);
    this_thread::sleep_for(std::chrono::seconds(1));
}