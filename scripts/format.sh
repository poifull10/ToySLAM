#!/bin/bash
docker run --rm -v $PWD:$PWD -w $PWD -it poifull10/tsfm-ci python3 /build/run-clang-format/run-clang-format.py -i -r src examples tests
