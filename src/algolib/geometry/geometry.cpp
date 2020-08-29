/*!
 * \file geometry.cpp
 * \brief Basic geometric operations
 */
#include "algolib/geometry/geometry.hpp"
#include <cmath>

namespace alge = algolib::geometry;

alge::vector2d alge::make_vector(const alge::point2d & begin, const point2d & end)
{
    return vector2d(end.x() - begin.x(), end.y() - begin.y());
}

alge::vector3d alge::make_vector(const alge::point3d & begin, const point3d & end)
{
    return vector3d(end.x() - begin.x(), end.y() - begin.y(), end.z() - begin.z());
}

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
