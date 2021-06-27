/*!
 * \file point.cpp
 * \brief Structure of point in 3D
 */
#include "algolib/geometry/dim3/point_3d.hpp"

namespace alges = algolib::geometry::space;

bool alges::operator==(const alges::point_3d & p1, const alges::point_3d & p2)
{
    return alges::point_3d::equal(p1.x_, p2.x_) && alges::point_3d::equal(p1.y_, p2.y_)
           && alges::point_3d::equal(p1.z_, p2.z_);
}

bool alges::operator!=(const alges::point_3d & p1, const alges::point_3d & p2)
{
    return !(p1 == p2);
}

std::ostream & alges::operator<<(std::ostream & os, const alges::point_3d & p)
{
    os << "(" << p.x_ << ", " << p.y_ << ", " << p.z_ << ")";
    return os;
}
