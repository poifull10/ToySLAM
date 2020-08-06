#pragma once
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

  virtual void setIntrinsic(const std::unordered_map<std::string, float>&) = 0;
  virtual cv::Vec2d project(const cv::Vec3d&) const = 0;
  virtual cv::Vec3d unproject(const cv::Vec2d&) const = 0;
};
} // namespace tsfm
