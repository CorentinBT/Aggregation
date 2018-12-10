#include <random>

#include "math_utils.h"

#define M_PI 3.14159265358979323846

namespace Math
{

static std::random_device rd;
static std::default_random_engine generator(rd());
static std::normal_distribution<double> normal_dist(0, 1);

template <>
Vec3<double> rand_point_sphere(const Vec3<double> &from, const double &rad)
{
    const Vec3<double> x{normal_dist(generator), normal_dist(generator), normal_dist(generator)};
    const Vec3<double> ratio{1 / x.Length(), 1 / x.Length(), 1 / x.Length()};
    const Vec3<double> radius{rad, rad, rad};

    return from + x * ratio * radius;
}

template <>
Vec3<double> rand_point_sphere_angle(const Vec3<double> &from, const double &rad, double alpha, double beta)
{
    std::normal_distribution<double> normal_dist_alpha(0, alpha);
    std::normal_distribution<double> normal_dist_beta(-90.0, beta);

    const auto rand_alpha = normal_dist_alpha(generator) * M_PI / 180.0;
    const auto rand_beta = normal_dist_beta(generator) * M_PI / 180.0;

    const auto x = rad * std::cos(rand_alpha) * std::cos(rand_beta);
    const auto y = rad * std::sin(rand_alpha) * std::cos(rand_beta);
    const auto z = rad * std::sin(rand_beta);

    return from + Vec3<double>{x, y, z};
}

} // namespace Math