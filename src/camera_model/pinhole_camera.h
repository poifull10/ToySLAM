#pragma once
#include "camera_model.h"

namespace tsfm {
class PinholeCamera : public CameraModel {
 public:
  PinholeCamera() = default;
  PinholeCamera(const PinholeCamera&) = default;
  PinholeCamera(PinholeCamera&&) = default;
  ~PinholeCamera() = default;
  PinholeCamera& operator=(PinholeCamera&) = default;

  void setIntrinsic(const std::unordered_map<std::string, double>&) override;
  Vec2 project(const Vec3& p) const override;
  Vec3 unproject(const Vec2&) const override;
  cv::Mat K() const override;
  struct IntrincsicParameter {
    double fx;
    double fy;
    double cx;
    double cy;
  };

 private:
  IntrincsicParameter intrinsic_;
};
}  // namespace tsfm
