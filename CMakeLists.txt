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

cmake_minimum_required(VERSION 2.8.12)
project(cmake-demo)

# ------------------------  Add referenced projects ---------------------------

add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/lib/math-extra )

# ------------------------------- Build target --------------------------------

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/lib/math-extra/include )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/lib/math-extra/lib/math-basic/include )

add_executable( cmake-demo ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp )
target_link_libraries( cmake-demo math-extra )

# ----------------------------- Install target --------------------------------

set( CMAKE_MACOSX_RPATH ON )
set_target_properties( cmake-demo PROPERTIES INSTALL_RPATH "@loader_path/../lib")
install( TARGETS cmake-demo DESTINATION bin )
