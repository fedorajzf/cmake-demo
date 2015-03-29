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

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    cmake_minimum_required (VERSION 2.8.12)
else ()
    cmake_minimum_required (VERSION 2.8.0)
endif ()

project (cmake-demo)
enable_testing ()

# ------------------------  Add referenced projects ---------------------------

set (BUILD_SHARED_LIBS ON CACHE STRING "")
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/lib/math-extra)

# ------------------------------- Build target --------------------------------

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/lib/math-extra/include)
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/lib/math-extra/lib/math-basic/include)

set (SOURCES
     ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/src/math.cpp
)

add_executable (cmake-demo ${SOURCES})
target_link_libraries (cmake-demo math-extra)

# ----------------------------- Install target --------------------------------

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set (CMAKE_MACOSX_RPATH ON)
    set_target_properties (cmake-demo PROPERTIES INSTALL_RPATH "@loader_path/../lib")
else ()
    set_target_properties (cmake-demo PROPERTIES BUILD_WITH_INSTALL_RPATH FALSE)
    set_target_properties (cmake-demo PROPERTIES INSTALL_RPATH "\$ORIGIN/../lib")
endif ()
install (TARGETS cmake-demo DESTINATION bin)

# ------------------------------- Build package--------------------------------

set (CPACK_GENERATOR "DEB")
set (CPACK_DEBIAN_PACKAGE_MAINTAINER "Tamar Kranenburg")
include (CPack)

# ------------------------------- Build tests ---------------------------------

add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/lib/gtest)
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/lib/gtest/include)

set  (TEST_SOURCES
      ${CMAKE_CURRENT_SOURCE_DIR}/tests/gtest_example.cpp
      ${SOURCES}
)

add_executable (${CMAKE_PROJECT_NAME}-test ${TEST_SOURCES})
target_link_libraries (${CMAKE_PROJECT_NAME}-test gtest_main)
target_link_libraries (${CMAKE_PROJECT_NAME}-test math-extra)
add_test (${CMAKE_PROJECT_NAME}-test ${CMAKE_PROJECT_NAME}-test)

add_test (
    ${PROJECT_NAME}-style
    ${PROJECT_SOURCE_DIR}/tools/check_style.sh
)

# Add a new target 'check' that wraps the built-in test target
if (CMAKE_CONFIGURATION_TYPES)
    add_custom_target (check COMMAND ${CMAKE_CTEST_COMMAND}
        --force-new-ctest-process --output-on-failure
        --build-config "$<CONFIGURATION>")
else ()
    add_custom_target (check COMMAND ${CMAKE_CTEST_COMMAND}
        --force-new-ctest-process --output-on-failure)
endif ()

# ---------------------------- Coverage analysis ------------------------------

set (CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
if (CMAKE_BUILD_TYPE MATCHES Debug)
    if (CMAKE_COMPILER_IS_GNUCXX OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        include (CodeCoverage)
        setup_target_for_coverage (coverage ${CMAKE_PROJECT_NAME}-test coverage
                                  "${PROJECT_SOURCE_DIR}/src/*")
    endif ()
endif ()

# ------------------------- Generate Documentation ----------------------------

find_package (Doxygen)
if (DOXYGEN_FOUND)
    configure_file (${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile @ONLY)
    add_custom_target (doc ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile
    ${CMAKE_CURRENT_SOURCE_DIR}/doc
    COMMENT "Generating API documentation" VERBATIM
)
endif (DOXYGEN_FOUND)
