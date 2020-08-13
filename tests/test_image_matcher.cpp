#include <gtest/gtest.h>
#include <matcher/image_matcher.h>

#include <iostream>

TEST(ImageMatcher, match)
{
  tsfm::ImageMaker maker;
  auto img1 = maker.make("../tests/pose_initializer_dataset/000000.png");
  auto img2 = maker.make("../tests/pose_initializer_dataset/000001.png");
  auto img3 = maker.make("../tests/pose_initializer_dataset/000002.png");
  img1->load();
  img2->load();
  tsfm::ImageMatcher im({img1, img2});
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

  img3->load();
  tsfm::ImageMatcher im2({img1, img2, img3});
  im2.extractFeatures();
  im2.match();
  im2.drawMatch("match3.png");
}