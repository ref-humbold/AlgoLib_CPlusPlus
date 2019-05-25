/*!
 * \file point2d.hpp
 * \brief Points on a plane.
 */
#ifndef POINT2D_HPP_
#define POINT2D_HPP_

#include <cstdlib>
#include <cmath>
#include <iostream>

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
            point2d(double x, double y) : xCoord{x}, yCoord{y}
            {
            }

            ~point2d() = default;
            point2d(const point2d &) = default;
            point2d(point2d &&) = default;
            point2d & operator=(const point2d &) = default;
            point2d & operator=(point2d &&) = default;

            double x() const
            {
                return xCoord;
            }

            double y() const
            {
                return yCoord;
            }

            double angle() const
            {
                double ang = atan2(yCoord, xCoord) * 180.0 / M_PI;

                return yCoord >= 0.0 ? ang : ang + 360.0;
            }

            double radius() const
            {
                return xCoord * xCoord + yCoord * yCoord;
            }

            friend bool operator==(const point2d & p1, const point2d & p2);
            friend bool operator!=(const point2d & p1, const point2d & p2);
            friend bool operator<(const point2d & p1, const point2d & p2);
            friend bool operator<=(const point2d & p1, const point2d & p2);
            friend bool operator>(const point2d & p1, const point2d & p2);
            friend bool operator>=(const point2d & p1, const point2d & p2);

            friend std::ostream & operator<<(std::ostream & os, const point2d & p);

            friend struct std::hash<point2d>;

        private:
            double xCoord, yCoord;
        };

        point2d p2d(double x, double y);

        bool operator==(const point2d & p1, const point2d & p2);
        bool operator!=(const point2d & p1, const point2d & p2);
        bool operator<(const point2d & p1, const point2d & p2);
        bool operator<=(const point2d & p1, const point2d & p2);
        bool operator>(const point2d & p1, const point2d & p2);
        bool operator>=(const point2d & p1, const point2d & p2);
        std::ostream & operator<<(std::ostream & os, const point2d & p);
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
            return hash<double>()(p.xCoord) ^ hash<double>()(p.yCoord);
        }
    };
}

#endif
