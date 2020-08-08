#pragma once

#include "vector.h"

namespace tsfm
{
class Pose
{
public:
  Pose() : trans_{0, 0, 0}, quat_{0, 0, 0, 1} {}
  Pose(const Vec3& t, const Vec4& q) : trans_(t), quat_(q) { normalize(); }
  Pose(const Pose&) = default;
  Pose(Pose&&) = default;
  Pose& operator=(const Pose&) = default;
  Pose& operator=(Pose&&) = default;

  Vec3 trans() const { return trans_; }
  Vec4 quat() const { return quat_; }

  void normalize() { quat_ = quat_ / tsfm::norm(quat_); }

private:
  Vec3 trans_;
  Vec4 quat_;
};
} // namespace tsfm
