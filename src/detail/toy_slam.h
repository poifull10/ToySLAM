#pragma once

#include <boost/circular_buffer.hpp>
#include <sophus/se2.hpp>

#include "../configuration.h"
#include "../io_data.h"

namespace ToySLAM::detail {
class LiDARSLAM {
 public:
  LiDARSLAM(ExtrinsicCalibration calibration, Configuration configuration) : calibration_(std::move(calibration)), configuration_(std::move(configuration)), frames(configuration_.subMapFrameCount) {}
  LiDARSLAM(const LiDARSLAM&) = delete;
  LiDARSLAM& operator=(const LiDARSLAM&) = delete;
  LiDARSLAM(LiDARSLAM&&) = default;
  LiDARSLAM& operator=(LiDARSLAM&&) = default;

  SLAMResult operator()(RangeFrame frame);
  void reset();

 private:
  ExtrinsicCalibration calibration_;
  Configuration configuration_;
  boost::circular_buffer<RangeFrame> frames;
  std::optional<Sophus::SE2<DataFloatingType>> prevRigToOrigin_;
  std::optional<Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic>> map_;
  std::optional<Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic>> subMap_;

  bool isInitialized() const;
  SLAMResult initialize(const RangeFrame& frame);
};
}  // namespace ToySLAM::detail
