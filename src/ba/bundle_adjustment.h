#pragma once
#include <memory>
#include <vector>

#include "../camera_model/camera_model.h"
#include "../image/frame.h"

namespace tsfm
{
class BundleAdjustment
{
public:
  BundleAdjustment(double lambda = 1e-2);
  ~BundleAdjustment();

  void addFrame(std::shared_ptr<Frame> frame);
  void addCameraModel(std::shared_ptr<CameraModel> cm);
  void initialization();
  double optimize(size_t N);

private:
  class Impl;
  std::vector<std::shared_ptr<Frame>> frames_;
  std::shared_ptr<CameraModel> cm_;
  double lambda_;
  std::unique_ptr<Impl> impl_;
};
} // namespace tsfm
