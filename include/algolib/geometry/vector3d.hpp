/*!
 * \file vector3d.hpp
 * \brief Structure of vector in a space
 */
#ifndef VECTOR3D_HPP_
#define VECTOR3D_HPP_

#include <cstdlib>
#include <cmath>
#include <iostream>
#include "vector2d.hpp"

namespace algolib
{
    namespace geometry
    {
        class vector3d;
    }
}

namespace std
{
    template <>
    struct hash<algolib::geometry::vector3d>;
}

namespace algolib
{
    namespace geometry
    {
        class vector3d
        {
        public:
            vector3d(double x, double y, double z) : x_{x}, y_{y}, z_{z}
            {
            }

            explicit vector3d(const vector2d & v) : x_{v.x()}, y_{v.y()}, z_{0}
            {
            }

            ~vector3d() = default;
            vector3d(const vector3d &) = default;
            vector3d(vector3d &&) = default;
            vector3d & operator=(const vector3d &) = default;
            vector3d & operator=(vector3d &&) = default;

            static double area(const vector3d & v1, const vector3d & v2);
            static double volume(const vector3d & v1, const vector3d & v2, const vector3d & v3);

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

            double length() const
            {
                return sqrt(x_ * x_ + y_ * y_ + z_ * z_);
            }

            friend bool operator==(const vector3d & v1, const vector3d & v2);
            friend bool operator!=(const vector3d & v1, const vector3d & v2);
            friend vector3d operator+(vector3d v1, const vector3d & v2);
            friend vector3d operator-(vector3d v1, const vector3d & v2);
            friend double operator*(const vector3d & v1, const vector3d & v2);
            friend vector3d operator*(vector3d v, double c);
            friend vector3d operator*(double c, vector3d v);
            friend vector3d operator/(vector3d v, double c);
            friend vector3d operator^(const vector3d & v1, const vector3d & v2);
            friend std::ostream & operator<<(std::ostream & os, const vector3d & v);

            friend struct std::hash<vector3d>;

        private:
            double x_, y_, z_;
        };

        bool operator==(const vector3d & v1, const vector3d & v2);
        bool operator!=(const vector3d & v1, const vector3d & v2);
        vector3d operator+(vector3d v1, const vector3d & v2);
        vector3d operator-(vector3d v1, const vector3d & v2);
        double operator*(const vector3d & v1, const vector3d & v2);
        vector3d operator*(vector3d v, double c);
        vector3d operator*(double c, vector3d v);
        vector3d operator/(vector3d v, double c);
        vector3d operator^(const vector3d & v1, const vector3d & v2);
        std::ostream & operator<<(std::ostream & os, const vector3d & v);
    }
}

namespace std
{
    template <>
    struct hash<algolib::geometry::vector3d>
    {
        using argument_type = algolib::geometry::vector3d;
        using result_type = size_t;

        result_type operator()(const argument_type & v)
        {
            size_t x_hash = hash<double>()(v.x_);
            size_t y_hash = hash<double>()(v.y_);
            size_t z_hash = hash<double>()(v.z_);
            size_t xy_hash = x_hash ^ (y_hash + 0x9e3d79b9 + (x_hash << 6) + (x_hash >> 2));

            return z_hash ^ (xy_hash + 0x9e3d79b9 + (z_hash << 6) + (z_hash >> 2));
        }
    };
}

#endif
