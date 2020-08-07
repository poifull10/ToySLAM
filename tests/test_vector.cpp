#include <geo_primitive/vector.h>
#include <gtest/gtest.h>

TEST(Vector, constructor)
{
  tsfm::Vec2 v2;
  tsfm::Vec3 v3;
  tsfm::Vec4 v4;
}

TEST(Vector, apply)
{
  tsfm::Vec3 v3{1, 2, 3};
  auto actual = tsfm::apply(
    v3, std::function<double(double)>([](double x) { return x * x - 3; }));

  EXPECT_NEAR(actual[0], -2, 1e-3);
  EXPECT_NEAR(actual[1], 1, 1e-3);
  EXPECT_NEAR(actual[2], 6, 1e-3);
}

TEST(Vector, sum)
{
  tsfm::Vec3 v3{1, -7, 3};
  auto actual = tsfm::sum(v3);

  EXPECT_NEAR(actual, -3, 1e-3);
}

TEST(Vector, norm)
{
  tsfm::Vec3 v3{1, -7, 3};
  auto actual = tsfm::norm(v3);

  EXPECT_NEAR(actual, std::sqrt(1 + 49 + 9), 1e-3);
}