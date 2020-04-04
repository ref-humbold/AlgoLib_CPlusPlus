/*!
 * \file closest_points.hpp
 * \brief Algorithm for pair of closest points on a plane
 */
#ifndef CLOSEST_POINTS_HPP_
#define CLOSEST_POINTS_HPP_

#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include "points_sorting.hpp"

namespace algolib
{
    namespace geometry
    {
        /*!
         * \brief Searches for closest points among specified points.
         *
         * \param points a vector of points
         * \return pair of closest points
         */
        std::pair<point2d, point2d> find_closest_points(const std::vector<point2d> & points);
    }
}

#endif
