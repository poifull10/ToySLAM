#pragma once
#include <opencv2/opencv.hpp>

#include "../geo_primitive/pose.h"
#include "../geo_primitive/vector.h"

namespace tsfm
{

Vec3 cvMat2Vec3(const cv::Mat& p);
cv::Mat vec2ToCvMat(const Vector<double, 2>& p, bool outHomography = false);
cv::Mat vec3ToCvMat(const Vector<double, 3>& p);
cv::Mat quatToCvRot(const Vec4 q);
cv::Mat poseToCvMat(const Pose& pose);
Vec4 CvRotToQuat(const cv::Mat& R);

} // namespace tsfm