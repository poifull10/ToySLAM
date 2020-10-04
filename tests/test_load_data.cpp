#include <util/load_data.h>

#include "gtest/gtest.h"  // NOLINT

TEST(CalibrationLoader, load) {
  tsfm::CalibrationLoader loader("tests/pose_initializer_dataset/cam.yaml");
  const auto& [type, data] = loader.load();
  ASSERT_TRUE(type.camera == tsfm::CameraType::pinhole);
  ASSERT_TRUE(type.distortion == tsfm::DistortionType::none);
  ASSERT_FLOAT_EQ(data.at("fx"), 405.1404);
  ASSERT_FLOAT_EQ(data.at("fy"), 405.1404);
  ASSERT_FLOAT_EQ(data.at("cx"), 300);
  ASSERT_FLOAT_EQ(data.at("cy"), 200);
}
