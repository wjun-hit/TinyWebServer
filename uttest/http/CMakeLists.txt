
include(${ROOT_DIR}/Common.cmake)

set(HTTP_TEST httptest)
 
AUX_SOURCE_DIRECTORY(. DIR_SRC_TESTS)
add_executable(${HTTP_TEST} ${DIR_SRC_TESTS})
target_link_libraries(${HTTP_TEST}  gtest gtest_main gmock gmock_main pthread)
target_link_libraries(${HTTP_TEST}  http utils log)

add_test(
    NAME ${HTTP_TEST}
    COMMAND ${HTTP_TEST}
)
