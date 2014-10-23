#!/bin/sh

mydir=`dirname $0`
$mydir/cpplint.py --filter=-runtime/references,-readability/streams \
    --root=src \
    $mydir/../src/*.cpp $mydir/../src/*.h \
    $mydir/../tests/*.cpp $mydir/../tests/*.h
