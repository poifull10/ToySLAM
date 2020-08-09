#include "load_data.h"

#include <yaml-cpp/yaml.h>

namespace tsfm
{
namespace
{
const std::unordered_map<std::string, CameraType> str2CameraType = {
  {"pinhole", CameraType::pinhole}};

const std::unordered_map<std::string, DistortionType> str2DistortionType = {
  {"none", DistortionType::none}};

} // namespace

std::tuple<CameraDistortion, std::unordered_map<std::string, double>>
CalibrationLoader::load()
{
  YAML::Node config = YAML::LoadFile(path_.string());
  const auto cameraType = str2CameraType.at(config["camera"].as<std::string>());
  const auto distortionType =
    str2DistortionType.at(config["distortion"].as<std::string>());

  std::unordered_map<std::string, double> parameters;

  if (cameraType == CameraType::pinhole)
  {
    parameters.insert_or_assign("fx", config["fx"].as<double>());
    parameters.insert_or_assign("fy", config["fy"].as<double>());
    parameters.insert_or_assign("cx", config["cx"].as<double>());
    parameters.insert_or_assign("cy", config["cy"].as<double>());
  }

  if (distortionType == DistortionType::none) {}
  return {{cameraType, distortionType}, parameters};
}
} // namespace tsfm