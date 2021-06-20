/*!
 * \file point2d.hpp
 * \brief Structure of point in 2 dimensions
 */
#ifndef POINT_2D_HPP_
#define POINT_2D_HPP_

#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <array>
#include <exception>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include "../geometry_object.hpp"

namespace algolib::geometry::plane
{
    class point2d : public algolib::geometry::geometry_object
    {
    public:
        point2d(double x, double y) : x_{x}, y_{y}
        {
        }

        ~point2d() override = default;
        point2d(const point2d &) = default;
        point2d(point2d &&) = default;
        point2d & operator=(const point2d &) = default;
        point2d & operator=(point2d &&) = default;

        double x() const
        {
            return x_;
        }

        double y() const
        {
            return y_;
        }

        double radius() const
        {
            return sqrt(x_ * x_ + y_ * y_);
        }

        double angle_rad() const
        {
            return atan2(y_, x_);
        }

        double angle_deg() const
        {
            double ang = angle_rad() * 180.0 / M_PI;

            return y_ >= 0.0 ? ang : ang + 360.0;
        }

        friend bool operator==(const point2d & p1, const point2d & p2);
        friend bool operator!=(const point2d & p1, const point2d & p2);
        friend std::ostream & operator<<(std::ostream & os, const point2d & p);

        friend struct std::hash<point2d>;

    private:
        double x_, y_;
    };

    bool operator==(const point2d & p1, const point2d & p2);
    bool operator!=(const point2d & p1, const point2d & p2);
    std::ostream & operator<<(std::ostream & os, const point2d & p);

#pragma endregion
}

namespace std
{
    template <>
    struct hash<algolib::geometry::plane::point2d>
    {
        using argument_type = algolib::geometry::plane::point2d;
        using result_type = size_t;

        result_type operator()(const argument_type & p)
        {
            size_t x_hash = hash<double>()(p.x_);
            size_t y_hash = hash<double>()(p.y_);

            return x_hash ^ (y_hash + 0x9e3779b9 + (x_hash << 6) + (x_hash >> 2));
        }
    };
}

#endif
