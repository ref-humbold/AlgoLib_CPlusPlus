/*!
 * \file geometry.cpp
 * \brief Basic geometric operations
 */
#include "algolib/geometry/geometry.hpp"

namespace alge = algolib::geometry;

alge::point2d alge::translate(const alge::point2d & p, const alge::vector2d & v)
{
    return point2d(p.x() + v.x(), p.y() + v.y());
}

alge::point3d alge::translate(const alge::point3d & p, const alge::vector3d & v)
{
    return point3d(p.x() + v.x(), p.y() + v.y(), p.z() + v.z());
}
