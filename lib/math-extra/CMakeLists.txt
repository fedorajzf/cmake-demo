cmake_minimum_required(VERSION 2.8.0)
project(library-math-extra)
enable_testing()

# Build dependent project (math-basic)

include(ExternalProject) # cmake module, available as of v2.8.0

ExternalProject_Add(
    math-basic-build
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/math-basic
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/math-basic
    BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/math-basic/bin
    DOWNLOAD_COMMAND ""
    UPDATE_COMMAND ""
    INSTALL_COMMAND ""
)

ExternalProject_Get_Property( math-basic-build SOURCE_DIR )
ExternalProject_Get_Property( math-basic-build BINARY_DIR )

add_library( math-basic SHARED IMPORTED )
add_library( math-basic-static STATIC IMPORTED )

set_target_properties( math-basic PROPERTIES IMPORTED_LOCATION ${BINARY_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}math-basic${CMAKE_SHARED_LIBRARY_SUFFIX} )
set_target_properties( math-basic-static PROPERTIES IMPORTED_LOCATION ${BINARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}math-basic-static${CMAKE_STATIC_LIBRARY_SUFFIX} )

# Build library math-extra

set ( HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/math-extra.h
)

set ( SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/power.cpp
    ${HEADERS}
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${SOURCE_DIR}/include
)

# Build dynamic library
add_library( math-extra SHARED
    ${SOURCES}
)
target_link_libraries( math-extra math-basic )
add_dependencies( math-extra math-basic-build )

# Build static library
add_library( math-extra-static STATIC
    ${SOURCES}
)
target_link_libraries( math-extra-static math-basic-static )
add_dependencies( math-extra-static math-basic-build )

# Build tests

set ( TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/power.cpp
)

foreach( testsourcefile ${TEST_SOURCES} )
    get_filename_component( testname ${testsourcefile} NAME_WE)
    add_executable( ${testname} ${testsourcefile} )
    target_link_libraries( ${testname} math-extra )
    add_test( ${testname} ${testname} )
endforeach()
