#include <camera_model/pinhole_camera.h>

#include "gtest/gtest.h"

TEST(PinholeCamera, setIntrinsic)
{
  tsfm::PinholeCamera pc;
  std::unordered_map<std::string, double> int_;

  EXPECT_THROW(pc.setIntrinsic(int_), std::invalid_argument);

  int_.emplace("fx", 300);
  int_.emplace("fy", 300);
  int_.emplace("cx", 300);
  int_.emplace("cy", 300);

  EXPECT_NO_THROW(pc.setIntrinsic(int_));
}

TEST(PinholeCamera, project)
{
  tsfm::PinholeCamera pc;
  std::unordered_map<std::string, double> int_;
  const auto fx = 300;
  const auto fy = 100;
  const auto cx = 400;
  const auto cy = 200;
  int_.emplace("fx", fx);
  int_.emplace("fy", fy);
  int_.emplace("cx", cx);
  int_.emplace("cy", cy);
  pc.setIntrinsic(int_);

  std::array<double, 3> v{-0.3, 2.6, 4.5};
  const auto lower = v[2];
  const auto expect_v_x = (v[0] * fx + v[2] * cx) / lower;
  const auto expect_v_y = (v[1] * fy + v[2] * cy) / lower;

  const auto actual = pc.project(v);
  EXPECT_NEAR(actual[0], expect_v_x, 1e-2);
  EXPECT_NEAR(actual[1], expect_v_y, 1e-2);
}

TEST(PinholeCamera, unproject)
{
  tsfm::PinholeCamera pc;
  std::unordered_map<std::string, double> int_;
  const auto fx = 300;
  const auto fy = 100;
  const auto cx = 400;
  const auto cy = 200;
  int_.emplace("fx", fx);
  int_.emplace("fy", fy);
  int_.emplace("cx", cx);
  int_.emplace("cy", cy);
  pc.setIntrinsic(int_);

  std::array<double, 3> v{-0.3, 2.6, 4.5};
  const auto lower = v[2];
  const auto expect_v_x = (v[0] * fx + v[2] * cx) / lower;
  const auto expect_v_y = (v[1] * fy + v[2] * cy) / lower;

  const auto actual = pc.unproject({expect_v_x, expect_v_y});
  EXPECT_NEAR(actual[0], v[0] / v[2], 1e-2);
  EXPECT_NEAR(actual[1], v[1] / v[2], 1e-2);
  EXPECT_NEAR(actual[2], 1.0, 1e-2);
}