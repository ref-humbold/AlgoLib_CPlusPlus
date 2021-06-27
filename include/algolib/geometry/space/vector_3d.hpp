/*!
 * \file vector_3d.hpp
 * \brief Structure of vector in 3D
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
#include "point_3d.hpp"

namespace algolib::geometry::space
{
    class vector_3d : public algolib::geometry::geometry_object
    {
    public:
        vector_3d(double x, double y, double z) : x_{x}, y_{y}, z_{z}
        {
        }

        ~vector_3d() override = default;
        vector_3d(const vector_3d &) = default;
        vector_3d(vector_3d &&) = default;
        vector_3d & operator=(const vector_3d &) = default;
        vector_3d & operator=(vector_3d &&) = default;

        static vector_3d between(const point_3d & begin, const point_3d & end)
        {
            return vector_3d(end.x() - begin.x(), end.y() - begin.y(), end.z() - begin.z());
        }

        static double area(const vector_3d & v1, const vector_3d & v2);
        static double volume(const vector_3d & v1, const vector_3d & v2, const vector_3d & v3);

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

        vector_3d & operator+=(const vector_3d & v);
        vector_3d & operator-=(const vector_3d & v);
        vector_3d & operator*=(double c);
        vector_3d & operator/=(double c);

        friend bool operator==(const vector_3d & v1, const vector_3d & v2);
        friend bool operator!=(const vector_3d & v1, const vector_3d & v2);
        friend vector_3d operator+(vector_3d v1, const vector_3d & v2);
        friend vector_3d operator-(vector_3d v1, const vector_3d & v2);
        friend vector_3d operator*(vector_3d v, double c);
        friend vector_3d operator*(double c, vector_3d v);
        friend vector_3d operator/(vector_3d v, double c);
        friend std::ostream & operator<<(std::ostream & os, const vector_3d & v);
        friend double dot(const vector_3d & v1, const vector_3d & v2);
        friend vector_3d cross(const vector_3d & v1, const vector_3d & v2);

        friend struct std::hash<vector_3d>;

    private:
        double x_, y_, z_;
    };

    bool operator==(const vector_3d & v1, const vector_3d & v2);
    bool operator!=(const vector_3d & v1, const vector_3d & v2);
    vector_3d operator+(vector_3d v1, const vector_3d & v2);
    vector_3d operator-(vector_3d v1, const vector_3d & v2);
    vector_3d operator*(vector_3d v, double c);
    vector_3d operator*(double c, vector_3d v);
    vector_3d operator/(vector_3d v, double c);
    std::ostream & operator<<(std::ostream & os, const vector_3d & v);
    double dot(const vector_3d & v1, const vector_3d & v2);
    vector_3d cross(const vector_3d & v1, const vector_3d & v2);
}

namespace std
{
    template <>
    struct hash<algolib::geometry::space::vector_3d>
    {
        using argument_type = algolib::geometry::space::vector_3d;
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
