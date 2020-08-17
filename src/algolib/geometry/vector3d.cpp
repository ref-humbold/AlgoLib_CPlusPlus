/*!
 * \file vector3d.cpp
 * \brief Structure of vector in a space
 */
#include "algolib/geometry/vector3d.hpp"

namespace alge = algolib::geometry;

double alge::vector3d::area(const alge::vector3d & v1, const alge::vector3d & v2)
{
    return (v1 ^ v2).length();
}

double alge::vector3d::volume(const alge::vector3d & v1, const alge::vector3d & v2,
                              const alge::vector3d & v3)
{
    return v1 * (v2 ^ v3);
}

bool alge::operator==(const alge::vector3d & v1, const alge::vector3d & v2)
{
    return v1.x_ == v2.x_ && v1.y_ == v2.y_ && v1.z_ == v2.z_;
}

bool alge::operator!=(const alge::vector3d & v1, const alge::vector3d & v2)
{
    return !(v1 == v2);
}

alge::vector3d alge::operator+(alge::vector3d v1, const alge::vector3d & v2)
{
    v1.x_ += v2.x_;
    v1.y_ += v2.y_;
    v1.z_ += v2.z_;
    return v1;
}

alge::vector3d alge::operator-(alge::vector3d v1, const alge::vector3d & v2)
{
    v1.x_ -= v2.x_;
    v1.y_ -= v2.y_;
    v1.z_ -= v2.z_;
    return v1;
}

double alge::operator*(const alge::vector3d & v1, const alge::vector3d & v2)
{
    return v1.x_ * v2.x_ + v1.y_ * v2.y_ + v1.z_ * v2.z_;
}

alge::vector3d alge::operator*(alge::vector3d v, double c)
{
    v.x_ *= c;
    v.y_ *= c;
    v.z_ *= c;
    return v;
}

alge::vector3d alge::operator*(double c, alge::vector3d v)
{
    v.x_ *= c;
    v.y_ *= c;
    v.z_ *= c;
    return v;
}

alge::vector3d alge::operator/(alge::vector3d v, double c)
{
    v.x_ /= c;
    v.y_ /= c;
    v.z_ /= c;
    return v;
}

alge::vector3d alge::operator^(const alge::vector3d & v1, const alge::vector3d & v2)
{
    return vector3d(v1.y_ * v2.z_ - v1.z_ * v2.y_, v1.z_ * v2.x_ - v1.x_ * v2.z_,
                    v1.x_ * v2.y_ - v1.y_ * v2.x_);
}

std::ostream & alge::operator<<(std::ostream & os, const alge::vector3d & v)
{
    os << "[" << v.x_ << ", " << v.y_ << ", " << v.z_ << "]";
    return os;
}
