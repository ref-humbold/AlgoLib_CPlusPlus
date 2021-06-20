/*!
 * \file vector2d.cpp
 * \brief Structure of vector in 2 dimensions
 */
#include "algolib/geometry/plane/vector2d.hpp"

namespace algep = algolib::geometry::plane;

double algep::vector2d::area(const algep::vector2d & v1, const algep::vector2d & v2)
{
    return v1.x() * v2.y() - v1.y() * v2.x();
}

algep::vector2d & algep::vector2d::operator+=(const algep::vector2d & v)
{
    x_ += v.x();
    y_ += v.y();
    return *this;
}

algep::vector2d & algep::vector2d::operator-=(const algep::vector2d & v)
{
    x_ -= v.x();
    y_ -= v.y();
    return *this;
}

algep::vector2d & algep::vector2d::operator*=(double c)
{
    x_ *= c;
    y_ *= c;
    return *this;
}

algep::vector2d & algep::vector2d::operator/=(double c)
{
    if(c == 0)
        throw std::domain_error("Division by zero");

    x_ /= c;
    y_ /= c;
    return *this;
}

bool algep::operator==(const algep::vector2d & v1, const algep::vector2d & v2)
{
    return algep::vector2d::equal(v1.x_, v2.x_) && algep::vector2d::equal(v1.y_, v2.y_);
}

bool algep::operator!=(const algep::vector2d & v1, const algep::vector2d & v2)
{
    return !(v1 == v2);
}

algep::vector2d algep::operator+(algep::vector2d v1, const algep::vector2d & v2)
{
    v1 += v2;
    return v1;
}

algep::vector2d algep::operator-(algep::vector2d v1, const algep::vector2d & v2)
{
    v1 -= v2;
    return v1;
}

algep::vector2d algep::operator*(algep::vector2d v, double c)
{
    v *= c;
    return v;
}

algep::vector2d algep::operator*(double c, algep::vector2d v)
{
    v *= c;
    return v;
}

algep::vector2d algep::operator/(algep::vector2d v, double c)
{
    v /= c;
    return v;
}

std::ostream & algep::operator<<(std::ostream & os, const algep::vector2d & v)
{
    os << "[" << v.x_ << ", " << v.y_ << "]";
    return os;
}

double algep::dot(const algep::vector2d & v1, const algep::vector2d & v2)
{
    return v1.x_ * v2.x_ + v1.y_ * v2.y_;
}
