#include "image_matcher.h"

#include <opencv2/features2d.hpp>   // NOLINT
#include <opencv2/opencv.hpp>       // NOLINT
#include <opencv2/xfeatures2d.hpp>  // NOLINT
#include <random>

namespace tsfm {

class ImageMatcher::Impl {
 public:
  Impl() = default;
  ~Impl() = default;

  void extractFeatures(const std::vector<std::shared_ptr<Image>>& images) {
    const auto detector = cv::ORB::create(2000);

    for (const auto& image : images) {
      std::vector<cv::KeyPoint> keypoint;
      cv::Mat desc;
      detector->detectAndCompute(image->image(), cv::noArray(), keypoint, desc);
      imageIds_.emplace_back(image->id());
      keypoints_.emplace_back(keypoint);
      descriptors_.emplace_back(desc);
    }
  }

  std::vector<MatchResult> match() {
    const auto matcher = cv::BFMatcher(cv::NORM_HAMMING, false);
    std::vector<std::vector<cv::DMatch>> match;
    const int numOfMatch = 2;
    const float ratio_thresh = 0.7f;

    matcher.knnMatch(descriptors_[0], descriptors_[1], match, numOfMatch);

    for (size_t i = 0; i < match.size(); i++) {
      if (match[i][0].distance >= ratio_thresh * match[i][1].distance) {
        continue;
      }
      MatchResult mr;
      mr.keypoints.push_back(Vec2{keypoints_[0][match[i][0].queryIdx].pt.x, keypoints_[0][match[i][0].queryIdx].pt.y});
      mr.keypoints.push_back(Vec2{keypoints_[1][match[i][0].trainIdx].pt.x, keypoints_[1][match[i][0].trainIdx].pt.y});
      mr.imageIds.emplace_back(imageIds_[0]);
      mr.imageIds.emplace_back(imageIds_[1]);

      cv::Mat desc = descriptors_[1].row(match[i][0].trainIdx);
      for (size_t j = 1; j < descriptors_.size() - 1; j++) {
        std::vector<std::vector<cv::DMatch>> nestMatch;
        matcher.knnMatch(desc, descriptors_[j + 1], nestMatch, numOfMatch);
        if (nestMatch[0][0].distance >= ratio_thresh * nestMatch[0][1].distance) {
          continue;
        }
        mr.keypoints.emplace_back(Vec2{keypoints_[j + 1][nestMatch[0][0].trainIdx].pt.x, keypoints_[j + 1][nestMatch[0][0].trainIdx].pt.y});
        mr.imageIds.emplace_back(imageIds_[j + 1]);
        desc = descriptors_[j + 1].row(nestMatch[0][0].trainIdx);
      }
      matches_.push_back(mr);
    }

    return matches_;
  }

  void drawMatch(const std::vector<std::shared_ptr<Image>>& images, const fs::path& path) {
    std::random_device seed_gen;
    std::default_random_engine engine(seed_gen());
    std::uniform_int_distribution<> rand(0, 255);

    cv::Mat dst = images.front()->image();
    const auto firstId = images.front()->id().toInt();
    const auto width = images.front()->width();
    const auto height = images.front()->height();

    for (size_t i = 1; i < images.size(); i++) {
      cv::vconcat(dst, images[i]->image(), dst);
    }

    for (const auto& match : matches_) {
      const auto r = rand(engine);
      const auto g = rand(engine);
      const auto b = rand(engine);
      assert(match.imageIds.size() == match.keypoints.size());
      for (size_t i = 0; i < match.imageIds.size() - 1; i++) {
        const auto fromIdx = match.imageIds[i].toInt();
        const auto toIdx = match.imageIds[i + 1].toInt();
        const auto fromV = match.keypoints[i];
        const auto toV = match.keypoints[i + 1];
        const auto fromRow = fromIdx - firstId;
        const auto toRow = toIdx - firstId;
        cv::line(dst, cv::Point{static_cast<int>(fromV[0] + .5), static_cast<int>(fromV[1] + height * fromRow + .5)},
                 cv::Point{static_cast<int>(toV[0] + .5), static_cast<int>(toV[1] + height * toRow + .5)}, cv::Scalar(b, g, r));
        cv::circle(dst, cv::Point{static_cast<int>(fromV[0] + .5), static_cast<int>(fromV[1] + height * fromRow + .5)}, 3, cv::Scalar(b, g, r));
        cv::circle(dst, cv::Point{static_cast<int>(toV[0] + .5), static_cast<int>(toV[1] + height * toRow + .5)}, 3, cv::Scalar(b, g, r));
      }
    }
    cv::imwrite(path.string(), dst);
  }

  std::vector<std::vector<cv::KeyPoint>> keypoints_;
  std::vector<ImageID> imageIds_;
  std::vector<cv::Mat> descriptors_;
  std::vector<MatchResult> matches_;
};

ImageMatcher::ImageMatcher(const std::vector<std::shared_ptr<Image>>& images) : images_(images), impl_(std::make_unique<Impl>()) {}

ImageMatcher::~ImageMatcher() {}

void ImageMatcher::extractFeatures() {
  impl_->extractFeatures(images_);
}
std::vector<MatchResult> ImageMatcher::match() {
  return impl_->match();
}

void ImageMatcher::drawMatch(const fs::path& path) {
  impl_->drawMatch(images_, path);
}

}  // namespace tsfm
