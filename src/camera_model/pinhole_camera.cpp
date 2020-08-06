#include "pinhole_camera.h"

#include <stdexcept>

namespace tsfm
{
void PinholeCamera::setIntrinsic(
  const std::unordered_map<std::string, float>& param)
{
  if (param.count("fx") == 0)
  {
    throw std::invalid_argument("param needs fx");
  }

  if (param.count("fy") == 0)
  {
    throw std::invalid_argument("param needs fy");
  }

  if (param.count("cx") == 0)
  {
    throw std::invalid_argument("param needs cx");
  }

  if (param.count("cy") == 0)
  {
    throw std::invalid_argument("param needs cy");
  }

  intrinsic_ = PinholeCamera::IntrincsicParameter{
    param.at("fx"), param.at("fy"), param.at("cx"), param.at("cy")};
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
