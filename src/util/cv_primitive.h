#pragma once
#include <opencv2/opencv.hpp>  // NOLINT

#include "../math/vector.h"

namespace tsfm {
auto cvMat2Vec3(const cv::Mat& p) -> Vec3;
auto vec2ToCvMat(const Vector<double, 2>& p, bool outHomography = false) -> cv::Mat;
auto vec3ToCvMat(const Vector<double, 3>& p) -> cv::Mat;
auto quatToCvRot(const Vec4 q) -> cv::Mat;
auto CvRotToQuat(const cv::Mat& R) -> Vec4;
}  // namespace tsfm
