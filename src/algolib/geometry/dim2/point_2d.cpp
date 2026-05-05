/*!
 * \file point_2d.cpp
 * \brief Structure of point in 2D.
 */
#include "algolib/geometry/dim2/point_2d.hpp"
#include <format>

namespace alge2 = algolib::geometry::dim2;

bool alge2::operator==(const point_2d & p1, const point_2d & p2)
{
    return point_2d::comparator.compare(p1.x_, p2.x_) == 0
           && point_2d::comparator.compare(p1.y_, p2.y_) == 0;
}

bool alge2::operator!=(const point_2d & p1, const point_2d & p2)
{
    return !(p1 == p2);
}

std::ostream & alge2::operator<<(std::ostream & os, const point_2d & p)
{
    os << std::format("({}, {})", p.x_, p.y_);
    return os;
}
