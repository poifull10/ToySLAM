#!/bin/bash
set -eux
git submodule update --init --recursive
mkdir -p build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug -GNinja
ninja
./tests/TSfMTest
