#pragma once

#include "../io_data.h"

namespace ToySLAM::detail {
class LiDARSLAM {
 public:
  LiDARSLAM(ExtrinsicCalibration calibration) : calibration_(calibration) {}
  LiDARSLAM(const LiDARSLAM&) = delete;
  LiDARSLAM& operator=(const LiDARSLAM&) = delete;
  LiDARSLAM(LiDARSLAM&&) = default;
  LiDARSLAM& operator=(LiDARSLAM&&) = default;

  SLAMResult operator()(const RangeFrame& frame);
  void reset();

 private:
  ExtrinsicCalibration calibration_;
};
}  // namespace ToySLAM::detail
