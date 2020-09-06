/*!
 * \file vector.hpp
 * \brief Structure of vector on a plane or in a space
 */
#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>

namespace algolib::geometry
{
    template <size_t N>
    class vector;

    template <size_t N>
    bool operator==(const vector<N> & v1, const vector<N> & v2);

    template <size_t N>
    bool operator!=(const vector<N> & v1, const vector<N> & v2);

    template <size_t N>
    vector<N> operator+(vector<N> v1, const vector<N> & v2);

    template <size_t N>
    vector<N> operator-(vector<N> v1, const vector<N> & v2);

    template <size_t N>
    double operator*(const vector<N> & v1, const vector<N> & v2);

    template <size_t N>
    vector<N> operator*(vector<N> v, double c);

    template <size_t N>
    vector<N> operator*(double c, vector<N> v);

    template <size_t N>
    vector<N> operator/(vector<N> v, double c);

    template <size_t N>
    std::ostream & operator<<(std::ostream & os, const vector<N> & v);

    class vector2d;

    class vector3d;
}

namespace std
{
    template <size_t N>
    struct hash<algolib::geometry::vector<N>>;

    template <>
    struct hash<algolib::geometry::vector2d>;

    template <>
    struct hash<algolib::geometry::vector3d>;
}

namespace algolib::geometry
{
#pragma region vector

    template <size_t N>
    class vector
    {
    public:
        explicit vector(std::array<double, N> coordinates) : coordinates{coordinates}
        {
        }

        ~vector() = default;
        vector(const vector &) = default;
        vector(vector &&) = default;
        vector & operator=(const vector &) = default;
        vector & operator=(vector &&) = default;

        double operator[](size_t i) const;
        double length() const;

        template <size_t M>
        vector<M> project() const;

        vector<N> & operator+=(const vector<N> & v);
        vector<N> & operator-=(const vector<N> & v);
        vector<N> & operator*=(double c);
        vector<N> & operator/=(double c);

        // clang-format off
        friend bool operator== <N>(const vector<N> & v1, const vector<N> & v2);
        friend bool operator!= <N>(const vector<N> & v1, const vector<N> & v2);
        friend vector<N> operator+ <N>(vector<N> v1, const vector<N> & v2);
        friend vector<N> operator- <N>(vector<N> v1, const vector<N> & v2);
        friend double operator* <N>(const vector<N> & v1, const vector<N> & v2);
        friend vector<N> operator* <N>(vector<N> v, double c);
        friend vector<N> operator* <N>(double c, vector<N> v);
        friend vector<N> operator/ <N>(vector<N> v, double c);
        friend std::ostream & operator<< <N>(std::ostream & os, const vector<N> & v);
        // clang-format on

        friend struct std::hash<vector<N>>;

    private:
        std::array<double, N> coordinates;
    };

    template <>
    class vector<0>;

    template <size_t N>
    double vector<N>::operator[](size_t i) const
    {
        if(i == 0 || i > coordinates.size())
            throw std::out_of_range("Coordinate index has to be between 1 and "
                                    + std::to_string(coordinates.size()));

        return coordinates[i - 1];
    }

    template <size_t N>
    double vector<N>::length() const
    {
        return sqrt(std::accumulate(coordinates.begin(), coordinates.end(), 0.0,
                                    [](double acc, double coord) { return acc + coord * coord; }));
    }

    template <size_t N>
    template <size_t M>
    vector<M> vector<N>::project() const
    {
        if(M == 0)
            throw std::out_of_range();

        if(M == N)
            return *this;

        std::array<double, M> new_coords;

        new_coords.fill(0.0);
        std::copy_n(coordinates.begin(), std::min(N, M), new_coords.begin());
        return vector<M>(new_coords);
    }

    template <size_t N>
    vector<N> & vector<N>::operator+=(const vector<N> & v)
    {
        for(size_t i = 0; i < N; ++i)
            coordinates[i] += v.coordinates[i];
    }

    template <size_t N>
    vector<N> & vector<N>::operator-=(const vector<N> & v)
    {
        for(size_t i = 0; i < N; ++i)
            coordinates[i] -= v.coordinates[i];
    }

