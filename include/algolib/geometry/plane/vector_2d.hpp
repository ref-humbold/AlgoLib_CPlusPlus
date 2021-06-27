/*!
 * \file vector_2d.hpp
 * \brief Structure of vector in 2D
 */
#ifndef VECTOR_2D_HPP_
#define VECTOR_2D_HPP_

#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>
#include "../geometry_object.hpp"
#include "point_2d.hpp"

namespace algolib::geometry::plane
{
    class vector_2d : public algolib::geometry::geometry_object
    {
    public:
        vector_2d(double x, double y) : x_{x}, y_{y}
        {
        }

        ~vector_2d() override = default;
        vector_2d(const vector_2d &) = default;
        vector_2d(vector_2d &&) = default;
        vector_2d & operator=(const vector_2d &) = default;
        vector_2d & operator=(vector_2d &&) = default;

        static vector_2d between(const point_2d & begin, const point_2d & end)
        {
            return vector_2d(end.x() - begin.x(), end.y() - begin.y());
        }

        static double area(const vector_2d & v1, const vector_2d & v2);

        double x() const
        {
            return x_;
        }

        double y() const
        {
            return y_;
        }

        double length() const
        {
            return sqrt(x_ * x_ + y_ * y_);
        }

        vector_2d & operator+=(const vector_2d & v);
        vector_2d & operator-=(const vector_2d & v);
        vector_2d & operator*=(double c);
        vector_2d & operator/=(double c);

        friend bool operator==(const vector_2d & v1, const vector_2d & v2);
        friend bool operator!=(const vector_2d & v1, const vector_2d & v2);
        friend vector_2d operator+(vector_2d v1, const vector_2d & v2);
        friend vector_2d operator-(vector_2d v1, const vector_2d & v2);
        friend vector_2d operator*(vector_2d v, double c);
        friend vector_2d operator*(double c, vector_2d v);
        friend vector_2d operator/(vector_2d v, double c);
        friend std::ostream & operator<<(std::ostream & os, const vector_2d & v);
        friend double dot(const vector_2d & v1, const vector_2d & v2);

        friend struct std::hash<vector_2d>;

    private:
        double x_, y_;
    };

    bool operator==(const vector_2d & v1, const vector_2d & v2);
    bool operator!=(const vector_2d & v1, const vector_2d & v2);
    vector_2d operator+(vector_2d v1, const vector_2d & v2);
    vector_2d operator-(vector_2d v1, const vector_2d & v2);
    vector_2d operator*(vector_2d v, double c);
    vector_2d operator*(double c, vector_2d v);
    vector_2d operator/(vector_2d v, double c);
    std::ostream & operator<<(std::ostream & os, const vector_2d & v);
    double dot(const vector_2d & v1, const vector_2d & v2);
}

namespace std
{
    template <>
    struct hash<algolib::geometry::plane::vector_2d>
    {
        using argument_type = algolib::geometry::plane::vector_2d;
        using result_type = size_t;

        result_type operator()(const argument_type & v)
        {
            size_t x_hash = hash<double>()(v.x_);
            size_t y_hash = hash<double>()(v.y_);

            return x_hash ^ (y_hash + 0x9e3779b9 + (x_hash << 6) + (x_hash >> 2));
        }
    };
}

#endif
