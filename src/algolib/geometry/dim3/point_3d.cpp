/*!
 * \file point_3d.cpp
 * \brief Structure of point in 3D.
 */
#include "algolib/geometry/dim3/point_3d.hpp"
#include <format>

namespace alge3 = algolib::geometry::dim3;

const alge3::point_3d alge3::point_3d::zero = point_3d(0.0, 0.0, 0.0);

bool alge3::operator==(const point_3d & p1, const point_3d & p2)
{
    return point_3d::comparator.compare(p1.x_, p2.x_) == 0
            && point_3d::comparator.compare(p1.y_, p2.y_) == 0
            && point_3d::comparator.compare(p1.z_, p2.z_) == 0;
}

std::ostream & alge3::operator<<(std::ostream & os, const point_3d & p)
{
    os << std::format("({}, {}, {})", p.x_, p.y_, p.z_);
    return os;
}
