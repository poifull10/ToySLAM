#include <Eigen/Core>              // NOLINT
#include <Eigen/Geometry>          // NOLINT
#include <opencv2/core/eigen.hpp>  // NOLINT
#include <opencv2/opencv.hpp>      // NOLINT
#include <utility>

#include "../image/frame.h"
#include "../matcher/image_matcher.h"
#include "../util/cv_primitive.h"
#include "pose_initializer.h"

namespace tsfm {
Pose Tracker::operator()(const std::shared_ptr<Frame>& srcFrame, const std::shared_ptr<Frame>& dstFrame, const CameraModel& cm) const {
  ImageMatcher im({srcFrame->image(), dstFrame->image()});
  im.extractFeatures();
  const auto& matched = im.match();
  assert(matched.size() >= 5);

  const auto& [pointsSrcFrame, pointsDstFrame] = [&matched]() {
    std::vector<cv::Point2f> points1, points2;
    for (const auto [keypoints, _] : matched) {
      const auto v1 = keypoints[0];
      const auto v2 = keypoints[1];
      points1.emplace_back(v1[0], v1[1]);
      points2.emplace_back(v2[0], v2[1]);
    }
    return std::make_pair(points1, points2);
  }();

  const cv::Mat K = cm.K();
  const cv::Mat E = cv::findEssentialMat(pointsSrcFrame, pointsDstFrame, K);
  cv::Mat R, t;
  cv::recoverPose(E, pointsSrcFrame, pointsDstFrame, K, R, t);
  const auto quat = CvRotToQuat(R);
  return Pose(normalize(Vec3{t.at<double>(0, 0), t.at<double>(1, 0), t.at<double>(2, 0)}), normalize(quat));
}
}  // namespace tsfm
