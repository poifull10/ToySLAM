#include "bundle_adjustment.h"

#include <iostream>

#include "../image/image.h"
#include "../initializer/pose_initializer.h"
#include "../matcher/image_matcher.h"
#include "../util/cv_primitive.h"

namespace tsfm
{

class BundleAdjustment::Impl
{
public:
  Impl() {}
  ~Impl() {}
};

BundleAdjustment::BundleAdjustment(std::vector<std::shared_ptr<Frame>> frames, std::vector<std::shared_ptr<CameraModel>> cameraModels)
  : frames_(frames), cameraModels_(cameraModels), impl_(std::make_unique<Impl>()), pointMaker_()
{
}
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

  PoseInitializer poseInitializer;
  for (size_t i = 1; i < frames_.size(); i++)
  {
    const auto estimatedPose = poseInitializer(frames_.front(), frames_[i], *(cameraModels_[i - 1]));
    frames_[i]->setPose(estimatedPose);
  }

  std::vector<std::shared_ptr<Image>> images;
  for (auto& frame : frames_)
  {
    images.emplace_back(frame->image());
  }

  ImageMatcher imageMatcher(images);
  imageMatcher.extractFeatures();
  const auto matches = imageMatcher.match();

  for (const auto& match : matches)
  {
    assert(match.keypoints.size() >= 2);
    const auto kpt1 = match.keypoints[0];
    const auto kpt2 = match.keypoints[1];
    const auto camId1 = match.imageIds[0];
    const auto camId2 = match.imageIds[1];
    auto srcFrame = frames_[camId1.toSizeT()];
    auto dstFrame = frames_[camId2.toSizeT()];
    cv::Mat point4d;
    cv::triangulatePoints(srcFrame->P(), dstFrame->P(), vec2ToCvMat(kpt1, false), vec2ToCvMat(kpt2, false), point4d);
    auto point = pointMaker_.make();
    const auto a = point4d.at<double>(0, 0);
    const auto b = point4d.at<double>(1, 0);
    const auto c = point4d.at<double>(2, 0);
    const auto d = point4d.at<double>(3, 0);
    point->X() = {a / d, b / d, c / d};
    points_.emplace_back(point);
    std::vector<std::tuple<ImageID, Vec2>> imgpoints;
    for (size_t i = 0; i < match.keypoints.size(); i++)
    {
      imgpoints.push_back({match.imageIds[i], match.keypoints[i]});
    }
    VisualObservation vo{vo.id = point->id(), imgpoints};
    visualObservations_.emplace_back(vo);
  }
}

double BundleAdjustment::optimize(size_t N, double lambda)
{
  return 0.;
}

} // namespace tsfm
