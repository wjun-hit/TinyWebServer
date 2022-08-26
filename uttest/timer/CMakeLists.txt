
include(${ROOT_DIR}/Common.cmake)

set(TIMER_TEST timertest)
 
AUX_SOURCE_DIRECTORY(. DIR_SRC_TESTS)
add_executable(${TIMER_TEST} ${DIR_SRC_TESTS})
target_link_libraries(${TIMER_TEST}  gtest gtest_main gmock gmock_main pthread)
target_link_libraries(${TIMER_TEST}  http utils log)

add_test(
    NAME ${TIMER_TEST}
    COMMAND ${TIMER_TEST}
)
 