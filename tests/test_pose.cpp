#include <gtest/gtest.h>  // NOLINT
#include <math/pose.h>

TEST(Pose, constructor) {
  const tsfm::Pose p;
  ASSERT_EQ(p.trans()[0], 0);
  ASSERT_EQ(p.trans()[1], 0);
  ASSERT_EQ(p.trans()[2], 0);
  ASSERT_EQ(p.quat()[0], 0);
  ASSERT_EQ(p.quat()[1], 0);
  ASSERT_EQ(p.quat()[2], 0);
  ASSERT_EQ(p.quat()[3], 1);
}

TEST(Pose, inv) {
  tsfm::Pose p(tsfm::Vec3{-1., -0.4, 19.}, tsfm::Vec4{-3., 1., 0.4, 3.});
  p = p.inv() * p;
  ASSERT_NEAR(p.trans()[0], 0, 1e-3);
  ASSERT_NEAR(p.trans()[1], 0, 1e-3);
  ASSERT_NEAR(p.trans()[2], 0, 1e-3);
  ASSERT_NEAR(p.quat()[0], 0, 1e-3);
  ASSERT_NEAR(p.quat()[1], 0, 1e-3);
  ASSERT_NEAR(p.quat()[2], 0, 1e-3);
  ASSERT_NEAR(p.quat()[3], 1, 1e-3);
}
