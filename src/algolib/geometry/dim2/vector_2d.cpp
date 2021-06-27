/*!
 * \file vector_2d.cpp
 * \brief Structure of vector in 2D
 */
#include "algolib/geometry/dim2/vector_2d.hpp"

namespace algep = algolib::geometry::plane;

double algep::vector_2d::area(const algep::vector_2d & v1, const algep::vector_2d & v2)
{
    return v1.x() * v2.y() - v1.y() * v2.x();
}

algep::vector_2d & algep::vector_2d::operator+=(const algep::vector_2d & v)
{
    x_ += v.x();
    y_ += v.y();
    return *this;
}

algep::vector_2d & algep::vector_2d::operator-=(const algep::vector_2d & v)
{
    x_ -= v.x();
    y_ -= v.y();
    return *this;
}

algep::vector_2d & algep::vector_2d::operator*=(double c)
{
    x_ *= c;
    y_ *= c;
    return *this;
}

algep::vector_2d & algep::vector_2d::operator/=(double c)
{
    if(c == 0)
        throw std::domain_error("Division by zero");

    x_ /= c;
    y_ /= c;
    return *this;
}

bool algep::operator==(const algep::vector_2d & v1, const algep::vector_2d & v2)
{
    return algep::vector_2d::equal(v1.x_, v2.x_) && algep::vector_2d::equal(v1.y_, v2.y_);
}

bool algep::operator!=(const algep::vector_2d & v1, const algep::vector_2d & v2)
{
    return !(v1 == v2);
}

algep::vector_2d algep::operator+(algep::vector_2d v1, const algep::vector_2d & v2)
{
    v1 += v2;
    return v1;
}

algep::vector_2d algep::operator-(algep::vector_2d v1, const algep::vector_2d & v2)
{
    v1 -= v2;
    return v1;
}

algep::vector_2d algep::operator*(algep::vector_2d v, double c)
{
    v *= c;
    return v;
}

algep::vector_2d algep::operator*(double c, algep::vector_2d v)
{
    v *= c;
    return v;
}

algep::vector_2d algep::operator/(algep::vector_2d v, double c)
{
    v /= c;
    return v;
}

std::ostream & algep::operator<<(std::ostream & os, const algep::vector_2d & v)
{
    os << "[" << v.x_ << ", " << v.y_ << "]";
    return os;
}

double algep::dot(const algep::vector_2d & v1, const algep::vector_2d & v2)
{
    return v1.x_ * v2.x_ + v1.y_ * v2.y_;
}
