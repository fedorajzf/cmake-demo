cmake_minimum_required(VERSION 2.6.0)
project(library-math)
enable_testing()

# Build library

set ( HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/math.h
)

set ( SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/math.cpp
    ${HEADERS}
)

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/include )

add_library ( math SHARED
    ${SOURCES}
)

# Build tests

set ( TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/divide.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/multiply.cpp
)

foreach( testsourcefile ${TEST_SOURCES} )
    get_filename_component( testname ${testsourcefile} NAME_WE)
    add_executable( ${testname} ${testsourcefile} )
    target_link_libraries( ${testname} math )
    add_test( ${testname} ${testname} )
endforeach( testsourcefile ${APP_SOURCES} )
