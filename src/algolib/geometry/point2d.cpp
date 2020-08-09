/*!
 * \file point2d.hpp
 * \brief Structure of point on a plane
 */
#include "algolib/geometry/point2d.hpp"

namespace alge = algolib::geometry;

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

alge::point2d alge::translate(const alge::point2d & p, const alge::vector2d & v)
{
    return point2d(p.x() + v.x(), p.y() + v.y());
}
