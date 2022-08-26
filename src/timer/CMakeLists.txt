cmake_minimum_required(VERSION 3.0.0)

include(${ROOT_DIR}/Common.cmake)

set(TIMER_TARGET timer)
 
aux_source_directory(. TIMER_DIRSRCS)

add_library(${TIMER_TARGET} ${TIMER_DIRSRCS})
target_link_libraries(${TIMER_TARGET} utils)

  