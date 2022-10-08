#pragma once

#include <memory>

#include "configuration.h"
#include "io_data.h"

namespace ToySLAM {
class LiDARSLAM {
 public:
  LiDARSLAM(ExtrinsicCalibration calibration, Configuration configuration);
  LiDARSLAM(const LiDARSLAM&) = delete;
  LiDARSLAM& operator=(const LiDARSLAM&) = delete;
  LiDARSLAM(LiDARSLAM&&) = default;
  LiDARSLAM& operator=(LiDARSLAM&&) = default;

  SLAMResult operator()(const RangeFrame& frame);
  void reset();

 private:
  class Impl;
  std::unique_ptr<Impl> impl_;
};
}  // namespace ToySLAM