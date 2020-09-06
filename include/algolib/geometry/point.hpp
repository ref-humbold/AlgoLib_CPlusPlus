/*!
 * \file point.hpp
 * \brief Structure of point on a plane or in a space
 */
#ifndef POINT_HPP_
#define POINT_HPP_

#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <array>
#include <exception>
#include <iostream>
#include <numeric>
#include <stdexcept>

namespace algolib::geometry
{
    template <size_t N>
    class point;

    template <size_t N>
    bool operator==(const point<N> & p1, const point<N> & p2);

    template <size_t N>
    bool operator!=(const point<N> & p1, const point<N> & p2);

    template <size_t N>
    std::ostream & operator<<(std::ostream & os, const point<N> & p);

    class point2d;

    class point3d;
}

namespace std
{
    template <size_t N>
    struct hash<algolib::geometry::point<N>>;

    template <>
    struct hash<algolib::geometry::point2d>;

    template <>
    struct hash<algolib::geometry::point3d>;
}

namespace algolib::geometry
{
#pragma region point

    template <size_t N>
    class point
    {
    public:
        explicit point(std::array<double, N> coordinates) : coordinates{coordinates}
        {
        }

        ~point() = default;
        point(const point &) = default;
        point(point &&) = default;
        point & operator=(const point &) = default;
        point & operator=(point &&) = default;

        double operator[](size_t i) const;
        double radius() const;

        template <size_t M>
        point<M> project() const;

        // clang-format off
        friend bool operator== <N>(const point<N> & p1, const point<N> & p2);
        friend bool operator!= <N>(const point<N> & p1, const point<N> & p2);
        friend std::ostream & operator<< <N>(std::ostream & os, const point<N> & p);
        // clang-format on

        friend struct std::hash<point<N>>;

    private:
        std::array<double, N> coordinates;
    };

    template <>
    class point<0>;

    template <size_t N>
    double point<N>::operator[](size_t i) const
    {
        if(i == 0 || i > coordinates.size())
            throw std::out_of_range("Coordinate index has to be between 1 and "
                                    + std::to_string(coordinates.size()));

        return coordinates[i - 1];
    }

    template <size_t N>
    double point<N>::radius() const
    {
        return sqrt(std::accumulate(coordinates.begin(), coordinates.end(), 0.0,
                                    [](double acc, double coord) { return acc + coord * coord; }));
    }

    template <size_t N>
    template <size_t M>
    point<M> point<N>::project() const
    {
        if(M == 0)
            throw std::out_of_range("Dimensions count has to be positive");

        if(M == N)
            return *this;

        std::array<double, M> new_coords;

        new_coords.fill(0.0);
        std::copy_n(coordinates.begin(), std::min(N, M), new_coords.begin());
        return point<M>(new_coords);
    }

    template <size_t N>
    bool operator==(const point<N> & p1, const point<N> & p2)
    {
        return p1.coordinates == p2.coordinates;
    }

    template <size_t N>
    bool operator!=(const point<N> & p1, const point<N> & p2)
    {
        return !(p1 == p2);
    }

    template <size_t N>
    std::ostream & operator<<(std::ostream & os, const point<N> & p)
    {
        os << "P(" << p.coordinates[0];

        for(size_t i = 1; i < p.coordinates.size(); ++i)
            os << ", " << p.coordinates[i];

        os << ")";
        return os;
    }

#pragma endregion
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

        static point2d from_point(point<2> p)
        {
            return point2d(p[1], p[2]);
        }

        double x() const
        {
            return x_;
        }

        double y() const
        {
            return y_;
        }

        point<2> to_point() const
        {
            return point<2>({x_, y_});
        }

        double radius() const
        {
            return sqrt(x_ * x_ + y_ * y_);
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

        friend bool operator==(const point2d & p1, const point2d & p2);
        friend bool operator!=(const point2d & p1, const point2d & p2);
        friend std::ostream & operator<<(std::ostream & os, const point2d & p);

        friend struct std::hash<point2d>;

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

        ~point3d() = default;
        point3d(const point3d &) = default;
        point3d(point3d &&) = default;
        point3d & operator=(const point3d &) = default;
        point3d & operator=(point3d &&) = default;

        static point3d from_point(point<3> p)
        {
            return point3d(p[1], p[2], p[3]);
        }

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

        point<3> to_point() const
        {
            return point<3>({x_, y_, z_});
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
    template <size_t N>
    struct hash<algolib::geometry::point<N>>
    {
        using argument_type = algolib::geometry::point<N>;
        using result_type = size_t;

        result_type operator()(const argument_type & p)
        {
            size_t full_hash;

            for(auto && c : p.coordinates)
            {
                size_t c_hash = hash<double>()(c);
                full_hash = c_hash ^ (full_hash + 0x9e3779b9 + (c_hash << 6) + (c_hash >> 2));
            }

            return full_hash;
        }
    };

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
