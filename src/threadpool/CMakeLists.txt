cmake_minimum_required(VERSION 3.0.0)

include(${ROOT_DIR}/Common.cmake)

set(THREAD_TARGET threadpool)
 
aux_source_directory(. THREAD_DIRSRCS)
 
add_library(${THREAD_TARGET} ${THREAD_DIRSRCS})

