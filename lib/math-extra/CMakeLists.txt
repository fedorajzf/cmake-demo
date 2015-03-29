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

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    cmake_minimum_required (VERSION 2.8.12)
else ()
    cmake_minimum_required (VERSION 2.8.0)
endif ()

project (library-math-extra)
enable_testing ()

set (math-extra_VERSION_MAJOR 1)
set (math-extra_VERSION_MINOR 0)
set (math-extra_VERSION_PATCH 0)
set (math-extra_VERSION_STRING ${math-extra_VERSION_MAJOR}.${math-extra_VERSION_MINOR}.${math-extra_VERSION_PATCH})

# ------------------------  Add referenced projects ---------------------------


# This is an example of using ExternalProject to build a 3rdparty library. Obviouly,
# one would use add_subdirectory whenever the 3rdparty library also uses CMake.

include (ExternalProject) # requires cmake v2.8.0
ExternalProject_Add (
    math-basic-build
    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/math-basic"
    PREFIX "${CMAKE_CURRENT_BINARY_DIR}/math-basic"
    BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/math-basic"
    CMAKE_ARGS "-DBUILD_STATIC_LIBRARIES=1"
    DOWNLOAD_COMMAND ""
    UPDATE_COMMAND ""
    INSTALL_COMMAND ""
)

add_library (math-basic STATIC IMPORTED)
set_target_properties (math-basic PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/math-basic/${CMAKE_STATIC_LIBRARY_PREFIX}math-basic${CMAKE_STATIC_LIBRARY_SUFFIX})
add_dependencies (math-basic math-basic-build)
set (MATH_BASIC_INCLUDE_DIRS  ${CMAKE_CURRENT_SOURCE_DIR}/lib/math-basic/include)
set (MATH_BASIC_LIBRARIES math-basic)

# ------------------------------ Build library --------------------------------

set (SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/power.cpp
)

include_directories (
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${MATH_BASIC_INCLUDE_DIRS}
)

if (BUILD_STATIC_LIBRARIES)
    add_library (math-extra STATIC ${SOURCES})
else ()
    add_library (math-extra SHARED ${SOURCES})
endif ()

target_link_libraries (math-extra ${MATH_BASIC_LIBRARIES})
set_target_properties (math-extra PROPERTIES VERSION ${math-extra_VERSION_STRING}
                                             SOVERSION ${math-extra_VERSION_MAJOR})

# ----------------------------- Install target --------------------------------

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    # Make installed library relocatable
    set (CMAKE_MACOSX_RPATH ON)
    set (CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
    set_target_properties (math-extra PROPERTIES INSTALL_NAME_DIR "@rpath")
endif ()
install (TARGETS math-extra DESTINATION lib)

# ------------------------------- Build tests ---------------------------------

set (TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/power.cpp
)

foreach (testsourcefile ${TEST_SOURCES})
    get_filename_component (testname ${testsourcefile} NAME_WE)
    add_executable (${testname} ${testsourcefile})
    target_link_libraries (${testname} math-extra)
    add_test (${testname} ${testname})
endforeach ()
