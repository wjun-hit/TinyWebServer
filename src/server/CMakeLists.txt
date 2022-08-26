cmake_minimum_required(VERSION 3.0.0)

include(${ROOT_DIR}/Common.cmake)

set(SERVER_TARGET server)
 
aux_source_directory(. SERVER_DIRSRCS)

add_library(${SERVER_TARGET} ${SERVER_DIRSRCS})
target_link_libraries(${SERVER_TARGET} http)

   