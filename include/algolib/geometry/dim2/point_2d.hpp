/*!
 * \file point_2d.hpp
 * \brief Structure of point in 2D.
 */
#ifndef POINT_2D_HPP_
#define POINT_2D_HPP_

#include <cmath>
#include <cstdlib>
#include <array>
#include <iostream>
#include <stdexcept>
#include "algolib/geometry/geometry_comparator.hpp"
#include "angle_2d.hpp"

namespace algolib::geometry::dim2
{
    class point_2d
    {
    public:
        point_2d(double x, double y) : x_{x}, y_{y}
        {
        }

        ~point_2d() = default;
        point_2d(const point_2d &) = default;
        point_2d(point_2d &&) = default;
        point_2d & operator=(const point_2d &) = default;
        point_2d & operator=(point_2d &&) = default;

        double x() const
        {
            return x_;
        }

        double y() const
        {
            return y_;
        }

        std::array<double, 2> coordinates() const
        {
            return {x_, y_};
        }

        double radius() const
        {
            return std::sqrt(x_ * x_ + y_ * y_);
        }

        angle_2d angle() const
        {
            return angle_2d(atan2(y_, x_), RADIANS);
        }

        friend bool operator==(const point_2d & p1, const point_2d & p2);
        friend bool operator!=(const point_2d & p1, const point_2d & p2);
        friend std::ostream & operator<<(std::ostream & os, const point_2d & p);

        friend struct std::hash<point_2d>;

    private:
        static const geometry_comparator comparator;
        double x_, y_;
    };

    bool operator==(const point_2d & p1, const point_2d & p2);
    bool operator!=(const point_2d & p1, const point_2d & p2);
    std::ostream & operator<<(std::ostream & os, const point_2d & p);
}

namespace std
{
    template <>
    struct hash<algolib::geometry::dim2::point_2d>
    {
        using argument_type = algolib::geometry::dim2::point_2d;
        using result_type = size_t;

        result_type operator()(const argument_type & p) const noexcept
        {
            result_type x_hash = std::hash<double>()(p.x_);
            result_type y_hash = std::hash<double>()(p.y_);

            return x_hash ^ (y_hash + 0x9e3779b9 + (x_hash << 6) + (x_hash >> 2));
        }
    };
}

#endif
