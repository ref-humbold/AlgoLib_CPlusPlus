/*!
 * \file angle_2d.cpp
 * \brief Structure of angle in 2D.
 */
#include "algolib/geometry/dim2/angle_2d.hpp"
#include <format>

namespace alge2 = algolib::geometry::dim2;

alge2::angle_2d::angle_2d(double angle, angle_unit unit)
{
    switch(unit)
    {
        case DEGREES:
            this->degrees_ = normalize(angle);
            break;
        case RADIANS:
            this->degrees_ = normalize(angle * full_angle_deg / full_angle_rad);
            break;
    }
}

bool alge2::operator==(const angle_2d & a1, const angle_2d & a2)
{
    return angle_2d::comparator.compare(a1.degrees_, a2.degrees_) == 0;
}

std::weak_ordering alge2::operator<=>(const angle_2d & a1, const angle_2d & a2)
{
    return angle_2d::comparator.compare(a1.degrees_, a2.degrees_);
}

std::ostream & alge2::operator<<(std::ostream & os, const angle_2d & a)
{
    os << std::format("Angle<{} deg>", a.degrees_);
    return os;
}

double alge2::angle_2d::normalize(double degrees)
{
    return std::fmod(std::fmod(degrees, full_angle_deg) + full_angle_deg, full_angle_deg);
}
