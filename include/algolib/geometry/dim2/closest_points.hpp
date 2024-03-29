/*!
 * \file closest_points.hpp
 * \brief Algorithm for searching pair of closest points in 2D.
 */
#ifndef CLOSEST_POINTS_HPP_
#define CLOSEST_POINTS_HPP_

#include <cstdlib>
#include <vector>
#include "algolib/geometry/dim2/point_2d.hpp"

namespace algolib::geometry::dim2
{
    /*!
     * \brief Searches for the pair of closest points among given points.
     * \param points the points
     * \return the pair of closest points
     */
    std::pair<point_2d, point_2d> find_closest_points(const std::vector<point_2d> & points);
}

#endif
