/*!
 * \file convex_hull.hpp
 * \brief Algorithm for convex hull in 2D (Graham's scan).
 */
#ifndef CONVEX_HULL_HPP_
#define CONVEX_HULL_HPP_

#include <cstdlib>
#include <vector>
#include "algolib/geometry/dim2/point_2d.hpp"

namespace algolib::geometry::dim2
{
    /*!
     * \brief Computes convex hull of given points.
     * \param points the points
     * \return the points in the convex hull
     */
    std::vector<point_2d> find_convex_hull(const std::vector<point_2d> & points);
}

#endif
