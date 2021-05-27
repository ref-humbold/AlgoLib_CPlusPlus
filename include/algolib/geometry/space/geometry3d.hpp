/*!
 * \file geometry3d.hpp
 * \brief Basic geometric operations in 3 dimensions
 */
#ifndef GEOMETRY_3D_HPP_
#define GEOMETRY_3D_HPP_

#include <cmath>
#include <cstdlib>
#include "point3d.hpp"
#include "vector3d.hpp"

namespace algolib::geometry::space
{
    /*!
     * \brief Mutably sorts points by their X coordinate. Sorting is guaranteed to be stable.
     * \param points vector of points
     */
    void sort_by_x(std::vector<point3d> & points);

    /*!
     * \brief Mutably sorts points by their Y coordinate. Sorting is guaranteed to be stable.
     * \param points vector of points
     */
    void sort_by_y(std::vector<point3d> & points);

    /*!
     * \brief Mutably sorts points by their Z coordinate. Sorting is guaranteed to be stable.
     * \param points vector of points
     */
    void sort_by_z(std::vector<point3d> & points);

    double distance(const point3d & p1, const point3d & p2);

    point3d translate(const point3d & p, const vector3d & v);
}

#endif
