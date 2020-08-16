#include <gtest/gtest.h>
#include <image/frame.h>
#include <matcher/image_matcher.h>

#include <iostream>

TEST(ImageMatcher, match)
{
  tsfm::FrameMaker maker;
  auto frame1 = maker.make("../tests/pose_initializer_dataset/000000.png");
  auto frame2 = maker.make("../tests/pose_initializer_dataset/000001.png");
  auto frame3 = maker.make("../tests/pose_initializer_dataset/000002.png");
  tsfm::ImageMatcher im({frame1->image(), frame2->image()});
  im.extractFeatures();
  const auto matched = im.match();

  for (const auto match : matched)
  {
    const auto v1 = match.keypoints[0];
    const auto v2 = match.keypoints[1];
    EXPECT_GT(v1[0], v2[0]);
    EXPECT_NEAR(v1[1], v2[1], 3.);
  }
  im.drawMatch("match2.png");

  tsfm::ImageMatcher im2({frame1->image(), frame2->image(), frame3->image()});
  im2.extractFeatures();
  im2.match();
  im2.drawMatch("match3.png");
}