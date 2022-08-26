
include(${ROOT_DIR}/Common.cmake)

set(SERVER_TEST servertest)
 
AUX_SOURCE_DIRECTORY(. DIR_SRC_TESTS)
add_executable(${SERVER_TEST} ${DIR_SRC_TESTS})
target_link_libraries(${SERVER_TEST}  gtest gtest_main gmock gmock_main pthread)
target_link_libraries(${SERVER_TEST}  http utils log)

add_test(
    NAME ${SERVER_TEST}
    COMMAND ${SERVER_TEST}
)
