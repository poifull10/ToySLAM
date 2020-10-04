#pragma once
#include <array>
#include <opencv2/opencv.hpp>  // NOLINT
#include <string>
#include <unordered_map>

#include "../geo_primitive/vector.h"

namespace tsfm {

enum class CameraType {
  pinhole
};

enum class DistortionType {
  none
};

struct CameraDistortion {
  CameraType camera;
  DistortionType distortion;
};

class CameraModel {
 public:
  CameraModel() = default;
  CameraModel(const CameraModel&) = default;
  CameraModel(CameraModel&&) = default;
  ~CameraModel() = default;
  CameraModel& operator=(CameraModel&) = default;

  virtual void setIntrinsic(const std::unordered_map<std::string, double>&) = 0;
  virtual Vec2 project(const Vec3& p) const = 0;
  virtual Vec3 unproject(const Vec2&) const = 0;
  virtual cv::Mat K() const = 0;
};
}  // namespace tsfm
