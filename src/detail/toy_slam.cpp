#pragma once

#include "toy_slam.h"

#include <chrono>

#include "../io_data.h"

namespace ToySLAM::detail {
SLAMResult LiDARSLAM::operator()(const RangeFrame& frame) {
  if (isInitialized()) {
    return initialize(frame);
  }
  return {};
}
void LiDARSLAM::reset() {
  map_.reset();
  subMap_.reset();
}

SLAMResult LiDARSLAM::initialize(const RangeFrame& frame) {
  return SLAMResult{
      .success = true,
      .timestamp = std::chrono::nanoseconds(0),
      .rectifiedRangeFrame = frame,
      .rigToOrigin = SE3{
          .translation = Eigen::Vector<DataFloatingType, 3>::Zero(),
          .rotation = Eigen::Quaternion<DataFloatingType>()}};
}
}  // namespace ToySLAM::detail
