/*!
 * \file point_2d.cpp
 * \brief Structure of point in 2D
 */
#include "algolib/geometry/dim2/point_2d.hpp"

namespace alge2 = algolib::geometry::dim2;

bool alge2::operator==(const alge2::point_2d & p1, const alge2::point_2d & p2)
{
    return alge2::point_2d::equal(p1.x_, p2.x_) && alge2::point_2d::equal(p1.y_, p2.y_);
}

bool alge2::operator!=(const alge2::point_2d & p1, const alge2::point_2d & p2)
{
    return !(p1 == p2);
}

std::ostream & alge2::operator<<(std::ostream & os, const alge2::point_2d & p)
{
    os << "(" << p.x_ << ", " << p.y_ << ")";
    return os;
}
