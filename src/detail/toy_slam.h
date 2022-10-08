#pragma once

#include "../configuration.h"
#include "../io_data.h"

namespace ToySLAM::detail {
class LiDARSLAM {
 public:
  LiDARSLAM(ExtrinsicCalibration calibration, Configuration configuration) : calibration_(std::move(calibration)), configuration_(std::move(configuration)) {}
  LiDARSLAM(const LiDARSLAM&) = delete;
  LiDARSLAM& operator=(const LiDARSLAM&) = delete;
  LiDARSLAM(LiDARSLAM&&) = default;
  LiDARSLAM& operator=(LiDARSLAM&&) = default;

  SLAMResult operator()(const RangeFrame& frame);
  void reset();

 private:
  ExtrinsicCalibration calibration_;
  Configuration configuration_;
  std::optional<Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic>> map_;
  std::optional<Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic>> subMap_;

  bool isInitialized() const {
    return !map_.has_value() && !subMap_.has_value();
  }

  SLAMResult initialize(const RangeFrame& frame);
};
}  // namespace ToySLAM::detail
