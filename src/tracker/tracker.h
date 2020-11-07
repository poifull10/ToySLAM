#pragma once

#include <memory>

#include "../camera_model/camera_model.h"
#include "../image/frame.h"
#include "../image/image.h"
#include "../math/pose.h"

namespace tsfm {
class Tracker {
 public:
  Tracker() = default;
  Pose operator()(const std::shared_ptr<Frame>& src, const std::shared_ptr<Frame>& dst, const CameraModel& cm) const;
};

}  // namespace tsfm
