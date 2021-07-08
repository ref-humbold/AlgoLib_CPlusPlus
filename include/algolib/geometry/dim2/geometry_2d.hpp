/*!
 * \file geometry_2d.hpp
 * \brief Algorithms for basic geometrical computations in 2D
 */
#ifndef GEOMETRY_2D_HPP_
#define GEOMETRY_2D_HPP_

#include <cmath>
#include <cstdlib>
#include "point_2d.hpp"
#include "vector_2d.hpp"

namespace algolib::geometry::dim2
{
    /*!
     * \brief Mutably sorts points by their X coordinate. Sorting is guaranteed to be stable.
     * \param points vector of points
     */
    void sort_by_x(std::vector<point_2d> & points);

    /*!
     * \brief Mutably sorts points by their Y coordinate. Sorting is guaranteed to be stable.
     * \param points vector of points
     */
    void sort_by_y(std::vector<point_2d> & points);

    /*!
     * \brief Mutably sorts points by their polar coordinates.
     * First sorts by angle, then by radius.
     * \param points vector of points
     */
    void sort_by_angle(std::vector<point_2d> & points);

    double distance(const point_2d & p1, const point_2d & p2);

    point_2d translate(const point_2d & p, const vector_2d & v);
}

#endif
