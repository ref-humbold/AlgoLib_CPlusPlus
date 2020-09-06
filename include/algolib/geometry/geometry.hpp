/*!
 * \file geometry.hpp
 * \brief Basic geometric operations
 */
#ifndef GEOMETRY_HPP_
#define GEOMETRY_HPP_

#include <cstdlib>
#include <cmath>
#include "point.hpp"
#include "vector.hpp"

namespace algolib::geometry
{
    template <size_t N>
    double distance(const point<N> & p1, const point<N> & p2)
    {
        double dist;

        for(size_t i = 1; i <= N; ++i)
            dist += (p2[i] - p1[i]) * (p2[i] - p1[i]);

        return sqrt(dist);
    }

    double distance(const point2d & p1, const point2d & p2);

    double distance(const point3d & p1, const point3d & p2);

    template <size_t N>
    point<N> translate(const point<N> & p, const vector<N> & v)
    {
        std::array<double, N> coords;

        for(size_t i = 1; i <= N; ++i)
            coords[i] = p[i] + v[i];

        return point<N>(coords);
    }

    point2d translate(const point2d & p, const vector2d & v);

    point3d translate(const point3d & p, const vector3d & v);
}

#endif
