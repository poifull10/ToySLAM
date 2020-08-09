FROM ubuntu:focal

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
  build-essential cmake libopencv-dev libboost-all-dev \
  && rm -rf /var/lib/apt/lists/*