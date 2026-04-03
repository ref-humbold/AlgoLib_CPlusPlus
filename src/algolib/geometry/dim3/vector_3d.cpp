/*!
 * \file vector_3d.cpp
 * \brief Structure of vector in 3D.
 */
#include "algolib/geometry/dim3/vector_3d.hpp"

namespace alge3 = algolib::geometry::dim3;

double alge3::vector_3d::dot(const vector_3d & v1, const vector_3d & v2)
{
    return v1.x_ * v2.x_ + v1.y_ * v2.y_ + v1.z_ * v2.z_;
}

alge3::vector_3d alge3::vector_3d::cross(const vector_3d & v1, const vector_3d & v2)
{
    return vector_3d(v1.y_ * v2.z_ - v1.z_ * v2.y_, v1.z_ * v2.x_ - v1.x_ * v2.z_,
            v1.x_ * v2.y_ - v1.y_ * v2.x_);
}

double alge3::vector_3d::area(const vector_3d & v1, const vector_3d & v2)
{
    return cross(v1, v2).length();
}

double alge3::vector_3d::volume(
        const vector_3d & v1, const vector_3d & v2, const vector_3d & v3)
{
    return dot(v1, cross(v2, v3));
}

alge3::vector_3d & alge3::vector_3d::operator+=(const vector_3d & v)
{
    x_ += v.x_;
    y_ += v.y_;
    z_ += v.z_;
    return *this;
}

alge3::vector_3d & alge3::vector_3d::operator-=(const vector_3d & v)
{
    x_ -= v.x_;
    y_ -= v.y_;
    z_ -= v.z_;
    return *this;
}

alge3::vector_3d & alge3::vector_3d::operator*=(double c)
{
    x_ *= c;
    y_ *= c;
    z_ *= c;
    return *this;
}

alge3::vector_3d & alge3::vector_3d::operator/=(double c)
{
    if(c == 0)
        throw std::domain_error("Division by zero");

    x_ /= c;
    y_ /= c;
    z_ /= c;
    return *this;
}

bool alge3::operator==(const vector_3d & v1, const vector_3d & v2)
{
    return vector_3d::equal(v1.x_, v2.x_) && vector_3d::equal(v1.y_, v2.y_)
           && vector_3d::equal(v1.z_, v2.z_);
}

bool alge3::operator!=(const vector_3d & v1, const vector_3d & v2)
{
    return !(v1 == v2);
}

alge3::vector_3d alge3::operator+(vector_3d v)
{
    v.x_ = +v.x_;
    v.y_ = +v.y_;
    v.z_ = +v.z_;
    return v;
}

alge3::vector_3d alge3::operator-(vector_3d v)
{
    v.x_ = -v.x_;
    v.y_ = -v.y_;
    v.z_ = -v.z_;
    return v;
}

alge3::vector_3d alge3::operator+(vector_3d v1, const vector_3d & v2)
{
    v1 += v2;
    return v1;
}

alge3::vector_3d alge3::operator-(vector_3d v1, const vector_3d & v2)
{
    v1 -= v2;
    return v1;
}

alge3::vector_3d alge3::operator*(vector_3d v, double c)
{
    v *= c;
    return v;
}

alge3::vector_3d alge3::operator*(double c, vector_3d v)
{
    v *= c;
    return v;
}

alge3::vector_3d alge3::operator/(vector_3d v, double c)
{
    v /= c;
    return v;
}

std::ostream & alge3::operator<<(std::ostream & os, const vector_3d & v)
{
    os << "[" << v.x_ << ", " << v.y_ << ", " << v.z_ << "]";
    return os;
}
