cmake_minimum_required(VERSION 3.0.0)

include(${ROOT_DIR}/Common.cmake)

set(UTILS_TARGET utils)

aux_source_directory(. UTILS_DIRSRCS)
 
add_library(${UTILS_TARGET} ${UTILS_DIRSRCS})

