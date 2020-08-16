#include <ba/bundle_adjustment.h>
#include <camera_model/camera_model.h>
#include <camera_model/pinhole_camera.h>
#include <gtest/gtest.h>
#include <image/frame.h>
#include <util/load_data.h>

#include <boost/filesystem/path.hpp>

TEST(BA, initialization)
{
  namespace fs = boost::filesystem;
  tsfm::CalibrationLoader cl("../tests/pose_initializer_dataset/cam.yaml");
  const auto [_, data] = cl.load();
  tsfm::PinholeCamera pc;
  pc.setIntrinsic(data);
  std::vector<fs::path> paths = {"../tests/pose_initializer_dataset/000000.png", "../tests/pose_initializer_dataset/000001.png",
                                 "../tests/pose_initializer_dataset/000002.png"};
  std::vector<std::shared_ptr<tsfm::CameraModel>> cameraModels;
  for (const auto &_ : paths)
  {
    cameraModels.emplace_back(std::make_shared<tsfm::PinholeCamera>(pc));
  }

  tsfm::FrameMaker fm;
  auto frames = fm.make(paths, cameraModels);

  tsfm::BundleAdjustment ba(frames, cameraModels);
  ba.initialization();
}