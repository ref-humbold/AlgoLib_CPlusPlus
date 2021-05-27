/*!
 * \file geometry2d.hpp
 * \brief Basic geometric operations in 2 dimensions
 */
#ifndef GEOMETRY_2D_HPP_
#define GEOMETRY_2D_HPP_

#include <cmath>
#include <cstdlib>
#include "point2d.hpp"
#include "vector2d.hpp"

namespace algolib::geometry::plane
{
    /*!
     * \brief Mutably sorts points by their X coordinate. Sorting is guaranteed to be stable.
     * \param points vector of points
     */
    void sort_by_x(std::vector<point2d> & points);

    /*!
     * \brief Mutably sorts points by their Y coordinate. Sorting is guaranteed to be stable.
     * \param points vector of points
     */
    void sort_by_y(std::vector<point2d> & points);

    /*!
     * \brief Mutably sorts points by their polar coordinates.
     * First sorts by angle, then by radius.
     * \param points vector of points
     */
    void sort_by_angle(std::vector<point2d> & points);

    double distance(const point2d & p1, const point2d & p2);

    point2d translate(const point2d & p, const vector2d & v);
}

#endif
