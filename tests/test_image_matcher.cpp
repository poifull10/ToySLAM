#include <gtest/gtest.h>
#include <matcher/image_matcher.h>

TEST(ImageMatcher, match)
{
  tsfm::Image img1("../tests/pose_initializer_dataset/000000.png");
  tsfm::Image img2("../tests/pose_initializer_dataset/000001.png");
  img1.load();
  img2.load();
  const auto img_ptr1 = std::make_shared<tsfm::Image>(img1);
  const auto img_ptr2 = std::make_shared<tsfm::Image>(img2);
  tsfm::ImageMatcher im(img_ptr1, img_ptr2);
  im.extractFeatures();
  const auto matched = im.match();
  im.drawMatch("match_result.png");

  for (const auto [v1, v2] : matched)
  {
    EXPECT_GT(v1[0], v2[0]);
    EXPECT_NEAR(v1[1], v2[1], 3.F);
  }
}