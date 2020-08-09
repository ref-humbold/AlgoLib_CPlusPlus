/*!
 * \file vector2d.hpp
 * \brief Structure of vector on a plane
 */
#include "algolib/geometry/vector2d.hpp"

namespace alge = algolib::geometry;

bool alge::operator==(const alge::vector2d & v1, const alge::vector2d & v2)
{
    return v1.x_ == v2.x_ && v1.y_ == v2.y_;
}

bool alge::operator!=(const alge::vector2d & v1, const alge::vector2d & v2)
{
    return !(v1 == v2);
}

alge::vector2d alge::operator+(alge::vector2d v1, const alge::vector2d & v2)
{
    v1.x_ += v2.x_;
    v1.y_ += v2.y_;
    return v1;
}

alge::vector2d alge::operator-(alge::vector2d v1, const alge::vector2d & v2)
{
    v1.x_ -= v2.x_;
    v1.y_ -= v2.y_;
    return v1;
}

double alge::operator*(const alge::vector2d & v1, const alge::vector2d & v2)
{
    return v1.x_ * v2.x_ + v1.y_ * v2.y_;
}

alge::vector2d alge::operator*(alge::vector2d v, double c)
{
    v.x_ *= c;
    v.y_ *= c;
    return v;
}

alge::vector2d alge::operator*(double c, alge::vector2d v)
{
    v.x_ *= c;
    v.y_ *= c;
    return v;
}

alge::vector2d alge::operator/(alge::vector2d v, double c)
{
    v.x_ /= c;
    v.y_ /= c;
    return v;
}

alge::vector2d alge::operator/(double c, alge::vector2d v)
{
    v.x_ /= c;
    v.y_ /= c;
    return v;
}

std::ostream & alge::operator<<(std::ostream & os, const alge::vector2d & v)
{
    os << "[" << v.x_ << ", " << v.y_ << "]";
    return os;
}

double alge::area(const alge::vector2d & v1, const alge::vector2d & v2)
{
    return v1.x() * v2.y() - v1.y() * v2.x();
}
