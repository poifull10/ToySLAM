#pragma once
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>

namespace Eigen {
template <typename T, int N>
using Vector = Matrix<T, N, 1>;
}
