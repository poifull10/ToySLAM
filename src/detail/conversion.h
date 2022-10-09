#pragma once
#include <sophus/se2.hpp>

#include "../constants.h"
#include "../eigen_helper.h"
#include "../io_data.h"

namespace ToySLAM {
inline Sophus::SE2<DataFloatingType> toSophus2D(const SE3& se3) {
  Sophus::SE2<DataFloatingType> ret;
  ret.translation() = se3.translation.head<2>();
  ret.so2() = Sophus::SO2<DataFloatingType>::exp(se3.rotation.toRotationMatrix().eulerAngles(0, 1, 2)[2]);
  return ret;
}

inline SE3 toSE3(const Sophus::SE2<DataFloatingType>& se2) {
  SE3 ret{
      .translation = Eigen::Vector<DataFloatingType, 3>::Zero(),
      .rotation = Eigen::Quaternion<DataFloatingType>()};
  ret.translation.head<2>() = se2.translation();
  ret.rotation = Eigen::Quaternion<DataFloatingType>(AngleAxis<DataFloatingType>(se2.so2(), Eigen::Vector<DataFloatingType, 3>::UnitZ()));
  return ret;
}

}  // namespace ToySLAM
