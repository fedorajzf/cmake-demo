cmake_minimum_required(VERSION 2.8.0)
project(cmake-demo)

add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/lib/math-extra )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/lib/math-extra/include )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/lib/math-extra/lib/math-basic/include )

add_executable( cmake-demo ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp )
target_link_libraries( cmake-demo math-extra )
