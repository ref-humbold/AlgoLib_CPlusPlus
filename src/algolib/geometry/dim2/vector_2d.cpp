/*!
 * \file vector_2d.cpp
 * \brief Structure of vector in 2D.
 */
#include "algolib/geometry/dim2/vector_2d.hpp"

namespace alge2 = algolib::geometry::dim2;

double alge2::vector_2d::dot(const alge2::vector_2d & v1, const alge2::vector_2d & v2)
{
    return v1.x_ * v2.x_ + v1.y_ * v2.y_;
}

double alge2::vector_2d::area(const alge2::vector_2d & v1, const alge2::vector_2d & v2)
{
    return v1.x() * v2.y() - v1.y() * v2.x();
}

alge2::vector_2d & alge2::vector_2d::operator+=(const alge2::vector_2d & v)
{
    x_ += v.x();
    y_ += v.y();
    return *this;
}

alge2::vector_2d & alge2::vector_2d::operator-=(const alge2::vector_2d & v)
{
    x_ -= v.x();
    y_ -= v.y();
    return *this;
}

alge2::vector_2d & alge2::vector_2d::operator*=(double c)
{
    x_ *= c;
    y_ *= c;
    return *this;
}

alge2::vector_2d & alge2::vector_2d::operator/=(double c)
{
    if(c == 0)
        throw std::domain_error("Division by zero");

    x_ /= c;
    y_ /= c;
    return *this;
}

bool alge2::operator==(const alge2::vector_2d & v1, const alge2::vector_2d & v2)
{
    return alge2::vector_2d::equal(v1.x_, v2.x_) && alge2::vector_2d::equal(v1.y_, v2.y_);
}

bool alge2::operator!=(const alge2::vector_2d & v1, const alge2::vector_2d & v2)
{
    return !(v1 == v2);
}

alge2::vector_2d alge2::operator+(alge2::vector_2d v)
{
    v.x_ = +v.x_;
    v.y_ = +v.y_;
    return v;
}

alge2::vector_2d alge2::operator-(alge2::vector_2d v)
{
    v.x_ = -v.x_;
    v.y_ = -v.y_;
    return v;
}

alge2::vector_2d alge2::operator+(alge2::vector_2d v1, const alge2::vector_2d & v2)
{
    v1 += v2;
    return v1;
}

alge2::vector_2d alge2::operator-(alge2::vector_2d v1, const alge2::vector_2d & v2)
{
    v1 -= v2;
    return v1;
}

alge2::vector_2d alge2::operator*(alge2::vector_2d v, double c)
{
    v *= c;
    return v;
}

alge2::vector_2d alge2::operator*(double c, alge2::vector_2d v)
{
    v *= c;
    return v;
}

alge2::vector_2d alge2::operator/(alge2::vector_2d v, double c)
{
    v /= c;
    return v;
}

std::ostream & alge2::operator<<(std::ostream & os, const alge2::vector_2d & v)
{
    os << "[" << v.x_ << ", " << v.y_ << "]";
    return os;
}
