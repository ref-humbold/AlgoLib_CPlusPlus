/*!
 * \file point3d.hpp
 * \brief Structure of point in 3 dimensions
 */
#ifndef POINT_3D_HPP_
#define POINT_3D_HPP_

#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <array>
#include <exception>
#include <iostream>
#include <numeric>
#include <stdexcept>

namespace algolib::geometry::space
{
    class point3d
    {
    public:
        point3d(double x, double y, double z) : x_{x}, y_{y}, z_{z}
        {
        }

        ~point3d() = default;
        point3d(const point3d &) = default;
        point3d(point3d &&) = default;
        point3d & operator=(const point3d &) = default;
        point3d & operator=(point3d &&) = default;

        double x() const
        {
            return x_;
        }

        double y() const
        {
            return y_;
        }

        double z() const
        {
            return z_;
        }

        double radius() const
        {
            return sqrt(x_ * x_ + y_ * y_ + z_ * z_);
        }

        friend bool operator==(const point3d & p1, const point3d & p2);
        friend bool operator!=(const point3d & p1, const point3d & p2);
        friend std::ostream & operator<<(std::ostream & os, const point3d & p);

        friend struct std::hash<point3d>;

    private:
        double x_, y_, z_;
    };

    bool operator==(const point3d & p1, const point3d & p2);
    bool operator!=(const point3d & p1, const point3d & p2);
    std::ostream & operator<<(std::ostream & os, const point3d & p);

#pragma endregion
}

namespace std
{
    template <>
    struct hash<algolib::geometry::space::point3d>
    {
        using argument_type = algolib::geometry::space::point3d;
        using result_type = size_t;

        result_type operator()(const argument_type & p)
        {
            size_t x_hash = hash<double>()(p.x_);
            size_t y_hash = hash<double>()(p.y_);
            size_t z_hash = hash<double>()(p.z_);
            size_t xy_hash = x_hash ^ (y_hash + 0x9e3779b9 + (x_hash << 6) + (x_hash >> 2));

            return z_hash ^ (xy_hash + 0x9e3779b9 + (z_hash << 6) + (z_hash >> 2));
        }
    };
}

#endif
