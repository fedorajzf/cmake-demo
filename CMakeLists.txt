###############################################################################
# Project "cmake-demo" links to libmath-extra for some cool functions         #
#                                                                             #
# Options:                                                                    #
#    BUILD_STATIC_LIBRARIES=[On|Off]                                          #
#                                                                             #
# Targets:                                                                    #
#    cmake-demo [executable]                                                  #
#                                                                             #
###############################################################################

# ----------------------------- Initialization --------------------------------

if( ${CMAKE_SYSTEM_NAME} MATCHES "Darwin" )
    cmake_minimum_required(VERSION 2.8.12)
else()
    cmake_minimum_required(VERSION 2.8.0)
endif()

project(cmake-demo)
enable_testing()

# ------------------------  Add referenced projects ---------------------------

add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/lib/math-extra )

# ------------------------------- Build target --------------------------------

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/lib/math-extra/include )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/lib/math-extra/lib/math-basic/include )

add_executable( cmake-demo ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp )
target_link_libraries( cmake-demo math-extra )

# ----------------------------- Install target --------------------------------

if( ${CMAKE_SYSTEM_NAME} MATCHES "Darwin" )
    set( CMAKE_MACOSX_RPATH ON )
    set_target_properties( cmake-demo PROPERTIES INSTALL_RPATH "@loader_path/../lib")
else()
    set_target_properties( cmake-demo PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE )
    set_target_properties( cmake-demo PROPERTIES INSTALL_RPATH "\$ORIGIN/../lib" )
endif()
install( TARGETS cmake-demo DESTINATION bin )

# ------------------------------- Build tests ---------------------------------

add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/lib/gtest )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/lib/gtest/include )

set ( TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/gtest_example.cpp
)

foreach( testsourcefile ${TEST_SOURCES} )
    get_filename_component( testname ${testsourcefile} NAME_WE)
    add_executable( ${testname} ${testsourcefile} )
    target_link_libraries( ${testname} gtest_main )
    add_test( ${testname} ${testname} )
endforeach()
