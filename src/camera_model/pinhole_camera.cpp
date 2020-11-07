#include "pinhole_camera.h"

#include <iostream>
#include <stdexcept>

#include "../configuration/constant.h"
#include "../util/cv_primitive.h"

namespace tsfm {

namespace {

cv::Mat constructK(const PinholeCamera::IntrincsicParameter& intr) {
  cv::Mat mat = CvMatMaker<TSFMFloatType>::makeEye(3, 3);
  mat.at<double>(0, 0) = intr.fx;
  mat.at<double>(0, 2) = intr.cx;
  mat.at<double>(1, 1) = intr.fy;
  mat.at<double>(1, 2) = intr.cy;
  return mat;
}
}  // namespace

void PinholeCamera::setIntrinsic(const std::unordered_map<std::string, double>& param) {
  if (param.count("fx") == 0) {
    throw std::invalid_argument("param needs fx");
  }

  if (param.count("fy") == 0) {
    throw std::invalid_argument("param needs fy");
  }

  if (param.count("cx") == 0) {
    throw std::invalid_argument("param needs cx");
  }

  if (param.count("cy") == 0) {
    throw std::invalid_argument("param needs cy");
  }
  intrinsic_ = PinholeCamera::IntrincsicParameter{param.at("fx"), param.at("fy"), param.at("cx"), param.at("cy")};
}

Vec2 PinholeCamera::project(const Vec3& p) const {
  const cv::Mat K = constructK(intrinsic_);
  const cv::Mat vP = vec3ToCvMat(p);
  const cv::Mat projected = K * vP;
  const Vec2 projectedVec{projected.at<double>(0, 0), projected.at<double>(1, 0)};
  return projectedVec / projected.at<double>(2, 0);
}

Vec3 PinholeCamera::unproject(const Vec2& p) const {
  const cv::Mat K = constructK(intrinsic_);
  const cv::Mat vP = vec2ToCvMat(p, true);
  const cv::Mat unprojected = K.inv() * vP;
  const Vec3 unprojectedVec{unprojected.at<double>(0, 0), unprojected.at<double>(1, 0), unprojected.at<double>(2, 0)};
  return unprojectedVec / unprojectedVec[2];
}

cv::Mat PinholeCamera::K() const {
  cv::Mat K = CvMatMaker<TSFMFloatType>::makeEye(3, 3);
  K.at<double>(0, 0) = intrinsic_.fx;
  K.at<double>(1, 1) = intrinsic_.fy;
  K.at<double>(0, 2) = intrinsic_.cx;
  K.at<double>(1, 2) = intrinsic_.cy;
  return K;
}
}  // namespace tsfm
