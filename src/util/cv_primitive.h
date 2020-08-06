#pragma once
#include <opencv2/opencv.hpp>

#include "../geo_primitive/vector.h"

namespace tsfm
{
Vector<double, 3> cvMat2Vec3(const cv::Mat& p, bool outHomography = false);
Vector<double, 2> cvMat2Vec2(const cv::Mat& p);

cv::Mat vec2ToCvMat(const Vector<double, 2>& p, bool outHomography = false)
{
  if (outHomography)
  {
    cv::Mat mat = cv::Mat::zeros(3, 1, CV_64F);
    mat.at<double>(0, 0) = p[0];
    mat.at<double>(1, 0) = p[1];
    mat.at<double>(2, 0) = 1;
    return mat;
  }
  cv::Mat mat = cv::Mat::zeros(2, 1, CV_64F);
  mat.at<double>(0, 0) = p[0];
  mat.at<double>(1, 0) = p[1];
  return mat;
}

cv::Mat vec3ToCvMat(const Vector<double, 3>& p)
{
  cv::Mat mat = cv::Mat::zeros(3, 1, CV_64F);
  mat.at<double>(0, 0) = p[0];
  mat.at<double>(1, 0) = p[1];
  mat.at<double>(2, 0) = p[2];
  return mat;
}
} // namespace tsfm