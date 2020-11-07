#pragma once

#include <boost/filesystem/path.hpp>
#include <memory>

#include "../image/image.h"
#include "../math/vector.h"

namespace tsfm {
namespace fs = boost::filesystem;

struct MatchResult {
  std::vector<Vec2> keypoints;
  std::vector<ImageID> imageIds;
};

class ImageMatcher {
 public:
  ImageMatcher(const std::vector<std::shared_ptr<Image>>& images);
  ~ImageMatcher();

  void extractFeatures();
  std::vector<MatchResult> match();
  void drawMatch(const fs::path& path);

 private:
  class Impl;
  std::unique_ptr<Impl> impl_;
  std::vector<std::shared_ptr<Image>> images_;
};
}  // namespace tsfm
