/*!
 * \file closest_points.hpp
 * \brief Algorithm for pair of closest points
 */
#ifndef CLOSEST_POINTS_HPP_
#define CLOSEST_POINTS_HPP_

#include <cstdlib>
#include <vector>
#include "point2d.hpp"

namespace algolib::geometry::plane
{
    /*!
     * \brief Searches for closest points among given points.
     * \param points a vector of points
     * \return pair of closest points
     */
    std::pair<point2d, point2d> find_closest_points(const std::vector<point2d> & points);
}

#endif
