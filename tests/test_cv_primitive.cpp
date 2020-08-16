#include <gtest/gtest.h>
#include <util/cv_primitive.h>

TEST(CVPrimitive, poseToCvMat)
{
  cv::Mat ans = cv::Mat::eye(4, 4, CV_64F);
  ans.at<double>(0, 0) = 0.7058823529411764;
  ans.at<double>(0, 1) = -0.05882352941176469;
  ans.at<double>(0, 2) = 0.7058823529411765;
  ans.at<double>(1, 0) = -0.47058823529411764;
  ans.at<double>(1, 1) = 0.7058823529411764;
  ans.at<double>(1, 2) = 0.5294117647058824;
  ans.at<double>(2, 0) = -0.5294117647058824;
  ans.at<double>(2, 1) = -0.7058823529411764;
  ans.at<double>(2, 2) = 0.47058823529411764;
  ans.at<double>(0, 3) = -3.4;
  ans.at<double>(1, 3) = 37.9;
  ans.at<double>(2, 3) = -114;

  tsfm::Pose pose({-3.4, 37.9, -114}, {0.36380343755449945, -0.36380343755449945, 0.1212678125181665, -0.8488746876271654});
  cv::Mat actual = tsfm::poseToCvMat(pose);

  for (size_t i = 0; i < 4; i++)
  {
    for (size_t j = 0; j < 4; j++)
    {
      EXPECT_NEAR(actual.at<double>(i, j), ans.at<double>(i, j), 1e-3);
    }
  }
}
