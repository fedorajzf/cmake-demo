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

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    cmake_minimum_required (VERSION 2.8.12)
else ()
    cmake_minimum_required (VERSION 2.8.0)
endif ()

project(library-math-basic)
enable_testing()

set (math-basic_VERSION_MAJOR 1)
set (math-basic_VERSION_MINOR 0)
set (math-basic_VERSION_PATCH 0)
set (math-basic_VERSION_STRING ${math-basic_VERSION_MAJOR}.${math-basic_VERSION_MINOR}.${math-basic_VERSION_PATCH})

# ------------------------------ Build library --------------------------------

set (HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/math-basic.h
)

set (SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/math-basic.cpp
    ${HEADERS}
)

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/include)

if (BUILD_STATIC_LIBRARIES)
    add_library (math-basic STATIC ${SOURCES})
else ()
    add_library (math-basic SHARED ${SOURCES})
endif ()

set_target_properties (math-basic PROPERTIES VERSION ${math-basic_VERSION_STRING} SOVERSION ${math-basic_VERSION_MAJOR})

# ----------------------------- Install target -------------------------------

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set (CMAKE_MACOSX_RPATH ON)
    set (CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
    set_target_properties (math-basic PROPERTIES INSTALL_NAME_DIR "@rpath")
endif ()
install (TARGETS math-basic DESTINATION lib)

# ------------------------------- Build tests ---------------------------------

set (TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/divide.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/multiply.cpp
)

foreach (testsourcefile ${TEST_SOURCES})
    get_filename_component (testname ${testsourcefile} NAME_WE)
    add_executable (${testname} ${testsourcefile})
    if (BUILD_STATIC_LIBRARIES)
        target_link_libraries (${testname} math-basic)
    else ()
        target_link_libraries (${testname} math-basic)
    endif ()
    add_test (${testname} ${testname})
endforeach (testsourcefile ${TEST_SOURCES})
