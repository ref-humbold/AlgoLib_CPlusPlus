/*!
 * \file vector_2d.hpp
 * \brief Structure of vector in 2D.
 */
#ifndef VECTOR_2D_HPP_
#define VECTOR_2D_HPP_

#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>
#include "algolib/geometry/dim2/point_2d.hpp"
#include "algolib/geometry/geometry_object.hpp"

namespace algolib::geometry::dim2
{
    class vector_2d : public algolib::geometry::geometry_object<2>
    {
    public:
        vector_2d(double x, double y) : x_{x}, y_{y}
        {
        }

        vector_2d(const point_2d & begin, const point_2d & end)
            : x_{end.x() - begin.x()}, y_{end.y() - begin.y()}
        {
        }

        ~vector_2d() override = default;
        vector_2d(const vector_2d &) = default;
        vector_2d(vector_2d &&) = default;
        vector_2d & operator=(const vector_2d &) = default;
        vector_2d & operator=(vector_2d &&) = default;

        static double dot(const vector_2d & v1, const vector_2d & v2);
        static double area(const vector_2d & v1, const vector_2d & v2);

        double x() const
        {
            return x_;
        }

        double y() const
        {
            return y_;
        }

        std::array<double, 2> coordinates() const override
        {
            return {x_, y_};
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

        friend vector_2d operator+(vector_2d v);
        friend vector_2d operator-(vector_2d v);
        friend vector_2d operator+(vector_2d v1, const vector_2d & v2);
        friend vector_2d operator-(vector_2d v1, const vector_2d & v2);
        friend vector_2d operator*(vector_2d v, double c);
        friend vector_2d operator*(double c, vector_2d v);
        friend vector_2d operator/(vector_2d v, double c);

        friend std::ostream & operator<<(std::ostream & os, const vector_2d & v);

        friend struct std::hash<vector_2d>;

    private:
        double x_, y_;
    };

    bool operator==(const vector_2d & v1, const vector_2d & v2);
    bool operator!=(const vector_2d & v1, const vector_2d & v2);
    vector_2d operator+(vector_2d v);
    vector_2d operator-(vector_2d v);
    vector_2d operator+(vector_2d v1, const vector_2d & v2);
    vector_2d operator-(vector_2d v1, const vector_2d & v2);
    vector_2d operator*(vector_2d v, double c);
    vector_2d operator*(double c, vector_2d v);
    vector_2d operator/(vector_2d v, double c);
    std::ostream & operator<<(std::ostream & os, const vector_2d & v);
}

namespace std
{
    template <>
    struct hash<algolib::geometry::dim2::vector_2d>
    {
        using argument_type = algolib::geometry::dim2::vector_2d;
        using result_type = size_t;

        result_type operator()(const argument_type & v)
        {
            result_type x_hash = std::hash<double>()(v.x_);
            result_type y_hash = std::hash<double>()(v.y_);

            return x_hash ^ (y_hash + 0x9e3779b9 + (x_hash << 6) + (x_hash >> 2));
        }
    };
}

#endif
