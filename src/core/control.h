#pragma once

#include <optional>
#include <functional>

#include "aggregate.h"
#include "sphere.h"

#include "common/vector_math.h"

namespace Agg
{
template <typename T>
struct Aggregate;
}

namespace Agg::Control
{

using Vec3d = Math::Vec3<double>;
using Sphere = Agg::Object::Sphere<double>;
using OptionalVec = std::optional<Vec3d>;

class Controller
{

public:
  Controller(Sphere core, const double depth, double precision = 0.01);
  ~Controller() = default;

  Sphere spawn(const Vec3d &coord, double sphere_rad, double expl_rad);

  void putSphere(const Sphere &sphere);

  inline Agg::Aggregate<Agg::Object::Sphere<double>> getAggregate() const
  {
    return agg;
  }

  inline double getPrecision() const
  {
    return dt;
  }

  // private:
  Vec3d movToCenter(Sphere &obj);

  OptionalVec collision(const Sphere &obj) const;

  Sphere localMin(const Sphere &sphere, Vec3d from, double explRad) const;

  Agg::Aggregate<Agg::Object::Sphere<double>> agg{};
  double dt{};
};

} // namespace Agg::Control