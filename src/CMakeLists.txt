cmake_minimum_required(VERSION 3.0.0)

project(Main VERSION 0.1.0)

add_subdirectory(http) 
add_subdirectory(utils) 
add_subdirectory(log) 
add_subdirectory(server) 
add_subdirectory(threadpool) 
add_subdirectory(timer) 

include(${ROOT_DIR}/Common.cmake)
 

set(TARGET main)

aux_source_directory(. DIRSRCS)
add_executable(${TARGET} ${DIRSRCS})
target_link_libraries(${TARGET} pthread)
target_link_libraries(${TARGET} jsoncpp) 
target_link_libraries(${TARGET} http)
target_link_libraries(${TARGET} utils)
target_link_libraries(${TARGET} log)
target_link_libraries(${TARGET} server) 
target_link_libraries(${TARGET} threadpool) 
target_link_libraries(${TARGET} timer) 
