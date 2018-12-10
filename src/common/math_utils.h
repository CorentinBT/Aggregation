#pragma once

#include <random>

#include "vector_math.h"

namespace Math
{

template <typename T>
inline constexpr Vec3<T> sign(const Vec3<T> &x)
{
    return {
        static_cast<T>((0 < x[0]) - (x[0] < 0)),
        static_cast<T>((0 < x[1]) - (x[1] < 0)),
        static_cast<T>((0 < x[2]) - (x[2] < 0))};
}

template <typename T>
Vec3<T> rand_point_sphere(const Vec3<T> &from, const T &rad);

template <typename T>
Vec3<T> rand_point_sphere_angle(const Vec3<T> &from, const T &rad, double alpha, double beta);

} // namespace Math