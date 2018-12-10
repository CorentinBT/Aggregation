#include <vector>

#include "control.h"

#include "common/math_utils.h"

namespace Agg::Control
{

Controller::Controller(Sphere core, const double depth, double precision) : agg(core, depth), dt(precision)
{
    agg.root = core;
    agg.objects.push_back(core);
    agg.octree.insert(core);
}

Sphere Controller::spawn(const Vec3d &coord, double sphere_rad, double expl_rad)
{
    Sphere sphere{coord, sphere_rad};

    const auto collisionPoint = movToCenter(sphere);

    sphere = localMin(sphere, collisionPoint, expl_rad);

    movToCenter(sphere);

    agg.octree.insert(sphere);
    agg.objects.push_back(sphere);

    return sphere;
}

OptionalVec Controller::collision(const Sphere &sphere) const
{
    std::vector<Sphere> found{};

    const auto range = (sphere.radius + agg.root.radius + 2 * dt);
    agg.octree.getNeighbors(sphere.coord, range, found);

    for (const auto &neighbor : found)
    {
        if (Agg::Object::intersects(neighbor, sphere))
        {
            return Agg::Object::intersectionPoint(neighbor, sphere);
        }
    }

    return std::nullopt;
}

Sphere Controller::localMin(const Sphere &sphere, Vec3d from, double explRad) const
{
    const auto nbLayer = 30;
    const auto pointsLayer = 50;
    const auto localRad = explRad / nbLayer;

    auto currDistMin = Agg::Object::distance(sphere, agg.root);
    auto currMin = sphere;

    for (auto i = 0; i < nbLayer; i++)
    {
        for (auto j = 0; j < pointsLayer; j++)
        {

            const Sphere potentialSphere{Math::rand_point_sphere(from, localRad), sphere.radius};
            const auto newDist = Agg::Object::distance(potentialSphere, agg.root);

            if (newDist >= currDistMin)
            {
                continue;
            }

            if (!collision(potentialSphere).has_value())
            {
                currMin = potentialSphere;
                currDistMin = newDist;
            }
        }
        from = currMin.coord;
    }

    return currMin;
}

void Controller::putSphere(const Sphere &sphere)
{
    if (collision(sphere).has_value())
    {
        agg.objects.push_back(sphere);
        agg.octree.insert(sphere);
    }
}

Vec3d Controller::movToCenter(Sphere &sphere)
{
    for (;;)
    {
        sphere.coord -= Math::sign(sphere.coord) * dt;
        const auto collided = collision(sphere);
        if (collided.has_value())
        {
            return collided.value();
        }
    }
}

} // namespace Agg::Control