#pragma once
#include <boost/filesystem/path.hpp>
#include <opencv2/opencv.hpp>
#include <optional>
#include <string>

namespace tsfm
{
namespace fs = boost::filesystem;
class Image
{
public:
  Image(const fs::path& path, size_t id) : fpath_(path), id_(id) {}
  ~Image() = default;

  cv::Mat image() const { return *image_; }
  void load()
  {
    if (image_)
    {
      return;
    }
    image_ = cv::imread(fpath_.string());
  }
  void unload() { image_.reset(); }
  size_t id() { return id_; }

private:
  fs::path fpath_;
  size_t id_;
  std::optional<cv::Mat> image_;
};

class ImageMaker
{
public:
  ImageMaker() = default;
  ImageMaker(const ImageMaker&) = delete;
  ImageMaker(ImageMaker&&) = delete;
  ImageMaker& operator=(const ImageMaker&) = delete;
  ImageMaker& operator=(const ImageMaker&&) = delete;

  std::shared_ptr<Image> make(const fs::path& path) { return std::make_shared<Image>(path, id_++); }

private:
  size_t id_ = 0;
};
} // namespace tsfm
