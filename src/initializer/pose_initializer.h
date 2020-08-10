#pragma once

#include "../camera_model/camera_model.h"
#include "../geo_primitive/pose.h"
#include "../image/image.h"

namespace tsfm
{
class PoseInitializer
{
public:
  PoseInitializer() {}
  Pose operator()(const Image& img1, const Image& img2,
                  const CameraModel& cm) const;
};
} // namespace tsfm
