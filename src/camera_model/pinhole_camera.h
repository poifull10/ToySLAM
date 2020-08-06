#pragma once
#include "camera_model.h"

namespace tsfm
{
class PinholeCamera : public CameraModel
{
public:
  PinholeCamera() = default;
  PinholeCamera(const PinholeCamera&) = default;
  PinholeCamera(PinholeCamera&&) = default;
  ~PinholeCamera() = default;
  PinholeCamera& operator=(PinholeCamera&) = default;

  void setIntrinsic(const std::unordered_map<std::string, float>&) override;
  cv::Vec2d project(const cv::Vec3d&) const override;
  cv::Vec3d unproject(const cv::Vec2d&) const override;

private:
  struct IntrincsicParameter
  {
    float fx;
    float fy;
    float cx;
    float cy;
  };
  IntrincsicParameter intrinsic_;
};
} // namespace tsfm
