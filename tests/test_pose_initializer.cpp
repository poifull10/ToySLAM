#include <camera_model/pinhole_camera.h>
#include <glog/logging.h>
#include <gtest/gtest.h>
#include <image/frame.h>
#include <image/image.h>
#include <initializer/pose_initializer.h>
#include <matcher/image_matcher.h>
#include <util/load_data.h>
#include <yaml-cpp/yaml.h>

#include <iostream>

TEST(PoseInitializer, estimatePose)
{
  tsfm::PoseInitializer pi;
  tsfm::FrameMaker maker;
  auto frame1 = maker.make("../tests/pose_initializer_dataset/000000.png");
  auto frame2 = maker.make("../tests/pose_initializer_dataset/000002.png");

  tsfm::CalibrationLoader cl("../tests/pose_initializer_dataset/cam.yaml");
  const auto [_, data] = cl.load();

  const auto answer = YAML::LoadFile("../tests/pose_initializer_dataset/pose02.yaml");

  tsfm::PinholeCamera pc;
  pc.setIntrinsic(data);

  const auto pose = pi(frame1, frame2, pc);
  float sign = 1.F;
  tsfm::Vec4 ans_quat{answer["rx"].as<double>(), answer["ry"].as<double>(), answer["rz"].as<double>(), answer["rw"].as<double>()};
  ans_quat = tsfm::normalize(ans_quat);
  tsfm::Vec3 ans_t{answer["tx"].as<double>(), answer["ty"].as<double>(), answer["tz"].as<double>()};
  ans_t = tsfm::normalize(ans_t);

  EXPECT_NEAR(pose.quat()[0], sign * ans_quat[0], 1e-1);
  EXPECT_NEAR(pose.quat()[1], sign * ans_quat[1], 1e-1);
  EXPECT_NEAR(pose.quat()[2], sign * ans_quat[2], 1e-1);
  EXPECT_NEAR(pose.quat()[3], sign * ans_quat[3], 1e-1);
  EXPECT_NEAR(pose.trans()[0], ans_t[0], 3e-1);
  EXPECT_NEAR(pose.trans()[1], ans_t[1], 3e-1);
  EXPECT_NEAR(pose.trans()[2], ans_t[2], 3e-1);
}
