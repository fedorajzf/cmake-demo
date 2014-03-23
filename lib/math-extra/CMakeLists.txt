cmake_minimum_required(VERSION 2.8.0)
project(library-math-extra)
enable_testing()

# Build dependent project

include(ExternalProject) # cmake module, available as of v2.8.0

ExternalProject_Add(
    math-basic
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/math-basic
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/lib/math-basic
    DOWNLOAD_COMMAND ""
    UPDATE_COMMAND ""
    INSTALL_COMMAND ""
)

# Build library

set ( HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/math-extra.h
)

set ( SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/power.cpp
    ${HEADERS}
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/math-basic/include
)

add_library( math-extra SHARED
    ${SOURCES}
)

target_link_libraries( math-extra ${CMAKE_CURRENT_BINARY_DIR}/lib/math-basic/src/math-basic-build/libmath.dylib ) # make target independent

# Build tests

set ( TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/power.cpp
)

foreach( testsourcefile ${TEST_SOURCES} )
    get_filename_component( testname ${testsourcefile} NAME_WE)
    add_executable( ${testname} ${testsourcefile} )
    target_link_libraries( ${testname} math-extra )
    add_test( ${testname} ${testname} )
endforeach( testsourcefile ${TEST_SOURCES} )
