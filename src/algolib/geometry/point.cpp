/*!
 * \file point.cpp
 * \brief Structure of point on a plane or in a space
 */
#include "algolib/geometry/point.hpp"

namespace alge = algolib::geometry;

#pragma region point2d

bool alge::operator==(const alge::point2d & p1, const alge::point2d & p2)
{
    return p1.x_ == p2.x_ && p1.y_ == p2.y_;
}

bool alge::operator!=(const alge::point2d & p1, const alge::point2d & p2)
{
    return !(p1 == p2);
}

std::ostream & alge::operator<<(std::ostream & os, const alge::point2d & p)
{
    os << "(" << p.x_ << ", " << p.y_ << ")";
    return os;
}

#pragma endregion
#pragma region point3d

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

#pragma endregion
