#pragma once
#include <boost/filesystem/path.hpp>  // NOLINT
#include <opencv2/opencv.hpp>         // NOLINT
#include <optional>
#include <string>
#include <vector>

namespace tsfm {
namespace fs = boost::filesystem;

class ImageID {
 public:
  explicit ImageID(size_t id) : id_(id) {}
  size_t toSizeT() const { return id_; }
  int toInt() const { return static_cast<int>(id_); }

 private:
  size_t id_;
};

class Image {
 public:
  Image(const fs::path& path, size_t id) : fpath_(path), id_(id) {}
  ~Image() = default;

  cv::Mat image() const { return *image_; }
  void load() {
    if (image_) {
      return;
    }
    image_ = cv::imread(fpath_.string());
  }
  void unload() { image_.reset(); }
  ImageID id() { return id_; }
  size_t width() const { return image_.value().cols; }
  size_t height() const { return image_.value().rows; }

 private:
  fs::path fpath_;
  ImageID id_;
  std::optional<cv::Mat> image_;
};

}  // namespace tsfm
