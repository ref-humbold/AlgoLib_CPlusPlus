/*!
 * \file points_sorting.hpp
 * \brief Algorithms for points sorting
 */
#ifndef POINTS_SORTING_HPP_
#define POINTS_SORTING_HPP_

#include <cstdlib>
#include <algorithm>
#include <vector>
#include "point.hpp"

namespace algolib::geometry
{
    /*!
     * \brief Mutably sorts points with respect to their X coordinate. Sorting is guaranteed to be stable.
     * \param points vector of points
     */
    void sort_by_x(std::vector<point2d> & points);

    /*!
     * \brief Mutably sorts points with respect to their X coordinate. Sorting is guaranteed to be stable.
     * \param points vector of points
     */
    void sort_by_x(std::vector<point3d> & points);

    /*!
     * \brief Mutably sorts points with respect to their Y coordinate. Sorting is guaranteed to be stable.
     * \param points vector of points
     */
    void sort_by_y(std::vector<point2d> & points);

    /*!
     * \brief Mutably sorts points with respect to their Y coordinate. Sorting is guaranteed to be stable.
     * \param points vector of points
     */
    void sort_by_y(std::vector<point3d> & points);

    /*!
     * \brief Mutably sorts points with respect to their Z coordinate. Sorting is guaranteed to be stable.
     * \param points vector of points
     */
    void sort_by_z(std::vector<point3d> & points);

    /*!
     * \brief Mutably sorts points with respect to their polar coordinates.
     * First sorts by angle, then by radius.
     * \param points vector of points
     */
    void sort_by_angle(std::vector<point2d> & points);
}

#endif
