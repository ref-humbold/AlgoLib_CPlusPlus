/*!
 * \file convex_hull.hpp
 * \brief Algorithm for convex hull (monotone chain)
 */
#ifndef CONVEX_HULL_HPP_
#define CONVEX_HULL_HPP_

#include <cstdlib>
#include <vector>
#include "point2d.hpp"

namespace algolib::geometry::plane
{
    /*!
     * \brief Constructs a convex hull of given points.
     * \param points a vector of points
     * \return vector of hull points
     */
    std::vector<point2d> find_convex_hull(std::vector<point2d> points);
}

#endif
