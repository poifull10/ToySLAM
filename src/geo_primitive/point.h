#pragma once

#include "../geo_primitive/vector.h"

namespace tsfm
{
class PointID
{
public:
  PointID(size_t id) : id_(id) {}
  ~PointID() = default;

  size_t toSizeT() const { return id_; }
  int toInt() const { return static_cast<int>(id_); }

private:
  size_t id_;
};

class Point
{
public:
  Point(Vec3 x, size_t id) : X_(x), id_(id) {}
  ~Point() = default;

  Vec3& X() { return X_; }
  PointID id() { return id_; }

private:
  Vec3 X_;
  PointID id_;
};

class PointMaker
{
public:
  PointMaker() = default;
  ~PointMaker() = default;
  std::shared_ptr<Point> make() { return std::make_shared<Point>(Vec3(), id_++); }

private:
  size_t id_ = 0;
};

} // namespace tsfm