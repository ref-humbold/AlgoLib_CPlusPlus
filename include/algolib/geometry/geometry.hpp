/*!
 * \file geometry.hpp
 * \brief Basic geometric operations
 */
#ifndef GEOMETRY_HPP_
#define GEOMETRY_HPP_

#include <cstdlib>
#include "point.hpp"
#include "vector.hpp"

namespace algolib::geometry
{
    vector2d make_vector(const point2d & begin, const point2d & end);

    vector3d make_vector(const point3d & begin, const point3d & end);

    double distance(const point2d & p1, const point2d & p2);

    double distance(const point3d & p1, const point3d & p2);

    point2d translate(const point2d & p, const vector2d & v);

    point3d translate(const point3d & p, const vector3d & v);
}

#endif
