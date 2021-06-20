/*!
 * \file vector3d.hpp
 * \brief Structure of vector in 3 dimensions
 */
#ifndef VECTOR_3D_HPP_
#define VECTOR_3D_HPP_

#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>
#include "../geometry_object.hpp"
#include "point3d.hpp"

namespace algolib::geometry::space
{
    class vector3d : public algolib::geometry::geometry_object
    {
    public:
        vector3d(double x, double y, double z) : x_{x}, y_{y}, z_{z}
        {
        }

        ~vector3d() override = default;
        vector3d(const vector3d &) = default;
        vector3d(vector3d &&) = default;
        vector3d & operator=(const vector3d &) = default;
        vector3d & operator=(vector3d &&) = default;

        static vector3d between(const point3d & begin, const point3d & end)
        {
            return vector3d(end.x() - begin.x(), end.y() - begin.y(), end.z() - begin.z());
        }

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

        vector3d & operator+=(const vector3d & v);
        vector3d & operator-=(const vector3d & v);
        vector3d & operator*=(double c);
        vector3d & operator/=(double c);

        friend bool operator==(const vector3d & v1, const vector3d & v2);
        friend bool operator!=(const vector3d & v1, const vector3d & v2);
        friend vector3d operator+(vector3d v1, const vector3d & v2);
        friend vector3d operator-(vector3d v1, const vector3d & v2);
        friend vector3d operator*(vector3d v, double c);
        friend vector3d operator*(double c, vector3d v);
        friend vector3d operator/(vector3d v, double c);
        friend std::ostream & operator<<(std::ostream & os, const vector3d & v);
        friend double dot(const vector3d & v1, const vector3d & v2);
        friend vector3d cross(const vector3d & v1, const vector3d & v2);

        friend struct std::hash<vector3d>;

    private:
        double x_, y_, z_;
    };

    bool operator==(const vector3d & v1, const vector3d & v2);
    bool operator!=(const vector3d & v1, const vector3d & v2);
    vector3d operator+(vector3d v1, const vector3d & v2);
    vector3d operator-(vector3d v1, const vector3d & v2);
    vector3d operator*(vector3d v, double c);
    vector3d operator*(double c, vector3d v);
    vector3d operator/(vector3d v, double c);
    std::ostream & operator<<(std::ostream & os, const vector3d & v);
    double dot(const vector3d & v1, const vector3d & v2);
    vector3d cross(const vector3d & v1, const vector3d & v2);
}

namespace std
{
    template <>
    struct hash<algolib::geometry::space::vector3d>
    {
        using argument_type = algolib::geometry::space::vector3d;
        using result_type = size_t;

        result_type operator()(const argument_type & v)
        {
            size_t x_hash = hash<double>()(v.x_);
            size_t y_hash = hash<double>()(v.y_);
            size_t z_hash = hash<double>()(v.z_);
            size_t xy_hash = x_hash ^ (y_hash + 0x9e3779b9 + (x_hash << 6) + (x_hash >> 2));

            return z_hash ^ (xy_hash + 0x9e3779b9 + (z_hash << 6) + (z_hash >> 2));
        }
    };
}

#endif
