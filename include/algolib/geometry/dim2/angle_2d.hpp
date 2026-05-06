/*!
 * \file angle_2d.hpp
 * \brief Structure of angle in 2D.
 */
#ifndef ANGLE_2D_HPP_
#define ANGLE_2D_HPP_

#include <iostream>
#include <numbers>
#include "algolib/geometry/geometry_comparator.hpp"

namespace algolib::geometry::dim2
{
    enum angle_unit
    {
        DEGREES,
        RADIANS
    };

    class angle_2d
    {
    public:
        angle_2d(double angle, angle_unit unit);
        ~angle_2d() = default;
        angle_2d(const angle_2d &) = default;
        angle_2d(angle_2d &&) = default;
        angle_2d & operator=(const angle_2d &) = default;
        angle_2d & operator=(angle_2d &&) = default;

        double degrees() const
        {
            return this->degrees_;
        }

        double radians() const
        {
            return this->degrees_ * full_angle_rad / full_angle_deg;
        }

        friend bool operator==(const angle_2d & a1, const angle_2d & a2);
        friend bool operator!=(const angle_2d & a1, const angle_2d & a2);
        friend bool operator<(const angle_2d & a1, const angle_2d & a2);
        friend bool operator<=(const angle_2d & a1, const angle_2d & a2);
        friend bool operator>(const angle_2d & a1, const angle_2d & a2);
        friend bool operator>=(const angle_2d & a1, const angle_2d & a2);
        friend std::ostream & operator<<(std::ostream & os, const angle_2d & a);

        friend struct std::hash<angle_2d>;

    private:
        static double normalize(double degrees);
        static constexpr double full_angle_deg = 360.0;
        static constexpr double full_angle_rad = 2 * std::numbers::pi;
        static const geometry_comparator comparator;
        double degrees_;
    };

    bool operator==(const angle_2d & a1, const angle_2d & a2);
    bool operator!=(const angle_2d & a1, const angle_2d & a2);
    bool operator<(const angle_2d & a1, const angle_2d & a2);
    bool operator<=(const angle_2d & a1, const angle_2d & a2);
    bool operator>(const angle_2d & a1, const angle_2d & a2);
    bool operator>=(const angle_2d & a1, const angle_2d & a2);
    std::ostream & operator<<(std::ostream & os, const angle_2d & a);
}

namespace std
{
    template <>
    struct hash<algolib::geometry::dim2::angle_2d>
    {
        using argument_type = algolib::geometry::dim2::angle_2d;
        using result_type = size_t;

        result_type operator()(const argument_type & p) const noexcept
        {
            return std::hash<double>()(p.degrees_);
        }
    };
}

#endif
