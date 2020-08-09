#include <util/load_data.h>

#include "gtest/gtest.h"

TEST(CalibrationLoader, load)
{
  tsfm::CalibrationLoader loader("../tests/pose_initializer_dataset/cam.yaml");
  const auto [type, data] = loader.load();
  EXPECT_TRUE(type.camera == tsfm::CameraType::pinhole);
  EXPECT_TRUE(type.distortion == tsfm::DistortionType::none);
  EXPECT_NEAR(data.at("fx"), 405.1404, 1e-4);
  EXPECT_NEAR(data.at("fy"), 405.1404, 1e-4);
  EXPECT_NEAR(data.at("cx"), 300, 1e-4);
  EXPECT_NEAR(data.at("cy"), 200, 1e-4);
}
