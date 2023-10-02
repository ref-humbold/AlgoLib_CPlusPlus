/*!
 * \file point.cpp
 * \brief Structure of point in 3D.
 */
#include "algolib/geometry/dim3/point_3d.hpp"

namespace alge3 = algolib::geometry::dim3;

bool alge3::operator==(const alge3::point_3d & p1, const alge3::point_3d & p2)
{
    return alge3::point_3d::equal(p1.x_, p2.x_) && alge3::point_3d::equal(p1.y_, p2.y_)
           && alge3::point_3d::equal(p1.z_, p2.z_);
}

bool alge3::operator!=(const alge3::point_3d & p1, const alge3::point_3d & p2)
{
    return !(p1 == p2);
}

std::ostream & alge3::operator<<(std::ostream & os, const alge3::point_3d & p)
{
    os << "(" << p.x_ << ", " << p.y_ << ", " << p.z_ << ")";
    return os;
}
