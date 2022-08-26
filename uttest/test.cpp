#include<iostream>
#include"gtest/gtest.h"
// #include"http/HttpParseTest.cpp"
// #include"http/HttpReaderTest.cpp"
// #include"http/HttpWriterTest.cpp"
#include"http/HttpProcessTest.cpp"

using namespace std;

int main()
{
    testing::InitGoogleTest();
    if(RUN_ALL_TESTS()){}
    return 0;
}