#include "pose.h"

#include "../util/cv_primitive.h"

namespace tsfm
{
Pose Pose::inv() const
{
  const auto R = quatToCvRot(quat());
  const auto t = vec3ToCvMat(trans());
  cv::Mat R_inv = R.t();
  cv::Mat t_inv = -R_inv * t;
  return Pose(cvMat2Vec3(t_inv), CvRotToQuat(R_inv));
}

Pose operator*(const Pose& p2, const Pose& p1)
{
  const auto R2 = quatToCvRot(p2.quat());
  const auto t2 = vec3ToCvMat(p2.trans());
  const auto R1 = quatToCvRot(p1.quat());
  const auto t1 = vec3ToCvMat(p1.trans());
  cv::Mat R = R2 * R1;
  cv::Mat t = R2 * t1 + t2;
  return Pose(cvMat2Vec3(t), CvRotToQuat(R));
}
} // namespace tsfm