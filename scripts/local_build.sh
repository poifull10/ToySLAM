#!/bin/bash
set -ex
usage_exit() {
  echo "Usage: $0 [-c gcc|clang] [-b Debug|Release]" 1>&2
  exit 1
}

while getopts b:c:h OPT
do
  case $OPT in
    b)  build_type=$OPTARG ;;
    c)  compiler_type=$OPTARG ;;
    h)  usage_exit ;;
    \?) usage_exit ;;
  esac
done

set -u

docker run --rm -v $PWD:$PWD -w $PWD -it poifull10/tsfm-ci .ci/build.sh -c $compiler_type -b $build_type
