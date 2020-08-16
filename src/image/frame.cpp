#include "frame.h"

#include "../util/cv_primitive.h"

namespace tsfm
{

cv::Mat Frame::K()
{
  return cameraModel_->K();
}

cv::Mat Frame::P()
{
  const cv::Mat _K = K();
  const cv::Mat T = poseToCvMat34(pose_);
  return cv::Mat(_K * T);
}
} // namespace tsfm