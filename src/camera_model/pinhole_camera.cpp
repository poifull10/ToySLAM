#include "pinhole_camera.h"

#include <iostream>
#include <stdexcept>

#include "../util/cv_primitive.h"

namespace tsfm
{

namespace
{
cv::Mat constructK(const PinholeCamera::IntrincsicParameter& intr)
{
  cv::Mat mat = cv::Mat::eye(3, 3, CV_64F);
  mat.at<double>(0, 0) = intr.fx;
  mat.at<double>(0, 2) = intr.cx;
  mat.at<double>(1, 1) = intr.fy;
  mat.at<double>(1, 2) = intr.cy;
  return mat;
}
} // namespace
void PinholeCamera::setIntrinsic(
  const std::unordered_map<std::string, double>& param)
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

Vec2 PinholeCamera::project(const Vec3& p) const
{
  cv::Mat K = constructK(intrinsic_);
  cv::Mat vP = vec3ToCvMat(p);
  cv::Mat projected = K * vP;
  return {projected.at<double>(0, 0) / projected.at<double>(2, 0),
          projected.at<double>(1, 0) / projected.at<double>(2, 0)};
}

Vec3 PinholeCamera::unproject(const Vec2& p) const
{
  cv::Mat K = constructK(intrinsic_);
  cv::Mat vP = vec2ToCvMat(p, true);
  cv::Mat unprojected = K.inv() * vP;
  return {unprojected.at<double>(0, 0) / unprojected.at<double>(2, 0),
          unprojected.at<double>(1, 0) / unprojected.at<double>(2, 0), 1.0F};
}
} // namespace tsfm
