/**
 * @file closest_points.hpp
 * @brief Algorithm for closest pair of points on a plane.
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
        /**
         * Funkcja obsługująca do wyszukiwania punktów.
         * @param points lista punktów
         * @return para najbliższych punktów
         */
        std::pair<point2d, point2d> find_closest_points(const std::vector<point2d> & points);
    }
}

#endif
