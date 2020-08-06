#pragma once
#include <array>
#include <opencv2/opencv.hpp>
#include <string>
#include <unordered_map>

namespace tsfm
{
class CameraModel
{
public:
  CameraModel() = default;
  CameraModel(const CameraModel&) = default;
  CameraModel(CameraModel&&) = default;
  ~CameraModel() = default;
  CameraModel& operator=(CameraModel&) = default;

  virtual void setIntrinsic(const std::unordered_map<std::string, double>&) = 0;
  virtual std::array<double, 2> project(
    const std::array<double, 3>& p) const = 0;
  virtual std::array<double, 3> unproject(
    const std::array<double, 2>&) const = 0;
};
} // namespace tsfm
