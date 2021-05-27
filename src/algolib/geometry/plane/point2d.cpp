/*!
 * \file point2d.cpp
 * \brief Structure of point in 2 dimensions
 */
#include "algolib/geometry/plane/point2d.hpp"

namespace algep = algolib::geometry::plane;

bool algep::operator==(const algep::point2d & p1, const algep::point2d & p2)
{
    return p1.x_ == p2.x_ && p1.y_ == p2.y_;
}

bool algep::operator!=(const algep::point2d & p1, const algep::point2d & p2)
{
    return !(p1 == p2);
}

std::ostream & algep::operator<<(std::ostream & os, const algep::point2d & p)
{
    os << "(" << p.x_ << ", " << p.y_ << ")";
    return os;
}
