#include <camera_model/pinhole_camera.h>

#include "gtest/gtest.h"

TEST(PinholeCamera, setIntrinsic)
{
  tsfm::PinholeCamera pc;
  std::unordered_map<std::string, float> int_;

  EXPECT_THROW(pc.setIntrinsic(int_), std::invalid_argument);

  int_.emplace("fx", 300);
  int_.emplace("fy", 300);
  int_.emplace("cx", 300);
  int_.emplace("cy", 300);

  EXPECT_NO_THROW(pc.setIntrinsic(int_));
}
