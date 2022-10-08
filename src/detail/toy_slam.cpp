#pragma once

#include "toy_slam.h"

#include "../io_data.h"

namespace ToySLAM::detail {
SLAMResult LiDARSLAM::operator()(const RangeFrame& frame) {
  return {};
}
void LiDARSLAM::reset() {
}
}  // namespace ToySLAM::detail
