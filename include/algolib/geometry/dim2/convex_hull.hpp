/*!
 * \file convex_hull.hpp
 * \brief Algorithm for convex hull (monotone chain) in 2D
 */
#ifndef CONVEX_HULL_HPP_
#define CONVEX_HULL_HPP_

#include <cstdlib>
#include <vector>
#include "algolib/geometry/dim2/point_2d.hpp"

namespace algolib::geometry::dim2
{
    /*!
     * \brief Constructs convex hull of given points.
     * \param points the points
     * \return the points in the convex hull
     */
    std::vector<point_2d> find_convex_hull(std::vector<point_2d> points);
}

#endif
