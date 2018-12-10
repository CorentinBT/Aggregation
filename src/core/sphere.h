#pragma once

#include <optional>

#include "common/vector_math.h"

namespace Agg::Object
{

using Vec3d = Math::Vec3<double>;
using OptionalVec = std::optional<Vec3d>;

template <typename T>
struct Sphere
{
    Sphere(const Math::Vec3<T> c, T rad) : coord(c), radius(rad){};

    union {
        Math::Vec3<T> coord{};
        T x;
        T y;
        T z;
    };
    T radius{};
};

template <typename T>
double distance(const T &lhs, const T &rhs);

template <typename T>
OptionalVec intersectionPoint(const T &lhs, const T &rhs);

template <typename T>
bool intersects(const T &lhs, const T &rhs);

template <>
inline double distance(const Sphere<double> &lhs, const Sphere<double> &rhs)
{
    return (lhs.coord - rhs.coord).Length();
}

template <>
inline bool intersects(const Sphere<double> &lhs, const Sphere<double> &rhs)
{
    const auto dist = distance(lhs, rhs);
    return dist <= lhs.radius + rhs.radius ? true : false;
}

template <>
inline OptionalVec intersectionPoint(const Sphere<double> &lhs, const Sphere<double> &rhs)
{
    if (intersects(lhs, rhs))
    {
        return lhs.coord + (rhs.coord - lhs.coord) * (lhs.radius / (rhs.radius + lhs.radius));
    }

    return std::nullopt;
}

} // namespace Agg::Object