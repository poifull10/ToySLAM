#include "cv_primitive.h"

#include <Eigen/Dense>
#include <Eigen/Geometry>

namespace tsfm {
Vec3 cvMat2Vec3(const cv::Mat& p) {
  return Vec3{p.at<double>(0, 0), p.at<double>(1, 0), p.at<double>(2, 0)};
}

cv::Mat vec2ToCvMat(const Vector<double, 2>& p, bool outHomography) {
  if (outHomography) {
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

cv::Mat vec3ToCvMat(const Vector<double, 3>& p) {
  cv::Mat mat = cv::Mat::zeros(3, 1, CV_64F);
  mat.at<double>(0, 0) = p[0];
  mat.at<double>(1, 0) = p[1];
  mat.at<double>(2, 0) = p[2];
  return mat;
}

cv::Mat quatToCvRot(const Vec4 q) {
  Eigen::Quaterniond quaternion(q[3], q[0], q[1], q[2]);
  Eigen::Matrix3d mat(quaternion);

  cv::Mat m = cv::Mat::zeros(3, 3, CV_64F);
  for (size_t y = 0; y < 3; y++) {
    for (size_t x = 0; x < 3; x++) {
      m.at<double>(y, x) = mat(y, x);
    }
  }
  return m;
}

Vec4 CvRotToQuat(const cv::Mat& R) {
  Eigen::Matrix3d mat;
  for (size_t y = 0; y < 3; y++) {
    for (size_t x = 0; x < 3; x++) {
      mat(y, x) = R.at<double>(y, x);
    }
  }
  Eigen::Quaterniond q(mat);
  return Vec4{q.x(), q.y(), q.z(), q.w()};
}

}  // namespace tsfm
