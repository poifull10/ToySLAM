#include "pinhole_camera.h"

namespace tsfm
{
void PinholeCamera::setIntrinsic(
  const std::unordered_map<std::string, float>& param)
{
}
cv::Vec2d PinholeCamera::project(const cv::Vec3d&) const
{
  return cv::Vec2d{};
}
cv::Vec3d PinholeCamera::unproject(const cv::Vec2d&) const
{
  return cv::Vec3d{};
}
} // namespace tsfm
