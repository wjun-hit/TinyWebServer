cmake_minimum_required(VERSION 3.0.0)

include(${ROOT_DIR}/Common.cmake)

set(LOG_TARGET log)
 
aux_source_directory(. LOG_DIRSRCS)

add_library(${LOG_TARGET} ${LOG_DIRSRCS})


