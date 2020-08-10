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
  BundleAdjustment(double lambda = 1e-2) : frames_(), cm_(), lambda_(lambda) {}
  ~BundleAdjustment() = default;

  void addFrame(std::shared_ptr<Frame> frame);
  void addCameraModel(std::shared_ptr<CameraModel> cm);
  void initialization();
  double optimize(size_t N);

private:
  std::vector<std::shared_ptr<Frame>> frames_;
  std::shared_ptr<CameraModel> cm_;
  double lambda_;
};
} // namespace tsfm
