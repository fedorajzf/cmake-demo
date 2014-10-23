cmake-demo: A cmake based skeleton project {#mainpage}
==========================================

Introduction
------------

This project is intended to be used as an example project, or a base project
for "the real work". The project setup is based on "best practices" as can
be found on the web. The project consists of:
- A main executable
- A dependent library (math-extra)
- Math-extra depends on the static library math-basic

It is assumed that math-basic is a project developed by a 3rd party, which is
augmented by our own library math-extra. The following cmake features are
demonstrated:

1. A consistent project structure

Each project and library can be build and tested independently of the
parent projects. Two strategies for adding related projects are demonstrated:
the builtin "add_subdirectory" and the cmake module "externalproject". Using
add_subdirectory is the easiest and recommended way to add a dependency; but
this is only suited for projects using CMake.

2. Integration of Cmake Test (ctest) and Google Test (gtest)

Both test runners ctest and gtest are used. Additionally, gtest is included
using the subtree-merge strategy for easy maintenance.

3. Relocatable installation targets

The generated binaries are "relocatable", meaning you could move them anywhere
in the system as long as their relative directory structure remains intact.
This is achieved by using the RPATH facilities of Unix-like Operating Systems.

Usage
-----

Every (sub)project can be built, tested and installed using the following
commands:

    $ mkdir build
    $ mkdir install
    $ cd build
    $ cmake [CMAKE_OPTIONS*] ..
    $ make
    $ make test
    $ make install

CMAKE_OPTIONS*:

For developers, it is recommended to add the following cmake-options:

    $ -DCMAKE_BUILD_PREFIX:PATH=`pwd`/../install

This will make sure the install command can be run without root privileges,
and it won't change the system.

Other usefull targets:

    $ make check # run tests, show output on failure
    $ make coverage # run coverage analysis and generate html report
