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

using point2D_t = std::pair<double, double>;

namespace algolib
{
    /**
     * Funkcja obsługująca do wyszukiwania punktów.
     * @param points lista punktów
     * @return para najbliższych punktów
     */
    std::pair<point2D_t, point2D_t> find_closest_points(const std::vector<point2D_t> & points);
}

#endif
