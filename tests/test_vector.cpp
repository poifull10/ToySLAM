#include <gtest/gtest.h>  // NOLINT
#include <math/vector.h>

TEST(Vector, constructor) {
  tsfm::Vec2 v2;
  tsfm::Vec3 v3;
  tsfm::Vec4 v4;
}

TEST(Vector, norm) {
  tsfm::Vec3 v3{1, -7, 3};
  auto actual = tsfm::norm(v3);
  ASSERT_NEAR(actual, std::sqrt(1 + 49 + 9), 1e-3);
}

TEST(Vector, mult) {
  tsfm::Vec3 v3{1, -7, 3};
  const auto actual = v3 * -2.0;
  ASSERT_NEAR(actual[0], -2, 1e-3);
  ASSERT_NEAR(actual[1], 14, 1e-3);
  ASSERT_NEAR(actual[2], -6, 1e-3);
}

TEST(Vector, div) {
  tsfm::Vec3 v3{1, -7, 3};
  const auto actual = v3 / tsfm::norm(v3);
  const auto norm = std::sqrt(1 + 49 + 9);
  ASSERT_NEAR(actual[0], 1 / norm, 1e-3);
  ASSERT_NEAR(actual[1], -7 / norm, 1e-3);
  ASSERT_NEAR(actual[2], 3 / norm, 1e-3);
}
