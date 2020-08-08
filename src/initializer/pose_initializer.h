#pragma once

#include "../geo_primitive/pose.h"
#include "../image/image.h"

namespace tsfm
{
class PoseInitializer
{
public:
  PoseInitializer() = default;
  Pose operator()(const Image& img1, const Image& img2) const;
};
} // namespace tsfm
