// Points on a plane.
#include "algolib/geometry/point2d.hpp"

namespace alge = algolib::geometry;

alge::point2d alge::p2d(double x, double y)
{
    return alge::point2d(x, y);
}

bool alge::operator==(const alge::point2d & p1, const alge::point2d & p2)
{
    return p1.x == p2.x && p1.y == p2.y;
}

bool alge::operator!=(const alge::point2d & p1, const alge::point2d & p2)
{
    return !(p1 == p2);
}

bool alge::operator<(const alge::point2d & p1, const alge::point2d & p2)
{
    return p1.x != p2.x ? p1.x < p2.x : p1.y < p2.y;
}

bool alge::operator<=(const alge::point2d & p1, const alge::point2d & p2)
{
    return p1 == p2 || p1 < p2;
}

bool alge::operator>(const alge::point2d & p1, const alge::point2d & p2)
{
    return p1.x != p2.x ? p1.x > p2.x : p1.y > p2.y;
}

bool alge::operator>=(const alge::point2d & p1, const alge::point2d & p2)
{
    return p1 == p2 || p1 > p2;
}

std::ostream & alge::operator<<(std::ostream & os, const alge::point2d & p)
{
    os << "(" << p.x << ", " << p.y << ")";

    return os;
}
