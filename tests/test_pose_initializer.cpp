#include <camera_model/pinhole_camera.h>
#include <glog/logging.h>
#include <gtest/gtest.h>
#include <image/image.h>
#include <initializer/pose_initializer.h>
#include <matcher/image_matcher.h>
#include <util/load_data.h>
#include <yaml-cpp/yaml.h>

#include <iostream>

TEST(PoseInitializer, estimatePose)
{
  tsfm::PoseInitializer pi;
  tsfm::ImageMaker maker;
  auto img1 = maker.make("../tests/pose_initializer_dataset/000000.png");
  auto img2 = maker.make("../tests/pose_initializer_dataset/000002.png");
  img1->load();
  img2->load();

  tsfm::CalibrationLoader cl("../tests/pose_initializer_dataset/cam.yaml");
  const auto [_, data] = cl.load();

  const auto answer = YAML::LoadFile("../tests/pose_initializer_dataset/pose02.yaml");

  tsfm::PinholeCamera pc;
  pc.setIntrinsic(data);

  const auto pose = pi(img1, img2, pc);
  float sign = 1.F;
  tsfm::Vec4 ans_quat{answer["rx"].as<double>(), answer["ry"].as<double>(), answer["rz"].as<double>(), answer["rw"].as<double>()};
  ans_quat = tsfm::normalize(ans_quat);

  EXPECT_NEAR(pose.quat()[0], sign * ans_quat[0], 1e-1);
  EXPECT_NEAR(pose.quat()[1], sign * ans_quat[1], 1e-1);
  EXPECT_NEAR(pose.quat()[2], sign * ans_quat[2], 1e-1);
  EXPECT_NEAR(pose.quat()[3], sign * ans_quat[3], 1e-1);
  tsfm::Vec3 t{answer["tx"].as<double>(), answer["ty"].as<double>(), answer["tz"].as<double>()};
  t = t / tsfm::norm(t);
  EXPECT_NEAR(pose.trans()[0], t[0], 5e-1);
  EXPECT_NEAR(pose.trans()[1], t[1], 5e-1);
  EXPECT_NEAR(pose.trans()[2], t[2], 5e-1);
}
