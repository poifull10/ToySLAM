#pragma once
#include <opencv2/opencv.hpp>
#include <optional>
#include <string>

namespace tsfm
{
class Image
{
public:
  Image(const std::string& path) : fpath(path) {}

  cv::Mat image() const { return *image_; }
  void load()
  {
    if (image_)
    {
      return;
    }
    image_ = cv::imread(fpath);
  }
  void unload() { image_.reset(); }

private:
  std::string fpath;
  std::optional<cv::Mat> image_;
};
} // namespace tsfm
