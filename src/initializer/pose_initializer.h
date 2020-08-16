#pragma once

#include <memory>

#include "../camera_model/camera_model.h"
#include "../geo_primitive/pose.h"
#include "../image/frame.h"
#include "../image/image.h"

namespace tsfm
{
class PoseInitializer
{
public:
  PoseInitializer() {}
  Pose operator()(const std::shared_ptr<Frame>& src, const std::shared_ptr<Frame>& dst, const CameraModel& cm) const;
};
} // namespace tsfm
