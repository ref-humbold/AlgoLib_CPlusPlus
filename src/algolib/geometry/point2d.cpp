/*!
 * \file point2d.hpp
 * \brief Structure of point on a plane
 */
#include "algolib/geometry/point2d.hpp"

namespace alge = algolib::geometry;

alge::point2d alge::p2d(double x, double y)
{
    return alge::point2d(x, y);
}

bool alge::operator==(const alge::point2d & p1, const alge::point2d & p2)
{
    return p1.xCoord == p2.xCoord && p1.yCoord == p2.yCoord;
}

bool alge::operator!=(const alge::point2d & p1, const alge::point2d & p2)
{
    return !(p1 == p2);
}

bool alge::operator<(const alge::point2d & p1, const alge::point2d & p2)
{
    return p1.xCoord != p2.xCoord ? p1.xCoord < p2.xCoord : p1.yCoord < p2.yCoord;
}

bool alge::operator<=(const alge::point2d & p1, const alge::point2d & p2)
{
    return p1 == p2 || p1 < p2;
}

bool alge::operator>(const alge::point2d & p1, const alge::point2d & p2)
{
    return p1.xCoord != p2.xCoord ? p1.xCoord > p2.xCoord : p1.yCoord > p2.yCoord;
}

bool alge::operator>=(const alge::point2d & p1, const alge::point2d & p2)
{
    return p1 == p2 || p1 > p2;
}

std::ostream & alge::operator<<(std::ostream & os, const alge::point2d & p)
{
    os << "(" << p.xCoord << ", " << p.yCoord << ")";

    return os;
}
