/*!
 * \file points_sorting.hpp
 * \brief Algorithms for points sorting
 */
#ifndef POINTS_SORTING_HPP_
#define POINTS_SORTING_HPP_

#include <cstdlib>
#include <algorithm>
#include <vector>
#include "point2d.hpp"

namespace algolib::geometry
{
    /*!
         * \brief Mutably sorts points with respect to their coordinates.
         * First sorts by X coordinate, then by Y coordinate.
         *
         * \param points vector of points
         */
    void sort_by_x(std::vector<point2d> & points);

    /*!
         * \brief Mutably sorts points with respect to their coordinates.
         * First sorts by Y coordinate, then by X coordinate.
         *
         * \param points vector of points
         */
    void sort_by_y(std::vector<point2d> & points);

    /*!
         * \brief Mutably sorts points with respect to their polar coordinates.
         *
         * First sorts by angle, then by radius
         * \param points vector of points
         */
    void sort_by_angle(std::vector<point2d> & points);
}

#endif
