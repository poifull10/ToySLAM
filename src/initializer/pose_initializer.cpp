#include "pose_initializer.h"

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <opencv2/core/eigen.hpp>
#include <opencv2/opencv.hpp>

#include "../image/frame.h"
#include "../matcher/image_matcher.h"
#include "../util/cv_primitive.h"

namespace tsfm
{
Pose PoseInitializer::operator()(const std::shared_ptr<Frame>& src, const std::shared_ptr<Frame>& dst, const CameraModel& cm) const
{
  ImageMatcher im({src->image(), dst->image()});
  im.extractFeatures();
  const auto& matched = im.match();
  im.drawMatch("match.png");

  assert(matched.size() >= 5);

  std::vector<cv::Point2f> points1, points2;

  for (const auto [keypoints, _] : matched)
  {
    const auto v1 = keypoints[0];
    const auto v2 = keypoints[1];
    points1.emplace_back(v1[0], v1[1]);
    points2.emplace_back(v2[0], v2[1]);
  }

  const cv::Mat K = cm.K();
  const cv::Mat E = cv::findEssentialMat(points1, points2, K);
  cv::Mat R, t;
  cv::recoverPose(E, points1, points2, K, R, t);
  const auto quat = CvRotToQuat(R);

  return Pose(normalize(Vec3{t.at<double>(0, 0), t.at<double>(1, 0), t.at<double>(2, 0)}), normalize(quat));
}
} // namespace tsfm
