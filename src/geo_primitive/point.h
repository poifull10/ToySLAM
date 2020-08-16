#pragma once

namespace tsfm
{
class PointID
{
public:
  PointID(size_t id) : id_(id) {}
  PointID(const PointID&) = delete;
  PointID& operator=(const PointID&) = delete;

  size_t toSizeT() const { return id_; }
  int toInt() const { return static_cast<int>(id_); }

private:
  size_t id_;
};
} // namespace tsfm