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

set( math-extra_VERSION_MAJOR 1 )
set( math-extra_VERSION_MINOR 0 )
set( math-extra_VERSION_PATCH 0 )
set( math-extra_VERSION_STRING ${math-extra_VERSION_MAJOR}.${math-extra_VERSION_MINOR}.${math-extra_VERSION_PATCH} )

# ------------------------  Add referenced projects ---------------------------

include( ExternalProject ) # requires cmake v2.8.0

ExternalProject_Add(
    math-basic-build
    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/math-basic"
    PREFIX "${CMAKE_CURRENT_BINARY_DIR}/math-basic"
    BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/math-basic/bin"
    CMAKE_ARGS "-DBUILD_STATIC_LIBRARIES=${BUILD_STATIC_LIBRARIES}"
    CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}"
    DOWNLOAD_COMMAND ""
    UPDATE_COMMAND ""
)

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
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/math-basic/include
)

if ( BUILD_STATIC_LIBRARIES )
    add_library( math-extra STATIC ${SOURCES} )
    target_link_libraries( math-extra ${CMAKE_INSTALL_PREFIX}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}math-basic${CMAKE_STATIC_LIBRARY_SUFFIX} )
else()
    add_library( math-extra SHARED ${SOURCES} )
    target_link_libraries( math-extra ${CMAKE_INSTALL_PREFIX}/lib/${CMAKE_SHARED_LIBRARY_PREFIX}math-basic${CMAKE_SHARED_LIBRARY_SUFFIX} )
endif()

add_dependencies( math-extra math-basic-build )

set_target_properties( math-extra PROPERTIES VERSION ${math-extra_VERSION_STRING} SOVERSION ${math-extra_VERSION_MAJOR} )

# ----------------------------- Install target --------------------------------

set( CMAKE_MACOSX_RPATH ON )
set_target_properties(math-extra PROPERTIES INSTALL_NAME_DIR "@rpath") 
install( TARGETS math-extra DESTINATION lib )

# ------------------------------- Build tests ---------------------------------

set ( TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/power.cpp
)

foreach( testsourcefile ${TEST_SOURCES} )
    get_filename_component( testname ${testsourcefile} NAME_WE)
    add_executable( ${testname} ${testsourcefile} )
    target_link_libraries( ${testname} math-extra )
    add_test( ${testname} ${testname} )
endforeach()
