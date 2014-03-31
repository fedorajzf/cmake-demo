###############################################################################
# Project "library-math-basic" builds a shared or static library with simple  #
#    mathematical functions.                                                  #
#                                                                             #
# Options:                                                                    #
#    BUILD_STATIC_LIBRARIES=[On|Off]                                          #
#                                                                             #
# Targets:                                                                    #
#    math-basic [lib]                                                         #
#                                                                             #
###############################################################################

# ----------------------------- Initialization --------------------------------

cmake_minimum_required(VERSION 2.6.0)
project(library-math-basic)
enable_testing()

# ------------------------------ Build library --------------------------------

set ( HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/math-basic.h
)

set ( SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/math-basic.cpp
    ${HEADERS}
)

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/include )

if( BUILD_STATIC_LIBRARIES )
    add_library ( math-basic STATIC ${SOURCES} )
else()
    add_library ( math-basic SHARED ${SOURCES} )
endif()

# ------------------------------- Build tests ---------------------------------

set ( TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/divide.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/multiply.cpp
)

foreach( testsourcefile ${TEST_SOURCES} )
    get_filename_component( testname ${testsourcefile} NAME_WE)
    add_executable( ${testname} ${testsourcefile} )
    if( BUILD_STATIC_LIBRARIES )
        target_link_libraries( ${testname} math-basic )
    else()
        target_link_libraries( ${testname} math-basic )
    endif()
    add_test( ${testname} ${testname} )
endforeach( testsourcefile ${TEST_SOURCES} )
