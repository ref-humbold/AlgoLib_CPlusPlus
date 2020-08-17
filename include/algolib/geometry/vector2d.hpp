/*!
 * \file vector2d.hpp
 * \brief Structure of vector on a plane
 */
#ifndef VECTOR2D_HPP_
#define VECTOR2D_HPP_

#include <cstdlib>
#include <cmath>
#include <iostream>

namespace algolib
{
    namespace geometry
    {
        class vector2d;
    }
}

namespace std
{
    template <>
    struct hash<algolib::geometry::vector2d>;
}

namespace algolib
{
    namespace geometry
    {
        class vector2d
        {
        public:
            vector2d(double x, double y) : x_{x}, y_{y}
            {
            }

            ~vector2d() = default;
            vector2d(const vector2d &) = default;
            vector2d(vector2d &&) = default;
            vector2d & operator=(const vector2d &) = default;
            vector2d & operator=(vector2d &&) = default;

            static double area(const vector2d & v1, const vector2d & v2);

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

            friend bool operator==(const vector2d & v1, const vector2d & v2);
            friend bool operator!=(const vector2d & v1, const vector2d & v2);
            friend vector2d operator+(vector2d v1, const vector2d & v2);
            friend vector2d operator-(vector2d v1, const vector2d & v2);
            friend double operator*(const vector2d & v1, const vector2d & v2);
            friend vector2d operator*(vector2d v, double c);
            friend vector2d operator*(double c, vector2d v);
            friend vector2d operator/(vector2d v, double c);
            friend std::ostream & operator<<(std::ostream & os, const vector2d & v);

            friend struct std::hash<vector2d>;

        private:
            double x_, y_;
        };

        bool operator==(const vector2d & v1, const vector2d & v2);
        bool operator!=(const vector2d & v1, const vector2d & v2);
        vector2d operator+(vector2d v1, const vector2d & v2);
        vector2d operator-(vector2d v1, const vector2d & v2);
        double operator*(const vector2d & v1, const vector2d & v2);
        vector2d operator*(vector2d v, double c);
        vector2d operator*(double c, vector2d v);
        vector2d operator/(vector2d v, double c);
        std::ostream & operator<<(std::ostream & os, const vector2d & v);
    }
}

namespace std
{
    template <>
    struct hash<algolib::geometry::vector2d>
    {
        using argument_type = algolib::geometry::vector2d;
        using result_type = size_t;

        result_type operator()(const argument_type & v)
        {
            size_t x_hash = hash<double>()(v.x_);
            size_t y_hash = hash<double>()(v.y_);

            return x_hash ^ (y_hash + 0x9e3d79b9 + (x_hash << 6) + (x_hash >> 2));
        }
    };
}

#endif
