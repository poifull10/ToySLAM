FROM ubuntu:focal

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
  build-essential cmake ninja-build git ca-certificates \
  libboost-all-dev \
  && rm -rf /var/lib/apt/lists/*

ARG WORKSPACE=/build

WORKDIR ${WORKSPACE}

RUN git clone https://github.com/opencv/opencv.git && git clone https://github.com/opencv/opencv_contrib.git

WORKDIR ${WORKSPACE}/opencv

RUN mkdir -p build

WORKDIR ${WORKSPACE}/opencv/build

RUN cmake .. -GNinja -DCMAKE_BUILD_TYPE=Release -DOPENCV_ENABLE_NONFREE=ON -DOPENCV_EXTRA_MODULES_PATH=${WORKSPACE}/opencv_contrib/modules \
  && ninja -j$(nproc) \
  && ninja install

WORKDIR ${WORKSPACE}

RUN rm -rf *