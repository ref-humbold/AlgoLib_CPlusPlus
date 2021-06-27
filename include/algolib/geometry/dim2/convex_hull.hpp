/*!
 * \file convex_hull.hpp
 * \brief Algorithm for convex hull (monotone chain) in 2D
 */
#ifndef CONVEX_HULL_HPP_
#define CONVEX_HULL_HPP_

#include <cstdlib>
#include <vector>
#include "point_2d.hpp"

namespace algolib::geometry::plane
{
    /*!
     * \brief Constructs a convex hull of given points.
     * \param points a vector of points
     * \return vector of hull points
     */
    std::vector<point_2d> find_convex_hull(std::vector<point_2d> points);
}

#endif