    template <size_t N>
    vector<N> & vector<N>::operator*=(double c)
    {
        for(size_t i = 0; i < N; ++i)
            coordinates[i] *= c;
    }

    template <size_t N>
    vector<N> & vector<N>::operator/=(double c)
    {
        for(size_t i = 0; i < N; ++i)
            coordinates[i] /= c;
    }

    template <size_t N>
    bool operator==(const vector<N> & v1, const vector<N> & v2)
    {
        return v1.coordinates == v2.coordinates;
    }

    template <size_t N>
    bool operator!=(const vector<N> & v1, const vector<N> & v2)
    {
        return !(v1 == v2);
    }

    template <size_t N>
    vector<N> operator+(vector<N> v1, const vector<N> & v2)
    {
        v1 += v2;
        return v1;
    }

    template <size_t N>
    vector<N> operator-(vector<N> v1, const vector<N> & v2)
    {
        v1 -= v2;
        return v1;
    }

    template <size_t N>
    double operator*(const vector<N> & v1, const vector<N> & v2)
    {
        double dot;

        for(size_t i = 0; i < N; ++i)
            dot += v1.coordinates[i] * v2.coordinates[i];

        return dot;
    }

    template <size_t N>
    vector<N> operator*(vector<N> v, double c)
    {
        v *= c;
        return v;
    }

    template <size_t N>
    vector<N> operator*(double c, vector<N> v)
    {
        v *= c;
        return v;
    }

    template <size_t N>
    vector<N> operator/(vector<N> v, double c)
    {
        v /= c;
        return v;
    }

    template <size_t N>
    std::ostream & operator<<(std::ostream & os, const vector<N> & v)
    {
        os << "V[" << v.coordinates[0];

        for(size_t i = 1; i < v.coordinates.size(); ++i)
            os << ", " << v.coordinates[i];

        os << "]";
        return os;
    }

#pragma endregion
#pragma region vector2d

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

        static vector2d from_vector(const vector<2> & v)
        {
            return vector2d(v[1], v[2]);
        }

        double x() const
        {
            return x_;
        }

        double y() const
        {
            return y_;
        }

        vector<2> to_vector() const
        {
            return vector<2>({x_, y_});
        }

        double length() const
        {
            return sqrt(x_ * x_ + y_ * y_);
        }

        vector2d & operator+=(const vector2d & v);
        vector2d & operator-=(const vector2d & v);
        vector2d & operator*=(double c);
        vector2d & operator/=(double c);

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

#pragma endregion
#pragma region vector3d

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

        static vector3d from_vector(const vector<3> & v)
        {
            return vector3d(v[1], v[2], v[3]);
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

        vector<3> to_vector() const
        {
            return vector<3>({x_, y_, z_});
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

#pragma endregion
}

namespace std
{
    template <size_t N>
    struct hash<algolib::geometry::vector<N>>
    {
        using argument_type = algolib::geometry::vector<N>;
        using result_type = size_t;

        result_type operator()(const argument_type & v)
        {
            size_t full_hash;

            for(auto && c : v.coordinates)
            {
                size_t c_hash = hash<double>()(c);
                full_hash = c_hash ^ (full_hash + 0x9e3779b9 + (c_hash << 6) + (c_hash >> 2));
            }

            return full_hash;
        }
    };

    template <>
    struct hash<algolib::geometry::vector2d>
    {
        using argument_type = algolib::geometry::vector2d;
        using result_type = size_t;

        result_type operator()(const argument_type & v)
        {
            size_t x_hash = hash<double>()(v.x_);
            size_t y_hash = hash<double>()(v.y_);

            return x_hash ^ (y_hash + 0x9e3779b9 + (x_hash << 6) + (x_hash >> 2));
        }
    };

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
            size_t xy_hash = x_hash ^ (y_hash + 0x9e3779b9 + (x_hash << 6) + (x_hash >> 2));

            return z_hash ^ (xy_hash + 0x9e3779b9 + (z_hash << 6) + (z_hash >> 2));
        }
    };
}

#endif
