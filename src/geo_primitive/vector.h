#pragma once
#include <initializer_list>
#include <vector>

namespace tsfm
{
template <typename T, int N>
class Vector
{
public:
  Vector(const std::array<T, N> data) : data_(data) {}
  Vector(std::initializer_list<T> init)
  {
    int cnt = 0;
    for (auto e : init)
    {
      data_[cnt++] = e;
    }
  }
  ~Vector() = default;
  Vector(Vector&&) = default;
  Vector(const Vector&) = default;
  Vector& operator=(Vector&) = default;
  T operator[](int i) const { return data_[i]; }

private:
  std::array<T, N> data_;
};

using Vec2 = Vector<double, 2>;
using Vec3 = Vector<double, 3>;
} // namespace tsfm