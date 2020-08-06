#include "pinhole_camera.h"

#include <iostream>
#include <stdexcept>

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
cv::Mat constructVVec(const std::array<double, 3>& p)
{
  cv::Mat mat = cv::Mat::zeros(3, 1, CV_64F);
  mat.at<double>(0, 0) = p[0];
  mat.at<double>(1, 0) = p[1];
  mat.at<double>(2, 0) = p[2];
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
std::array<double, 2> PinholeCamera::project(
  const std::array<double, 3>& p) const
{
  cv::Mat K = constructK(intrinsic_);
  cv::Mat vP = constructVVec(p);
  cv::Mat projected = K * vP;
  return {projected.at<double>(0, 0) / projected.at<double>(2, 0),
          projected.at<double>(1, 0) / projected.at<double>(2, 0)};
}
std::array<double, 3> PinholeCamera::unproject(
  const std::array<double, 2>& p) const
{
  return {};
}
} // namespace tsfm
