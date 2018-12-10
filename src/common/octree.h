#pragma once

#include <vector>
#include <memory>
#include <iostream>

#include "vector_math.h"

template <typename T, typename V = double>
class Octree
{
  public:
    Octree(const Math::Vec3<V> &coord, const V &depth, int degree = 4) : boundary({coord, depth}),
                                                                         capacity(degree),
                                                                         divided(false){};

  public:
    bool insert(const T &elem)
    {
        if (!boundary.contains(elem.coord))
            return false;

        if (lstObjects.size() <= capacity)
        {
            lstObjects.push_back(elem);
            return true;
        }

        if (!divided)
            subdivide();

        for (int i = 0; i < 8; ++i)
        {
            if (children[i].insert(elem))
            {
                return true;
            }
        }

        return false;
    }

    void getNeighbors(const Math::Vec3<V> &coord, const V &depth, std::vector<T> &found) const
    {
        const Cube range{coord, depth};

        // Automatically abort if the range does not intersect this cube subdivision
        if (!boundary.intersects(range))
            return;

        // Check objects at this cube subdivision level
        for (const auto &elem : lstObjects)
        {
            if (range.contains(elem.coord))
            {
                found.push_back(elem);
            }
        }

        // Terminate here, if there are no children
        if (divided)
        {
            // Otherwise, add the points from the children
            for (int i = 0; i < 8; ++i)
            {
                children[i].getNeighbors(coord, depth, found);
            }
        }
    }

  private:
    void subdivide()
    {
        auto newOrigin = boundary.coord;
        const auto new_depth = boundary.depth * .5;

        for (int i = 0; i < 8; ++i)
        {
            newOrigin.x = new_depth * (i & 4 ? .5 : -.5);
            newOrigin.y = new_depth * (i & 2 ? .5 : -.5);
            newOrigin.z = new_depth * (i & 1 ? .5 : -.5);
            children.push_back(Octree<T>(newOrigin, new_depth));
        }

        divided = 1;
    }

  private:
    struct Cube
    {
        Math::Vec3<V> coord{};
        V depth{};

        constexpr bool contains(const Math::Vec3<V> &p_coord) const
        {
            const Math::Vec3<V> depth_v{depth, depth, depth};
            return (p_coord >= coord - depth_v) && (p_coord <= coord + depth_v);
        }

        constexpr bool intersects(const Cube &other) const
        {
            const Math::Vec3<V> other_depth_vec{depth, depth, depth};
            const Math::Vec3<V> depth_vec{other.depth, other.depth, other.depth};
            return !(other.coord - other_depth_vec >= coord + depth_vec ||
                     other.coord + other_depth_vec <= coord - depth_vec);
        }
    };

  private:
    Cube boundary{};

    unsigned int capacity; // Capacity of each cube

    std::vector<T> lstObjects{};

    std::vector<Octree<T>> children{};

    bool divided;
};
