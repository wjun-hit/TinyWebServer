cmake_minimum_required(VERSION 3.0.0)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_STANDARD 17)

project(TinyWeb VERSION 0.1.0)

set(ROOT_DIR ${CMAKE_SOURCE_DIR})
ADD_DEFINITIONS(-D_ROOT_DIR=\"${CMAKE_SOURCE_DIR}\")
ADD_DEFINITIONS(-D_START_LOG=1)

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set (LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

message("编译后可执行程序目录: " ${EXECUTABLE_OUTPUT_PATH})
message("编译后库程序文件目录: " ${LIBRARY_OUTPUT_PATH})

add_subdirectory(src) 
  
# add_subdirectory(uttest) 
   