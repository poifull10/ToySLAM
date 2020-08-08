#pragma once

#include <opencv2/opencv.hpp>
#include <string>

#include "../geo_primitive/pose.h"
#include "image.h"

namespace tsfm
{
class Frame
{
public:
  Frame(const std::string& imgPath) : image_(imgPath), pose_() {}
  Image image()
  {
    image.load();
    return image_;
  }
  Pose pose() const { return pose_; }
  void setPose(const Pose& pose) { pose_ = pose; }

private:
  Image image_;
  Pose pose_;
};
} // namespace tsfm