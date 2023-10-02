/*!
 * \file point_3d.hpp
 * \brief Structure of point in 3D.
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
#include "algolib/geometry/geometry_object.hpp"

namespace algolib::geometry::dim3
{
    class point_3d : public algolib::geometry::geometry_object<3>
    {
    public:
        point_3d(double x, double y, double z) : x_{x}, y_{y}, z_{z}
        {
        }

        ~point_3d() override = default;
        point_3d(const point_3d &) = default;
        point_3d(point_3d &&) = default;
        point_3d & operator=(const point_3d &) = default;
        point_3d & operator=(point_3d &&) = default;

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

        std::array<double, 3> coordinates() const override
        {
            return {x_, y_, z_};
        }

        double radius() const
        {
            return sqrt(x_ * x_ + y_ * y_ + z_ * z_);
        }

        friend bool operator==(const point_3d & p1, const point_3d & p2);
        friend bool operator!=(const point_3d & p1, const point_3d & p2);
        friend std::ostream & operator<<(std::ostream & os, const point_3d & p);

        friend struct std::hash<point_3d>;

    private:
        double x_, y_, z_;
    };

    bool operator==(const point_3d & p1, const point_3d & p2);
    bool operator!=(const point_3d & p1, const point_3d & p2);
    std::ostream & operator<<(std::ostream & os, const point_3d & p);

#pragma endregion
}

namespace std
{
    template <>
    struct hash<algolib::geometry::dim3::point_3d>
    {
        using argument_type = algolib::geometry::dim3::point_3d;
        using result_type = size_t;

        result_type operator()(const argument_type & p)
        {
            result_type x_hash = std::hash<double>()(p.x_);
            result_type y_hash = std::hash<double>()(p.y_);
            result_type z_hash = std::hash<double>()(p.z_);
            result_type xy_hash = x_hash ^ (y_hash + 0x9e3779b9 + (x_hash << 6) + (x_hash >> 2));

            return z_hash ^ (xy_hash + 0x9e3779b9 + (z_hash << 6) + (z_hash >> 2));
        }
    };
}

#endif
