/*!
 * \file point3d.cpp
 * \brief Structure of point in a space
 */
#include "algolib/geometry/point3d.hpp"

namespace alge = algolib::geometry;

bool alge::operator==(const alge::point3d & p1, const alge::point3d & p2)
{
    return p1.x_ == p2.x_ && p1.y_ == p2.y_ && p1.z_ == p2.z_;
}

bool alge::operator!=(const alge::point3d & p1, const alge::point3d & p2)
{
    return !(p1 == p2);
}

std::ostream & alge::operator<<(std::ostream & os, const alge::point3d & p)
{
    os << "(" << p.x_ << ", " << p.y_ << ", " << p.z_ << ")";
    return os;
}
