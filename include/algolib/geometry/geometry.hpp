/*!
 * \file geometry.hpp
 * \brief Basic geometrical operations
 */
#ifndef GEOMETRY_HPP_
#define GEOMETRY_HPP_

#include <cstdlib>
#include <cmath>
#include "point3d.hpp"
#include "vector3d.hpp"

namespace algolib::geometry
{
    point2d translate(const point2d & p, const vector2d & v);

    point3d translate(const point3d & p, const vector3d & v);
}

#endif
