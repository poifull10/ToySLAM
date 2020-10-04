#!/bin/bash
user_name=$1
BUILD_TOOLKIT=1 docker build docker -t $user_name/tsfm-standard --target standard
BUILD_TOOLKIT=1 docker build docker -t $user_name/tsfm-ci --target ci
