#pragma once

#include <vector>

#include "common/octree.h"
#include "common/vector_math.h"

#include "sphere.h"

namespace Agg
{

template <typename T>
struct Aggregate
{
    T root;
    std::vector<T> objects{};
    Octree<T> octree;

    Aggregate() : root({{0, 0, 0}, 5}), octree(root.coord, 500.0){};
    Aggregate(const T &core, const double depth) : root(core), octree(root.coord, depth){};
};

} // namespace Agg