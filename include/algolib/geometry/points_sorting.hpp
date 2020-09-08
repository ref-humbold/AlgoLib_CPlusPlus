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
     * \brief Mutably sorts points by given coordinate index. Sorting is guaranteed to be stable.
     * \param i coordinate index
     * \param points vector of points
     */
    template <size_t N>
    void sort_by_dim(size_t i, std::vector<point<N>> & points)
    {
        auto comparator = [&](const point<N> & pt1, const point<N> & pt2) {
            return pt1[i] < pt2[i];
        };

        std::stable_sort(points.begin(), points.end(), comparator);
    }

    /*!
     * \brief Mutably sorts points by their X coordinate. Sorting is guaranteed to be stable.
     * \param points vector of points
     */
    void sort_by_x(std::vector<point2d> & points);

    /*!
     * \brief Mutably sorts points by their X coordinate. Sorting is guaranteed to be stable.
     * \param points vector of points
     */
    void sort_by_x(std::vector<point3d> & points);

    /*!
     * \brief Mutably sorts points by their Y coordinate. Sorting is guaranteed to be stable.
     * \param points vector of points
     */
    void sort_by_y(std::vector<point2d> & points);

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

    /*!
     * \brief Mutably sorts points by their polar coordinates.
     * First sorts by angle, then by radius.
     * \param points vector of points
     */
    void sort_by_angle(std::vector<point2d> & points);
}

#endif
