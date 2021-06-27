/*!
 * \file point_2d.cpp
 * \brief Structure of point in 2D
 */
#include "algolib/geometry/dim2/point_2d.hpp"

namespace algep = algolib::geometry::plane;

bool algep::operator==(const algep::point_2d & p1, const algep::point_2d & p2)
{
    return algep::point_2d::equal(p1.x_, p2.x_) && algep::point_2d::equal(p1.y_, p2.y_);
}

bool algep::operator!=(const algep::point_2d & p1, const algep::point_2d & p2)
{
    return !(p1 == p2);
}

std::ostream & algep::operator<<(std::ostream & os, const algep::point_2d & p)
{
    os << "(" << p.x_ << ", " << p.y_ << ")";
    return os;
}
