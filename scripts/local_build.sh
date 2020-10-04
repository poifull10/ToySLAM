#!/bin/bash
user_name=$1
docker run --rm $PWD:$PWD -w $PWD -it $user_name/tsfm-ci .ci/build.sh -c gcc -b Release
