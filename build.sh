#!/bin/sh

set -e

cd "$(dirname $0)"

if [ ! -d build ]; then
  mkdir build
fi
cd build

if [ ! -f Makefile ]; then
  cmake ..
fi

CTEST_OUTPUT_ON_FAILURE=1 make all test
