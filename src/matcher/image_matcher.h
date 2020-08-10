#pragma once

#include <boost/filesystem/path.hpp>
#include <memory>

#include "../geo_primitive/vector.h"
#include "../image/image.h"

namespace tsfm
{
namespace fs = boost::filesystem;
class ImageMatcher
{
public:
  ImageMatcher(std::shared_ptr<Image> image1, std::shared_ptr<Image> image2);
  ~ImageMatcher();

  void extractFeatures();
  std::vector<std::tuple<Vec2, Vec2>> match();
  void drawMatch(const fs::path& path);

private:
  class Impl;
  std::shared_ptr<Image> image1_, image2_;
  std::unique_ptr<Impl> impl_;
};
} // namespace tsfm
