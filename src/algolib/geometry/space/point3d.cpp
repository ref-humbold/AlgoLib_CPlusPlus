/*!
 * \file point.cpp
 * \brief Structure of point in 3 dimensions
 */
#include "algolib/geometry/space/point3d.hpp"

namespace alges = algolib::geometry::space;

bool alges::operator==(const alges::point3d & p1, const alges::point3d & p2)
{
    return p1.x_ == p2.x_ && p1.y_ == p2.y_ && p1.z_ == p2.z_;
}

bool alges::operator!=(const alges::point3d & p1, const alges::point3d & p2)
{
    return !(p1 == p2);
}

std::ostream & alges::operator<<(std::ostream & os, const alges::point3d & p)
{
    os << "(" << p.x_ << ", " << p.y_ << ", " << p.z_ << ")";
    return os;
}
