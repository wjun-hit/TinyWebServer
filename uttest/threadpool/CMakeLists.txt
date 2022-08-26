
include(${ROOT_DIR}/Common.cmake)

set(THREAD_TEST threadtest)
 
AUX_SOURCE_DIRECTORY(. DIR_SRC_TESTS)
add_executable(${THREAD_TEST} ${DIR_SRC_TESTS})
target_link_libraries(${THREAD_TEST}  gtest gtest_main gmock gmock_main pthread)
target_link_libraries(${THREAD_TEST}  http utils log)

add_test(
    NAME ${THREAD_TEST}
    COMMAND ${THREAD_TEST}
)
