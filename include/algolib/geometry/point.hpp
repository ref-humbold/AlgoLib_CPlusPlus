/*!
 * \file point.hpp
 * \brief Structure of point on a plane or in a space
 */
#ifndef POINT_HPP_
#define POINT_HPP_

#include <cstdlib>
#include <cmath>
#include <iostream>

namespace algolib::geometry
{
    class point2d;

    class point3d;
}

namespace std
{
    template <>
    struct hash<algolib::geometry::point2d>;

    template <>
    struct hash<algolib::geometry::point3d>;
}

namespace algolib::geometry
{
#pragma region point2d

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
            return sqrt(x_ * x_ + y_ * y_);
        }

        friend bool operator==(const point2d & p1, const point2d & p2);
        friend bool operator!=(const point2d & p1, const point2d & p2);
        friend std::ostream & operator<<(std::ostream & os, const point2d & p);

        friend struct std::hash<point2d>;

        static const point2d zero;

    private:
        double x_, y_;
    };

    bool operator==(const point2d & p1, const point2d & p2);
    bool operator!=(const point2d & p1, const point2d & p2);
    std::ostream & operator<<(std::ostream & os, const point2d & p);

#pragma endregion
#pragma region point3d

    class point3d
    {
    public:
        point3d(double x, double y, double z) : x_{x}, y_{y}, z_{z}
        {
        }

        explicit point3d(const point2d & p) : x_{p.x()}, y_{p.y()}, z_{0}
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

        static const point3d zero;

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

    template <>
    struct hash<algolib::geometry::point3d>
    {
        using argument_type = algolib::geometry::point3d;
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
