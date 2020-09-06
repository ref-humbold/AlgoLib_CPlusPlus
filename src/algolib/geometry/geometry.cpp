/*!
 * \file geometry.cpp
 * \brief Basic geometric operations
 */
#include "algolib/geometry/geometry.hpp"

namespace alge = algolib::geometry;

double alge::distance(const alge::point2d & p1, const alge::point2d & p2)
{
    return sqrt((p2.x() - p1.x()) * (p2.x() - p1.x()) + (p2.y() - p1.y()) * (p2.y() - p1.y()));
}

double alge::distance(const alge::point3d & p1, const alge::point3d & p2)
{
    return sqrt((p2.x() - p1.x()) * (p2.x() - p1.x()) + (p2.y() - p1.y()) * (p2.y() - p1.y())
                + (p2.z() - p1.z()) * (p2.z() - p1.z()));
}

alge::point2d alge::translate(const alge::point2d & p, const alge::vector2d & v)
{
    return point2d(p.x() + v.x(), p.y() + v.y());
}

alge::point3d alge::translate(const alge::point3d & p, const alge::vector3d & v)
{
    return point3d(p.x() + v.x(), p.y() + v.y(), p.z() + v.z());
}
