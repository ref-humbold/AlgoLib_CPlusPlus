/*!
 * \file convex_hull.hpp
 * \brief Algorithms for convex hull in 2D.
 */
#ifndef CONVEX_HULL_HPP_
#define CONVEX_HULL_HPP_

#include <vector>
#include "algolib/geometry/dim2/point_2d.hpp"

namespace algolib::geometry::dim2
{
    /*!
     * \brief Computes convex hull of given points using Andrew's monotone chain.
     * \param points the points
     * \return the points in the convex hull
     */
    std::vector<point_2d> find_andrew_convex_hull(std::vector<point_2d> points);

    /*!
     * \brief Computes convex hull of given points using Graham's scan.
     * \param points the points
     * \return the points in the convex hull
     */
    std::vector<point_2d> find_graham_convex_hull(const std::vector<point_2d> & points);
}

#endif
