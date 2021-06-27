/*!
 * \file vector_3d.cpp
 * \brief Structure of vector in 3D
 */
#include "algolib/geometry/space/vector_3d.hpp"

namespace alges = algolib::geometry::space;

double alges::vector_3d::area(const alges::vector_3d & v1, const alges::vector_3d & v2)
{
    return cross(v1, v2).length();
}

double alges::vector_3d::volume(const alges::vector_3d & v1, const alges::vector_3d & v2,
                                const alges::vector_3d & v3)
{
    return dot(v1, cross(v2, v3));
}

alges::vector_3d & alges::vector_3d::operator+=(const alges::vector_3d & v)
{
    x_ += v.x();
    y_ += v.y();
    return *this;
}

alges::vector_3d & alges::vector_3d::operator-=(const alges::vector_3d & v)
{
    x_ -= v.x();
    y_ -= v.y();
    return *this;
}

alges::vector_3d & alges::vector_3d::operator*=(double c)
{
    x_ *= c;
    y_ *= c;
    return *this;
}

alges::vector_3d & alges::vector_3d::operator/=(double c)
{
    if(c == 0)
        throw std::domain_error("Division by zero");

    x_ /= c;
    y_ /= c;
    return *this;
}

bool alges::operator==(const alges::vector_3d & v1, const alges::vector_3d & v2)
{
    return alges::vector_3d::equal(v1.x_, v2.x_) && alges::vector_3d::equal(v1.y_, v2.y_)
           && alges::vector_3d::equal(v1.z_, v2.z_);
}

bool alges::operator!=(const alges::vector_3d & v1, const alges::vector_3d & v2)
{
    return !(v1 == v2);
}

alges::vector_3d alges::operator+(alges::vector_3d v1, const alges::vector_3d & v2)
{
    v1 += v2;
    return v1;
}

alges::vector_3d alges::operator-(alges::vector_3d v1, const alges::vector_3d & v2)
{
    v1 -= v2;
    return v1;
}

alges::vector_3d alges::operator*(alges::vector_3d v, double c)
{
    v *= c;
    return v;
}

alges::vector_3d alges::operator*(double c, alges::vector_3d v)
{
    v *= c;
    return v;
}

alges::vector_3d alges::operator/(alges::vector_3d v, double c)
{
    v /= c;
    return v;
}

std::ostream & alges::operator<<(std::ostream & os, const alges::vector_3d & v)
{
    os << "[" << v.x_ << ", " << v.y_ << ", " << v.z_ << "]";
    return os;
}

double alges::dot(const alges::vector_3d & v1, const alges::vector_3d & v2)
{
    return v1.x_ * v2.x_ + v1.y_ * v2.y_ + v1.z_ * v2.z_;
}

alges::vector_3d alges::cross(const alges::vector_3d & v1, const alges::vector_3d & v2)
{
    return vector_3d(v1.y_ * v2.z_ - v1.z_ * v2.y_, v1.z_ * v2.x_ - v1.x_ * v2.z_,
                     v1.x_ * v2.y_ - v1.y_ * v2.x_);
}
