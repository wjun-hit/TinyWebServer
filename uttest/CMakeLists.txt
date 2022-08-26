cmake_minimum_required(VERSION 3.0.0)

add_subdirectory(http) 
add_subdirectory(threadpool) 
add_subdirectory(timer) 
add_subdirectory(socket) 
add_subdirectory(server) 

include(${ROOT_DIR}/Common.cmake)

set(GTEST test)


AUX_SOURCE_DIRECTORY(. DIR_SRC_TESTS)
add_executable(${GTEST} ${DIR_SRC_TESTS})

target_link_libraries(${GTEST}  gtest gtest_main gmock gmock_main pthread)
target_link_libraries(${GTEST}  http utils log)
 