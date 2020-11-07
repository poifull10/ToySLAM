#pragma once
#include <opencv2/opencv.hpp>  // NOLINT
#include <string>

#include "../math/pose.h"
#include "image.h"

namespace tsfm {
namespace fs = boost::filesystem;
class Frame {
 public:
  Frame(const fs::path& imgPath, size_t id) : image_(imgPath, id), pose_() {}
  std::shared_ptr<Image> image() {
    image_.load();
    return std::make_shared<Image>(image_);
  }
  Pose pose() const { return pose_; }
  void setPose(const Pose& pose) { pose_ = pose; }
  void unload() { image_.unload(); }

 private:
  Image image_;
  Pose pose_;
};

class FrameMaker {
 public:
  FrameMaker() = default;
  FrameMaker(const FrameMaker&) = delete;
  FrameMaker(FrameMaker&&) = delete;
  FrameMaker& operator=(const FrameMaker&) = delete;
  FrameMaker& operator=(const FrameMaker&&) = delete;

  std::shared_ptr<Frame> make(const fs::path& path) { return std::make_shared<Frame>(path, id_++); }
  std::vector<std::shared_ptr<Frame>> make(const std::vector<fs::path>& paths) {
    std::vector<std::shared_ptr<Frame>> ret;
    for (const auto path : paths) {
      ret.emplace_back(make(path));
    }
    return ret;
  }

 private:
  size_t id_ = 0;
};

}  // namespace tsfm
