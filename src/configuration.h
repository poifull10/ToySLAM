#pragma once

namespace ToySLAM {
class Configuration {
  float voxelResolution = 0.05F;
  float maxRange = 20.0F;
  float minRange = 0.2F;
  int subMapFrameCount = 5;
};
}  // namespace ToySLAM
