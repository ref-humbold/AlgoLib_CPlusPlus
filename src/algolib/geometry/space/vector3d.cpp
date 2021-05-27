/*!
 * \file vector3d.cpp
 * \brief Structure of vector in 3 dimensions
 */
#include "algolib/geometry/space/vector3d.hpp"

namespace alges = algolib::geometry::space;

double alges::vector3d::area(const alges::vector3d & v1, const alges::vector3d & v2)
{
    return cross(v1, v2).length();
}

double alges::vector3d::volume(const alges::vector3d & v1, const alges::vector3d & v2,
                               const alges::vector3d & v3)
{
    return dot(v1, cross(v2, v3));
}

alges::vector3d & alges::vector3d::operator+=(const alges::vector3d & v)
{
    x_ += v.x();
    y_ += v.y();
    return *this;
}

alges::vector3d & alges::vector3d::operator-=(const alges::vector3d & v)
{
    x_ -= v.x();
    y_ -= v.y();
    return *this;
}

alges::vector3d & alges::vector3d::operator*=(double c)
{
    x_ *= c;
    y_ *= c;
    return *this;
}

alges::vector3d & alges::vector3d::operator/=(double c)
{
    if(c == 0)
        throw std::domain_error("Division by zero");

    x_ /= c;
    y_ /= c;
    return *this;
}

bool alges::operator==(const alges::vector3d & v1, const alges::vector3d & v2)
{
    return v1.x_ == v2.x_ && v1.y_ == v2.y_ && v1.z_ == v2.z_;
}

bool alges::operator!=(const alges::vector3d & v1, const alges::vector3d & v2)
{
    return !(v1 == v2);
}

alges::vector3d alges::operator+(alges::vector3d v1, const alges::vector3d & v2)
{
    v1 += v2;
    return v1;
}

alges::vector3d alges::operator-(alges::vector3d v1, const alges::vector3d & v2)
{
    v1 -= v2;
    return v1;
}

alges::vector3d alges::operator*(alges::vector3d v, double c)
{
    v *= c;
    return v;
}

alges::vector3d alges::operator*(double c, alges::vector3d v)
{
    v *= c;
    return v;
}

alges::vector3d alges::operator/(alges::vector3d v, double c)
{
    v /= c;
    return v;
}

std::ostream & alges::operator<<(std::ostream & os, const alges::vector3d & v)
{
    os << "[" << v.x_ << ", " << v.y_ << ", " << v.z_ << "]";
    return os;
}

double alges::dot(const alges::vector3d & v1, const alges::vector3d & v2)
{
    return v1.x_ * v2.x_ + v1.y_ * v2.y_ + v1.z_ * v2.z_;
}

alges::vector3d alges::cross(const alges::vector3d & v1, const alges::vector3d & v2)
{
    return vector3d(v1.y_ * v2.z_ - v1.z_ * v2.y_, v1.z_ * v2.x_ - v1.x_ * v2.z_,
                    v1.x_ * v2.y_ - v1.y_ * v2.x_);
}
