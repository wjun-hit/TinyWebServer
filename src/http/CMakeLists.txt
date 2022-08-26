cmake_minimum_required(VERSION 3.0.0)

include(${ROOT_DIR}/Common.cmake)

set(HTTP_TARGET http)
 
aux_source_directory(. HTTP_DIRSRCS)
 
add_library(${HTTP_TARGET} ${HTTP_DIRSRCS})
