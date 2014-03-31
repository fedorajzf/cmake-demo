###############################################################################
# Project "library-math-extra" extends the library math-basic with the power  #
#    operator.                                                                #
#                                                                             #
# Options:                                                                    #
#    BUILD_STATIC_LIBRARIES=[On|Off]                                          #
#                                                                             #
# Targets:                                                                    #
#    math-basic [lib]                                                         #
#                                                                             #
###############################################################################

# ----------------------------- Initialization --------------------------------

cmake_minimum_required(VERSION 2.8.0)
project(library-math-extra)
enable_testing()

# ---------------------------- Build math-basic -------------------------------

include( ExternalProject ) # requires cmake v2.8.0

ExternalProject_Add(
    math-basic-build
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/math-basic
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/math-basic
    BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/math-basic/bin
    CMAKE_ARGS -DBUILD_STATIC_LIBRARIES=${BUILD_STATIC_LIBRARIES}
    DOWNLOAD_COMMAND ""
    UPDATE_COMMAND ""
    INSTALL_COMMAND ""
)

# We register the library into the build system
if ( BUILD_STATIC_LIBRARIES )
    add_library( math-basic STATIC IMPORTED )
else()
    add_library( math-basic SHARED IMPORTED )
endif()

ExternalProject_Get_Property( math-basic-build SOURCE_DIR )
ExternalProject_Get_Property( math-basic-build BINARY_DIR )

if( BUILD_STATIC_LIBRARIES )
    set_target_properties( math-basic PROPERTIES IMPORTED_LOCATION ${BINARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}math-basic${CMAKE_STATIC_LIBRARY_SUFFIX} )
else()
    set_target_properties( math-basic PROPERTIES IMPORTED_LOCATION ${BINARY_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}math-basic${CMAKE_SHARED_LIBRARY_SUFFIX} )
endif()

# ------------------------------ Build library --------------------------------

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

if ( BUILD_STATIC_LIBRARIES )
    add_library( math-extra STATIC ${SOURCES} )
else()
    add_library( math-extra SHARED ${SOURCES} )
endif()

target_link_libraries( math-extra math-basic )
add_dependencies( math-extra math-basic-build )

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
