
include(${ROOT_DIR}/Common.cmake)

set(SOCKET_TEST sockettest)
 
AUX_SOURCE_DIRECTORY(. DIR_SRC_TESTS)
add_executable(${SOCKET_TEST} ${DIR_SRC_TESTS})
target_link_libraries(${SOCKET_TEST}  gtest gtest_main gmock gmock_main pthread)
target_link_libraries(${SOCKET_TEST}  http utils log)

add_test(
    NAME ${SOCKET_TEST}
    COMMAND ${SOCKET_TEST}
)
