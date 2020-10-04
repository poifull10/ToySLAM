#!/bin/bash
set -ex

build_type="Debug"
compiler_type="gcc"
analyzer=""
tidy=""

usage_exit() {
  echo "Usage: $0 [-c gcc|clang] [-b Debug|Release] [-t enable Tidy when using clang] [-a enable -fanalyzer option when using gcc]" 1>&2
  exit 1
}

while getopts ab:c:th OPT
do
  case $OPT in
    a)  analyzer="-DCMAKE_CXX_FLAGS=\"-fanalyzer\"" ;;
    b)  build_type=$OPTARG ;;
    c)  compiler_type=$OPTARG ;;
    t)  tidy="clang-tidy;-checks=-*,modernize-*;clang-analyzer-*,google-*;-fix;-fix-errors;-header-filter=.*yaml-cpp/.*h" ;;
    h)  usage_exit ;;
    \?) usage_exit ;;
  esac
done

set -u

git submodule update --init --recursive

# check format
python3 /build/run-clang-format/run-clang-format.py -r src examples tests

# build
build_space=""
if [ $tidy = "" ]; then
  build_space="build/"$compiler_type"-"$build_type
elif [ $analyzer = "" ]; then
  build_space="build/"$compiler_type"-"$build_type-"tidy"
else
  build_space="build/"$compiler_type"-"$build_type-"analyzer"
fi
mkdir -p $build_space && cd $build_space

c_compiler=""
cxx_compiler=""
if [ $compiler_type = "gcc" ]; then
  c_compiler=/usr/local/bin/gcc
  cxx_compiler=/usr/local/bin/g++
elif [ $compiler_type = "clang" ]; then
  c_compiler=/usr/bin/clang
  cxx_compiler=/usr/bin/clang++
else
  echo "Unexpected option: " $compiler_type
  exit 1
fi

cmake ../.. -DCMAKE_BUILD_TYPE=$build_type -DCMAKE_C_COMPILER=$c_compiler -DCMAKE_CXX_COMPILER=$cxx_compiler -GNinja ${analyzer} -DCMAKE_CXX_CLANG_TIDY="${tidy}"
ninja

# test
cd ../..
${build_space}/tests/TSfMTest
