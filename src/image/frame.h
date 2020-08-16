#pragma once

#include <boost/filesystem/path.hpp>
#include <memory>
#include <opencv2/opencv.hpp>
#include <vector>

#include "../camera_model/camera_model.h"
#include "../geo_primitive/pose.h"
#include "image.h"

namespace tsfm
{
namespace fs = boost::filesystem;
class Frame
{
public:
  Frame(const fs::path& imgPath, const std::shared_ptr<CameraModel> cm, size_t id) : image_(imgPath, id), cameraModel_(cm), pose_() {}
  std::shared_ptr<Image> image()
  {
    image_.load();
    return std::make_shared<Image>(image_);
  }
  Pose pose() const { return pose_; }
  void setPose(const Pose& pose) { pose_ = pose; }
  void setCameraModel(std::shared_ptr<CameraModel> cm) { cameraModel_ = cm; }
  void unload() { image_.unload(); }
  cv::Mat P();
  cv::Mat K();

private:
  Image image_;
  Pose pose_;
  std::shared_ptr<CameraModel> cameraModel_;
};

class FrameMaker
{
public:
  FrameMaker() = default;
  FrameMaker(const FrameMaker&) = delete;
  FrameMaker(FrameMaker&&) = delete;
  FrameMaker& operator=(const FrameMaker&) = delete;
  FrameMaker& operator=(const FrameMaker&&) = delete;

  std::shared_ptr<Frame> make(const fs::path& path, const std::shared_ptr<CameraModel> cm) { return std::make_shared<Frame>(path, cm, id_++); }
  std::vector<std::shared_ptr<Frame>> make(const std::vector<fs::path>& paths, const std::vector<std::shared_ptr<CameraModel>>& cameraModels)
  {
    std::vector<std::shared_ptr<Frame>> ret;
    assert(paths.size() == cameraModels.size());
    for (size_t i = 0; i < paths.size(); i++)
    {
      const auto path = paths[i];
      const auto cameraModel = cameraModels[i];
      ret.emplace_back(make(path, cameraModel));
    }
    return ret;
  }

private:
  size_t id_ = 0;
};

} // namespace tsfm