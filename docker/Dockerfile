FROM ubuntu:focal AS base

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
  build-essential cmake ninja-build git ca-certificates \
  libboost-all-dev libeigen3-dev libgoogle-glog-dev \
  && rm -rf /var/lib/apt/lists/*

FROM base AS builder-opencv
  WORKDIR /build
  ARG OPENCV_VERSION=4.4.0
  RUN git clone --branch ${OPENCV_VERSION} --single-branch --depth=1 https://github.com/opencv/opencv.git
  RUN git clone --branch ${OPENCV_VERSION} --single-branch --depth=1 https://github.com/opencv/opencv_contrib.git
  WORKDIR /build/opencv/build
  RUN cmake .. -GNinja \
    -DCMAKE_BUILD_TYPE=Release \
    -DOPENCV_ENABLE_NONFREE=ON \
    -DOPENCV_EXTRA_MODULES_PATH=/build/opencv_contrib/modules
  RUN ninja
  RUN ninja install

FROM base AS standard
  COPY --from=builder-opencv /usr/local/ /usr/local

FROM base AS builder-gcc10
  ARG GMP=gmp-6.2.0
  ARG MPFR=mpfr-4.1.0
  ARG MPC=mpc-1.1.0
  RUN apt update && DEBIAN_FRONTEND=noninteractive apt install -y --no-install-recommends \
    curl lzip gcc-multilib flex

  WORKDIR /build
  RUN curl -sSL https://gmplib.org/download/gmp/${GMP}.tar.lz -o gmp
  RUN tar --lzip -xvf gmp
  WORKDIR /build/${GMP}
  RUN ./configure
  RUN make -j${nproc} install

  WORKDIR /build
  RUN curl -sSL https://www.mpfr.org/mpfr-current/${MPFR}.tar.xz -o mpfr
  RUN tar -Jxvf mpfr
  WORKDIR /build/${MPFR}
  RUN ./configure
  RUN make install

  WORKDIR /build
  RUN curl -sSL http://www.multiprecision.org/downloads/${MPC}.tar.gz -o mpc
  RUN tar -xvf mpc
  WORKDIR /build/${MPC}
  RUN ./configure
  RUN make install

  WORKDIR /build
  RUN git clone --branch releases/gcc-10.2.0 --single-branch --depth=1 https://github.com/gcc-mirror/gcc.git
  WORKDIR /build/gcc
  RUN ./configure --enable-languages=c,c++ --prefix=/usr/local --disable-bootstrap
  RUN make
  RUN make install
  WORKDIR /build/gcc

FROM standard AS ci
  RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    clang-format llvm clang clang-tidy \
    && rm -rf /var/lib/apt/lists/*
  RUN mkdir -p /build \
    && cd /build \
    && git clone --single-branch --depth=1 https://github.com/Sarcasm/run-clang-format.git
  COPY --from=builder-gcc10 /usr/local/ /usr/local
