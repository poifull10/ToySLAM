#pragma once

#include <iostream>

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

  friend std::ostream& operator<<(std::ostream& os, const Pose& p)
  {
    os << "rx = " << p.quat()[0] << " ry = " << p.quat()[1] << " rz = " << p.quat()[2] << " rw = " << p.quat()[3] << std::endl;
    os << "tx = " << p.trans()[0] << " ty = " << p.trans()[1] << " tz = " << p.trans()[2];
    return os;
  }

private:
  Vec3 trans_;
  Vec4 quat_;
};
} // namespace tsfm
