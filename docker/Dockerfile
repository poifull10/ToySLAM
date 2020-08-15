FROM ubuntu:focal

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
  build-essential cmake ninja-build git ca-certificates \
  libboost-all-dev libeigen3-dev libgoogle-glog-dev \
  && rm -rf /var/lib/apt/lists/*

ARG WORKSPACE=/build

RUN mkdir -p ${WORKSPACE} \
  && cd ${WORKSPACE} \
  && git clone https://github.com/opencv/opencv.git \
  && git clone https://github.com/opencv/opencv_contrib.git \
  && mkdir -p ${WORKSPACE}/opencv/build && cd ${WORKSPACE}/opencv/build \
  && cmake .. -GNinja \
  -DCMAKE_BUILD_TYPE=Release \
  -DOPENCV_ENABLE_NONFREE=ON \
  -DOPENCV_EXTRA_MODULES_PATH=${WORKSPACE}/opencv_contrib/modules \
  && ninja -j$(nproc) \
  && ninja install \
  && cd / \
  && rm -rf ${WORKSPACE}

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
  clang-format \
  && rm -rf /var/lib/apt/lists/* \
  && mkdir -p ${WORKSPACE} \
  && cd ${WORKSPACE} \
  && git clone https://github.com/Sarcasm/run-clang-format.git