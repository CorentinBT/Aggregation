// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

// Copyright 2014 Tony Wasserka
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the owner nor the names of its contributors may
//       be used to endorse or promote products derived from this software
//       without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#pragma once

#include <cmath>
#include <type_traits>

namespace Math
{

template <typename T>
class Vec2;
template <typename T>
class Vec3;
template <typename T>
class Vec4;

template <typename T>
class Vec2
{
  public:
    T x{};
    T y{};

    constexpr Vec2() = default;
    constexpr Vec2(const T &x_, const T &y_) : x(x_), y(y_) {}

    template <typename T2>
    constexpr Vec2<T2> Cast() const
    {
        return Vec2<T2>(static_cast<T2>(x), static_cast<T2>(y));
    }

    static constexpr Vec2 AssignToAll(const T &f)
    {
        return Vec2{f, f};
    }

    constexpr Vec2<decltype(T{} + T{})> operator+(const Vec2 &other) const
    {
        return {x + other.x, y + other.y};
    }
    constexpr Vec2 &operator+=(const Vec2 &other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }
    constexpr Vec2<decltype(T{} - T{})> operator-(const Vec2 &other) const
    {
        return {x - other.x, y - other.y};
    }
    constexpr Vec2 &operator-=(const Vec2 &other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    constexpr Vec2<decltype(T{} * T{})> operator*(const Vec2 &other) const
    {
        return {x * other.x, y * other.y};
    }

    template <typename V>
    constexpr Vec2<decltype(T{} * V{})> operator*(const V &f) const
    {
        return {x * f, y * f};
    }

    template <typename V>
    constexpr Vec2 &operator*=(const V &f)
    {
        *this = *this * f;
        return *this;
    }

    template <typename V>
    constexpr Vec2<decltype(T{} / V{})> operator/(const V &f) const
    {
        return {x / f, y / f};
    }

    template <typename V>
    constexpr Vec2 &operator/=(const V &f)
    {
        *this = *this / f;
        return *this;
    }

    constexpr T Length2() const
    {
        return x * x + y * y;
    }

    // Only implemented for T=double
    double Length() const;
    double Normalize(); // returns the previous length, which is often useful

    constexpr T &operator[](std::size_t i)
    {
        return *((&x) + i);
    }
    constexpr const T &operator[](std::size_t i) const
    {
        return *((&x) + i);
    }

    constexpr void SetZero()
    {
        x = 0;
        y = 0;
    }
};

template <typename T, typename V>
constexpr Vec2<T> operator*(const V &f, const Vec2<T> &vec)
{
    return Vec2<T>(f * vec.x, f * vec.y);
}

using Vec2f = Vec2<double>;

template <>
inline double Vec2<double>::Length() const
{
    return std::sqrt(x * x + y * y);
}

template <>
inline double Vec2<double>::Normalize()
{
    double length = Length();
    *this /= length;
    return length;
}

template <typename T>
class Vec3
{
  public:
    T x{};
    T y{};
    T z{};

    constexpr Vec3() = default;
    constexpr Vec3(const T &x_, const T &y_, const T &z_) : x(x_), y(y_), z(z_) {}

    template <typename T2>
    constexpr Vec3<T2> Cast() const
    {
        return Vec3<T2>(static_cast<T2>(x), static_cast<T2>(y), static_cast<T2>(z));
    }

    static constexpr Vec3 AssignToAll(const T &f)
    {
        return Vec3(f, f, f);
    }

    constexpr bool operator>=(const Vec3 &other) const
    {
        return x >= other.x && y >= other.y && z >= other.z;
    }

    constexpr bool operator<=(const Vec3 &other) const
    {
        return x <= other.x && y <= other.y && z <= other.z;
    }

    constexpr bool operator>(const Vec3 &other) const
    {
        return x > other.x && y > other.y && z > other.z;
    }

    constexpr bool operator<(const Vec3 &other) const
    {
        return x < other.x && y < other.y && z < other.z;
    }

    constexpr Vec3<decltype(T{} + T{})> operator+(const Vec3 &other) const
    {
        return {x + other.x, y + other.y, z + other.z};
    }

