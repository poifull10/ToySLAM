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
  Pose operator()(const std::shared_ptr<Image>& src, const std::shared_ptr<Image>& dst, const CameraModel& cm) const;
};
} // namespace tsfm
