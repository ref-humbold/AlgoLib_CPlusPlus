/*!
 * \file geometry_3d.hpp
 * \brief Algorithms for basic geometrical computations in 2D
 */
#ifndef GEOMETRY_3D_HPP_
#define GEOMETRY_3D_HPP_

#include <cmath>
#include <cstdlib>
#include "point_3d.hpp"
#include "vector_3d.hpp"

namespace algolib::geometry::dim3
{
    /*!
     * \brief Mutably sorts points by their X coordinate. Sorting is guaranteed to be stable.
     * \param points vector of points
     */
    void sort_by_x(std::vector<point_3d> & points);

    /*!
     * \brief Mutably sorts points by their Y coordinate. Sorting is guaranteed to be stable.
     * \param points vector of points
     */
    void sort_by_y(std::vector<point_3d> & points);

    /*!
     * \brief Mutably sorts points by their Z coordinate. Sorting is guaranteed to be stable.
     * \param points vector of points
     */
    void sort_by_z(std::vector<point_3d> & points);

    double distance(const point_3d & p1, const point_3d & p2);

    point_3d translate(const point_3d & p, const vector_3d & v);
}

#endif