    constexpr Vec3 &operator+=(const Vec3 &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    constexpr Vec3<decltype(T{} - T{})> operator-(const Vec3 &other) const
    {
        return {x - other.x, y - other.y, z - other.z};
    }

    constexpr Vec3 &operator-=(const Vec3 &other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    constexpr Vec3<decltype(T{} * T{})> operator*(const Vec3 &other) const
    {
        return {x * other.x, y * other.y, z * other.z};
    }

    template <typename V>
    constexpr Vec3<decltype(T{} * V{})> operator*(const V &f) const
    {
        return {x * f, y * f, z * f};
    }

    template <typename V>
    constexpr Vec3 &operator*=(const V &f)
    {
        *this = *this * f;
        return *this;
    }
    template <typename V>
    constexpr Vec3<decltype(T{} / V{})> operator/(const V &f) const
    {
        return {x / f, y / f, z / f};
    }

    template <typename V>
    constexpr Vec3 &operator/=(const V &f)
    {
        *this = *this / f;
        return *this;
    }

    constexpr T Length2() const
    {
        return x * x + y * y + z * z;
    }

    // Only implemented for T=double
    double Length() const;
    Vec3 Normalized() const;
    double Normalize(); // returns the previous length, which is often useful

    constexpr T &operator[](std::size_t i)
    {
        return *((&x) + i);
    }

    constexpr const T &operator[](std::size_t i) const
    {
        return *((&x) + i);
    }

    constexpr void SetZero()
    {
        x = 0;
        y = 0;
        z = 0;
    }
};

template <typename T, typename V>
constexpr Vec3<T> operator*(const V &f, const Vec3<T> &vec)
{
    return Vec3<T>(f * vec.x, f * vec.y, f * vec.z);
}

template <>
inline double Vec3<double>::Length() const
{
    return std::sqrt(x * x + y * y + z * z);
}

template <>
inline Vec3<double> Vec3<double>::Normalized() const
{
    return *this / Length();
}

template <>
inline double Vec3<double>::Normalize()
{
    double length = Length();
    *this /= length;
    return length;
}

using Vec3f = Vec3<double>;

template <typename T>
class Vec4
{
  public:
    T x{};
    T y{};
    T z{};
    T w{};

    constexpr Vec4() = default;
    constexpr Vec4(const T &x_, const T &y_, const T &z_, const T &w_)
        : x(x_), y(y_), z(z_), w(w_) {}

    template <typename T2>
    constexpr Vec4<T2> Cast() const
    {
        return Vec4<T2>(static_cast<T2>(x), static_cast<T2>(y), static_cast<T2>(z),
                        static_cast<T2>(w));
    }

    static constexpr Vec4 AssignToAll(const T &f)
    {
        return Vec4(f, f, f, f);
    }

    constexpr Vec4<decltype(T{} + T{})> operator+(const Vec4 &other) const
    {
        return {x + other.x, y + other.y, z + other.z, w + other.w};
    }

    constexpr Vec4 &operator+=(const Vec4 &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this;
    }

    constexpr Vec4<decltype(T{} - T{})> operator-(const Vec4 &other) const
    {
        return {x - other.x, y - other.y, z - other.z, w - other.w};
    }

    constexpr Vec4 &operator-=(const Vec4 &other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
        return *this;
    }

    constexpr Vec4<decltype(T{} * T{})> operator*(const Vec4 &other) const
    {
        return {x * other.x, y * other.y, z * other.z, w * other.w};
    }

    template <typename V>
    constexpr Vec4<decltype(T{} * V{})> operator*(const V &f) const
    {
        return {x * f, y * f, z * f, w * f};
    }

    template <typename V>
    constexpr Vec4 &operator*=(const V &f)
    {
        *this = *this * f;
        return *this;
    }

    template <typename V>
    constexpr Vec4<decltype(T{} / V{})> operator/(const V &f) const
    {
        return {x / f, y / f, z / f, w / f};
    }

    template <typename V>
    constexpr Vec4 &operator/=(const V &f)
    {
        *this = *this / f;
        return *this;
    }

    constexpr T Length2() const
    {
        return x * x + y * y + z * z + w * w;
    }

    constexpr T &operator[](std::size_t i)
    {
        return *((&x) + i);
    }

    constexpr const T &operator[](std::size_t i) const
    {
        return *((&x) + i);
    }

    constexpr void SetZero()
    {
        x = 0;
        y = 0;
        z = 0;
        w = 0;
    }
};

// Utility vector factories
template <typename T>
constexpr Vec2<T> MakeVec(const T &x, const T &y)
{
    return Vec2<T>{x, y};
}

template <typename T>
constexpr Vec3<T> MakeVec(const T &x, const T &y, const T &z)
{
    return Vec3<T>{x, y, z};
}

template <typename T>
constexpr Vec4<T> MakeVec(const T &x, const T &y, const Vec2<T> &zw)
{
    return MakeVec(x, y, zw[0], zw[1]);
}

template <typename T>
constexpr Vec3<T> MakeVec(const Vec2<T> &xy, const T &z)
{
    return MakeVec(xy[0], xy[1], z);
}

template <typename T>
constexpr Vec3<T> MakeVec(const T &x, const Vec2<T> &yz)
{
    return MakeVec(x, yz[0], yz[1]);
}

template <typename T>
constexpr Vec4<T> MakeVec(const T &x, const T &y, const T &z, const T &w)
{
    return Vec4<T>{x, y, z, w};
}

template <typename T>
constexpr Vec4<T> MakeVec(const Vec2<T> &xy, const T &z, const T &w)
{
    return MakeVec(xy[0], xy[1], z, w);
}

template <typename T>
constexpr Vec4<T> MakeVec(const T &x, const Vec2<T> &yz, const T &w)
{
    return MakeVec(x, yz[0], yz[1], w);
}

// NOTE: This has priority over "Vec2<Vec2<T>> MakeVec(const Vec2<T>& x, const Vec2<T>& y)".
//       Even if someone wanted to use an odd object like Vec2<Vec2<T>>, the compiler would error
//       out soon enough due to misuse of the returned structure.
template <typename T>
constexpr Vec4<T> MakeVec(const Vec2<T> &xy, const Vec2<T> &zw)
{
    return MakeVec(xy[0], xy[1], zw[0], zw[1]);
}

template <typename T>
constexpr Vec4<T> MakeVec(const Vec3<T> &xyz, const T &w)
{
    return MakeVec(xyz[0], xyz[1], xyz[2], w);
}

template <typename T>
constexpr Vec4<T> MakeVec(const T &x, const Vec3<T> &yzw)
{
    return MakeVec(x, yzw[0], yzw[1], yzw[2]);
}

} // namespace Math