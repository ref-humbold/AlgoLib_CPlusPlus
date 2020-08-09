/*!
 * \file convex_hull.hpp
 * \brief Algorithm for convex hull on a plane (monotone chain)
 */
#ifndef CONVEX_HULL_HPP_
#define CONVEX_HULL_HPP_

#include <cstdlib>
#include <algorithm>
#include <vector>
#include "points_sorting.hpp"

namespace algolib::geometry
{
    /*!
     * \brief Constructs a convex hull of specified points.
     * \param points a vector of points
     * \return vector of hull points
     */
    std::vector<point2d> find_convex_hull(std::vector<point2d> points);
}

#endif
