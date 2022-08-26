#include "gtest/gtest.h"
#include"TimedEvent.hpp"
#include<iostream>
#include<algorithm>
#include<queue>
#include"TimedTaskManagerCenter.hpp"

using namespace std;
using namespace timer;

TEST(TimerTest, test0)
{
    TimedTaskManagerCenter tmc;
    tmc.start();
    tmc.appendTask([](){cout<<"123"<<endl;}, 5, true);
    this_thread::sleep_for(std::chrono::seconds(2));
    tmc.appendTask([](){cout<<"456"<<endl;}, 1, true);
    this_thread::sleep_for(std::chrono::seconds(10));
    // while (true);
    tmc.stop();
    this_thread::sleep_for(std::chrono::seconds(5));
}

// TEST(TimerTest, test0)
// {
//     int num = 5;
//     vector<TimedEvent> timedEvents;
//     for (int i = 0; i < num; i++) {
//         timedEvents.push_back(TimedEvent([](){}, 100- 10*i, true));
//     }
//     sort(timedEvents.begin(), timedEvents.end());
//     for (int i = 0; i < num; i++) {
//         ASSERT_EQ(timedEvents[i].durationSec, 110 - num*10 + 10*i);
//         // cout << timedEvents[i].durationSec << " " << timedEvents[i].nextRunTime << endl;
//     }
//     ASSERT_TRUE(true);
// }

// TEST(TimerTest, test1)
// {
//     int num = 5;
//     priority_queue<TimedEvent> pq;
//     for (int i = 0; i < num; i++) {
//         TimedEvent timedEvent([](){}, 100- 10*i, true);
//         // timedEvent.setNextRunTime();
//         pq.push(timedEvent);
//     }

//     for (int i = 0; i < num; i++) {
//         TimedEvent timedEvent = pq.top();
//         pq.pop();
//         ASSERT_EQ(timedEvent.durationSec, 110 - num*10 + 10*i);
//         // cout << timedEvent.durationSec << " " << timedEvent.nextRunTime << endl;
//     }
//     ASSERT_TRUE(true);
// }