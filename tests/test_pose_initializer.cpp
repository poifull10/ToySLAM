#include <camera_model/pinhole_camera.h>
#include <gtest/gtest.h>
#include <image/image.h>
#include <initializer/pose_initializer.h>
#include <util/load_data.h>
#include <yaml-cpp/yaml.h>

#include <iostream>

TEST(PoseInitializer, estimatePose)
{
  tsfm::PoseInitializer pi;
  tsfm::Image img1("../tests/pose_initializer_dataset/000000.png");
  img1.load();
  tsfm::Image img2("../tests/pose_initializer_dataset/000002.png");
  img2.load();

  tsfm::CalibrationLoader cl("../tests/pose_initializer_dataset/cam.yaml");
  const auto [_, data] = cl.load();

  const auto answer =
    YAML::LoadFile("../tests/pose_initializer_dataset/pose02.yaml");

  tsfm::PinholeCamera pc;
  pc.setIntrinsic(data);

  const auto pose = pi(img1, img2, pc);
  EXPECT_NEAR(pose.quat()[0], answer["rx"].as<double>(), 1e-1);
  EXPECT_NEAR(pose.quat()[1], answer["ry"].as<double>(), 1e-1);
  EXPECT_NEAR(pose.quat()[2], answer["rz"].as<double>(), 1e-1);
  EXPECT_NEAR(pose.quat()[3], answer["rw"].as<double>(), 1e-1);
  tsfm::Vec3 t{answer["tx"].as<double>(), answer["ty"].as<double>(),
               answer["tz"].as<double>()};
  t = t / tsfm::norm(t);
  EXPECT_NEAR(pose.trans()[0], t[0], 5e-1);
  EXPECT_NEAR(pose.trans()[1], t[1], 5e-1);
  EXPECT_NEAR(pose.trans()[2], t[2], 5e-1);
}
