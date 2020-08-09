/*!
 * \file point2d.hpp
 * \brief Structure of point on a plane
 */
#ifndef POINT2D_HPP_
#define POINT2D_HPP_

#include <cstdlib>
#include <cmath>
#include <iostream>
#include "vector2d.hpp"

namespace algolib
{
    namespace geometry
    {
        class point2d;
    }
}

namespace std
{
    template <>
    struct hash<algolib::geometry::point2d>;
}

namespace algolib
{
    namespace geometry
    {
        class point2d
        {
        public:
            point2d(double x, double y) : x_{x}, y_{y}
            {
            }

            ~point2d() = default;
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

            double angle_rad() const
            {
                return atan2(y_, x_);
            }

            double angle_deg() const
            {
                double ang = angle_rad() * 180.0 / M_PI;

                return y_ >= 0.0 ? ang : ang + 360.0;
            }

            double radius() const
            {
                return hypot(x_, y_);
            }

            vector2d radius_vector() const
            {
                return vector2d(x_, y_);
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

        point2d translate(const point2d & p, const vector2d & v);
    }
}

namespace std
{
    template <>
    struct hash<algolib::geometry::point2d>
    {
        using argument_type = algolib::geometry::point2d;
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
