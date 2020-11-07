#pragma once
#include <algorithm>
#include <cmath>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <numeric>
#include <vector>

namespace tsfm {

template <typename T, int N>
class Vector {
  using Iterator = typename std::array<T, N>::iterator;
  using ConstIterator = typename std::array<T, N>::const_iterator;

 public:
  Vector() : data_() {}
  Vector(const std::array<T, N>& data) : data_(data) {}
  Vector(std::initializer_list<T> init) {
    int cnt = 0;
    for (const auto& e : init) {
      data_[cnt++] = e;
    }
  }
  ~Vector() = default;
  Vector(Vector&&) = default;
  Vector(const Vector&) = default;
  auto operator=(const Vector&) -> Vector& = default;
  [[nodiscard]] auto operator[](int i) const -> T { return data_[i]; }
  [[nodiscard]] auto operator[](size_t i) const -> T { return data_[i]; }

  friend auto operator<<(std::ostream& os, const Vector& p) -> std::ostream& {
    for (size_t i = 0; i < N - 1; i++) {
      os << p.data_[i] << " ";
    }
    os << p.data_[N - 1];
    return os;
  }

  Iterator begin() { return data_.begin(); }
  Iterator end() { return data_.end(); }
  ConstIterator cbegin() const { return data_.cbegin(); }
  ConstIterator cend() const { return data_.cend(); }

 private:
  std::array<T, N> data_;
};

template <typename T, int N>
auto norm(const Vector<T, N>& v) -> double {
  return std::sqrt(std::accumulate(v.cbegin(), v.cend(), T(), [](const auto& value, const auto& e) { return value + e * e; }));
};

template <typename T, int N>
auto operator*(const Vector<T, N>& v, T val) -> Vector<T, N> {
  std::array<T, N> data;
  std::transform(v.cbegin(), v.cend(), data.begin(), [&val](const auto& e) { return e * val; });
  return Vector<T, N>(data);
}

template <typename T, int N>
auto operator/(const Vector<T, N>& v, T val) -> Vector<T, N> {
  std::array<T, N> data;
  std::transform(v.cbegin(), v.cend(), data.begin(), [&val](const auto& e) { return e / val; });
  return Vector<T, N>(data);
}

template <typename T, int N>
auto normalize(const Vector<T, N>& v) -> Vector<T, N> {
  return v / tsfm::norm(v);
}

using Vec2 = Vector<double, 2>;
using Vec3 = Vector<double, 3>;
using Vec4 = Vector<double, 4>;
}  // namespace tsfm
