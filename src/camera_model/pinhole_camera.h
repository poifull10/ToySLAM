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

  void setIntrinsic(const std::unordered_map<std::string, double>&) override;
  std::array<double, 2> project(const std::array<double, 3>& p) const override;
  std::array<double, 3> unproject(const std::array<double, 2>&) const override;
  struct IntrincsicParameter
  {
    double fx;
    double fy;
    double cx;
    double cy;
  };

private:
  IntrincsicParameter intrinsic_;
};
} // namespace tsfm
