#include "toy_slam.h"

#include <chrono>

#include "../io_data.h"

namespace ToySLAM::detail {
namespace {
void registerPointsToMap(const RangeFrame& frame, std::optional<Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic>>& map) {
}
}  // namespace
SLAMResult LiDARSLAM::operator()(RangeFrame inputFrame) {
  RangeFrame frame = std::move(inputFrame);
  std::sort(frame.scans.begin(), frame.scans.end(), [](const auto& lhs, const auto& rhs) { return lhs.timestamp < rhs.timestamp; });
  if (frame.scans.empty()) {
    return {
        .status = SLAMStatus::DROPPED,
        .timestamp = frame.scans.front().timestamp,
        .rectifiedRangeFrame = frame,
        .rigToOrigin = SE3{
            .translation = Eigen::Vector<DataFloatingType, 3>::Zero(),
            .rotation = Eigen::Quaternion<DataFloatingType>()}};
  }
  if (isInitialized()) {
    return initialize(frame);
  }
  return {};
}

void LiDARSLAM::reset() {
  map_.reset();
  subMap_.reset();
  prevRigToOrigin_.reset();
}

bool LiDARSLAM::isInitialized() const {
  return !map_.has_value() && !subMap_.has_value() && !prevRigToOrigin_.has_value();
}

SLAMResult LiDARSLAM::initialize(const RangeFrame& frame) {
  registerPointsToMap(frame, subMap_);
  frames.push_back(frame);
  return SLAMResult{
      .status = SLAMStatus::INITIALIZED,
      .timestamp = frame.scans.front().timestamp,
      .rectifiedRangeFrame = frame,
      .rigToOrigin = SE3{
          .translation = Eigen::Vector<DataFloatingType, 3>::Zero(),
          .rotation = Eigen::Quaternion<DataFloatingType>()}};
}
}  // namespace ToySLAM::detail
