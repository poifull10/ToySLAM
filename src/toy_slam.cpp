#include "toy_slam.h"

#include "detail/toy_slam.h"
#include "io_data.h"

namespace ToySLAM {
class LiDARSLAM::Impl {
 public:
  Impl(ExtrinsicCalibration calibration) : slam_(std::move(calibration)) {}
  Impl(const Impl&) = delete;
  Impl(Impl&&) = default;
  Impl& operator=(Impl&&) = default;
  Impl& operator=(const Impl&) = delete;

  SLAMResult operator()(const RangeFrame& frame) {
    return slam_(frame);
  }
  void reset() {
    slam_.reset();
  };

 private:
  detail::LiDARSLAM slam_;
};

SLAMResult LiDARSLAM::operator()(const RangeFrame& frame) {
  return (*impl_)(frame);
};

void LiDARSLAM::reset() {
  impl_->reset();
}

LiDARSLAM::LiDARSLAM(ExtrinsicCalibration calibration) : impl_(std::make_unique<LiDARSLAM::Impl>(std::move(calibration))) {}

}  // namespace ToySLAM
