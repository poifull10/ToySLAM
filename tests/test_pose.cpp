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