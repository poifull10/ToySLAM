#pragma once

#include "../geo_primitive/vector.h"

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

class Point
{
public:
  Point(Vec3 x) : X_(x) {}
  ~Point() = default;
  Point(const Point&) = delete;
  Point(const Point&&) = default;
  Point& operator=(const Point&) = delete;
  Point& operator=(const Point&&) = default;

  Vec3& X() { return X_; }
  PointID id() const { return id_; }

private:
  Vec3 X_;
  PointID id_;
};

class PointMaker
{
};

} // namespace tsfm