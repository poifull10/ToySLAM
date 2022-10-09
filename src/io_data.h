#pragma once
#include <chrono>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "constants.h"
#include "eigen_helper.h"

namespace ToySLAM {
struct StampedRangePoint {
  std::chrono::nanoseconds timestamp;
  Eigen::Vector<DataFloatingType, 2> position;
};

struct SE3 {
  Eigen::Vector<DataFloatingType, 3> translation;
  Eigen::Quaternion<DataFloatingType> rotation;
};

struct ExtrinsicCalibration {
  SE3 se3;
};

struct RangeFrame {
  std::vector<StampedRangePoint> scans;
};

enum class SLAMStatus {
  INITIALIZED,
  DROPPED,
  SUCCESS,
  LOST
};
struct SLAMResult {
  SLAMStatus status;
  std::chrono::nanoseconds timestamp;
  RangeFrame rectifiedRangeFrame;
  SE3 rigToOrigin;
};
}  // namespace ToySLAM
