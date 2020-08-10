#include "image_matcher.h"

#include <opencv2/features2d.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>

namespace tsfm
{

class ImageMatcher::Impl
{
public:
  Impl() = default;
  ~Impl() = default;

  void extractFeatures(const std::shared_ptr<Image>& image1,
                       const std::shared_ptr<Image>& image2)
  {
    const auto siftDetector = cv::xfeatures2d::SURF::create(2000);
    std::vector<cv::KeyPoint> keypoint1, keypoint2;
    cv::Mat desc1, desc2;
    siftDetector->detectAndCompute(image1->image(), cv::noArray(), keypoint1,
                                   desc1);
    siftDetector->detectAndCompute(image2->image(), cv::noArray(), keypoint2,
                                   desc2);
    keypoints_ = {keypoint1, keypoint2};
    descriptors_ = {desc1, desc2};
  }

  std::vector<std::tuple<Vec2, Vec2>> match(
    const std::shared_ptr<Image>& image1, const std::shared_ptr<Image>& image2)
  {
    const auto [desc1, desc2] = descriptors_;
    const auto matcher =
      cv::DescriptorMatcher::create(cv::DescriptorMatcher::FLANNBASED);
    std::vector<std::vector<cv::DMatch>> knnMatches;
    const int numOfMatch = 2;
    matcher->knnMatch(desc1, desc2, knnMatches, numOfMatch);

    const float ratio_thresh = 0.7f;
    std::vector<std::tuple<Vec2, Vec2>> matches;
    const auto [keyPoint1, keyPoint2] = keypoints_;
    for (size_t i = 0; i < knnMatches.size(); i++)
    {
      if (knnMatches[i][0].distance < ratio_thresh * knnMatches[i][1].distance)
      {
        const auto pt1 = keyPoint1[knnMatches[i][0].queryIdx].pt;
        const auto pt2 = keyPoint2[knnMatches[i][0].trainIdx].pt;
        matches.emplace_back(tsfm::Vec2{pt1.x, pt1.y},
                             tsfm::Vec2{pt2.x, pt2.y});
        matches_.push_back(knnMatches[i][0]);
      }
    }
    return matches;
  }

  void drawMatch(const std::shared_ptr<Image>& image1,
                 const std::shared_ptr<Image>& image2, const fs::path& path)
  {
    const auto [keyPoint1, keyPoint2] = keypoints_;
    cv::Mat imgMatches;
    drawMatches(image1->image(), keyPoint1, image2->image(), keyPoint2,
                matches_, imgMatches, cv::Scalar::all(-1), cv::Scalar::all(-1),
                std::vector<char>(),
                cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
    cv::imwrite(path.string(), imgMatches);
  }

  std::tuple<std::vector<cv::KeyPoint>, std::vector<cv::KeyPoint>> keypoints_;
  std::tuple<cv::Mat, cv::Mat> descriptors_;
  std::vector<cv::DMatch> matches_;
};

ImageMatcher::ImageMatcher(std::shared_ptr<Image> image1,
                           std::shared_ptr<Image> image2)
  : image1_(image1), image2_(image2), impl_(std::make_unique<Impl>())
{
}

ImageMatcher::~ImageMatcher() {}

void ImageMatcher::extractFeatures()
{
  impl_->extractFeatures(image1_, image2_);
}
std::vector<std::tuple<Vec2, Vec2>> ImageMatcher::match()
{
  return impl_->match(image1_, image2_);
}

void ImageMatcher::drawMatch(const fs::path& path)
{
  impl_->drawMatch(image1_, image2_, path);
}

} // namespace tsfm
