#pragma once
#include <memory>
#include <tuple>
#include <vector>

#include "../camera_model/camera_model.h"
#include "../geo_primitive/point.h"
#include "../geo_primitive/pose.h"
#include "../geo_primitive/vector.h"
#include "../image/frame.h"
#include "../image/image.h"

namespace tsfm
{

struct VisualObservation
{
  PointID id_;
  std::vector<std::tuple<ImageID, Vec2>> points;
};

class BundleAdjustment
{
public:
  BundleAdjustment(std::vector<std::shared_ptr<Frame>> frames, std::vector<std::shared_ptr<CameraModel>> cameraModels);
  ~BundleAdjustment();
  BundleAdjustment(BundleAdjustment&&) = default;
  BundleAdjustment& operator=(BundleAdjustment&&) = default;
  BundleAdjustment(const BundleAdjustment&) = delete;
  BundleAdjustment& operator=(const BundleAdjustment&) = delete;

  void addFrame(std::shared_ptr<Frame>&& frame) { frames_.emplace_back(frame); }
  void setFrames(std::vector<std::shared_ptr<Frame>>&& frames) { frames_ = std::move(frames); }
  void addCameraModel(std::shared_ptr<CameraModel>&& cameraModel) { cameraModels_.emplace_back(cameraModel); }
  void setCameraModels(std::vector<std::shared_ptr<CameraModel>>&& cameraModels) { cameraModels_ = std::move(cameraModels); }
  void initialization();
  double optimize(size_t N, double lambda = 1e-3F);

  std::vector<std::shared_ptr<Frame>> frames() const { return frames_; }
  std::vector<std::shared_ptr<CameraModel>> cameraModels() const { return cameraModels_; }
  std::vector<std::shared_ptr<Point>> points() const { return points_; }

private:
  class Impl;
  std::vector<VisualObservation> observations_;
  std::vector<std::shared_ptr<Frame>> frames_;
  std::vector<std::shared_ptr<CameraModel>> cameraModels_;
  std::vector<std::shared_ptr<Point>> points_;
  std::unique_ptr<Impl> impl_;
  PointMaker pointMaker_;
};
} // namespace tsfm
