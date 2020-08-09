#pragma once

#include <boost/filesystem/path.hpp>
#include <string>
#include <unordered_map>

#include "../camera_model/camera_model.h"

namespace tsfm
{
namespace fs = boost::filesystem;

class CalibrationLoader
{
public:
  CalibrationLoader(const fs::path& path) : path_(path) {}
  std::tuple<CameraDistortion, std::unordered_map<std::string, double>> load();

private:
  fs::path path_;
};
} // namespace tsfm