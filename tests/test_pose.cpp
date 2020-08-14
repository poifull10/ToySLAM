#include <geo_primitive/pose.h>
#include <gtest/gtest.h>

TEST(Pose, constructor)
{
  const tsfm::Pose p;
  EXPECT_EQ(p.trans()[0], 0);
  EXPECT_EQ(p.trans()[1], 0);
  EXPECT_EQ(p.trans()[2], 0);
  EXPECT_EQ(p.quat()[0], 0);
  EXPECT_EQ(p.quat()[1], 0);
  EXPECT_EQ(p.quat()[2], 0);
  EXPECT_EQ(p.quat()[3], 1);
}

TEST(Pose, inv)
{
  tsfm::Pose p(tsfm::Vec3{-1., -0.4, 19.}, tsfm::Vec4{-3., 1., 0.4, 3.});
  p = p.inv() * p;
  EXPECT_NEAR(p.trans()[0], 0, 1e-3);
  EXPECT_NEAR(p.trans()[1], 0, 1e-3);
  EXPECT_NEAR(p.trans()[2], 0, 1e-3);
  EXPECT_NEAR(p.quat()[0], 0, 1e-3);
  EXPECT_NEAR(p.quat()[1], 0, 1e-3);
  EXPECT_NEAR(p.quat()[2], 0, 1e-3);
  EXPECT_NEAR(p.quat()[3], 1, 1e-3);
}