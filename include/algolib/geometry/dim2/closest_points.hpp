/*!
 * \file closest_points.hpp
 * \brief Algorithm for pair of closest points in 2D
 */
#ifndef CLOSEST_POINTS_HPP_
#define CLOSEST_POINTS_HPP_

#include <cstdlib>
#include <vector>
#include "point_2d.hpp"

namespace algolib::geometry::dim2
{
    /*!
     * \brief Searches for closest points among given points.
     * \param points a vector of points
     * \return pair of closest points
     */
    std::pair<point_2d, point_2d> find_closest_points(const std::vector<point_2d> & points);
}

#endif
