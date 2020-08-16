#include "bundle_adjustment.h"

#include "../initializer/pose_initializer.h"

namespace tsfm
{

class BundleAdjustment::Impl
{
public:
  Impl() {}
  ~Impl() {}
};

BundleAdjustment::BundleAdjustment(std::vector<std::shared_ptr<Frame>> frames) : frames_(frames), cameraModels_(), impl_(std::make_unique<Impl>()) {}
BundleAdjustment::~BundleAdjustment(){};

void BundleAdjustment::initialization()
{
  if (frames_.empty())
  {
    return;
  }

  frames_.front()->setPose(Pose());
  if (frames_.size() == 1)
  {
    return;
  }

  PoseInitializer pi;
  for (size_t i = 1; i < frames_.size(); i++)
  {
    const auto estimatedPose = pi(frames_.front(), frames_[i], *(cameraModels_[i - 1]));
    frames_[i]->setPose(estimatedPose);
  }
}

double BundleAdjustment::optimize(size_t N, double lambda)
{
  return 0.;
}

} // namespace tsfm
