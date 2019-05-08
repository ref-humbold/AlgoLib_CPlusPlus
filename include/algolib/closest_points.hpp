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

namespace detail
{
    /**
     * Znajdowanie najbliższej pary punktów.
     * @param points_X lista punktów posortowana po współrzędnej x
     * @param points_Y lista punktów posortowana po współrzędnej y
     * @param index_begin początek fragmentu listy punktów po x
     * @param index_end koniec fragmentu listy punktów po x
     * @return para najbliższych punktów
     */
    std::pair<point2D_t, point2D_t> search_closest(std::vector<point2D_t> & pointsX,
                                                   std::vector<std::pair<point2D_t, int>> & pointsY,
                                                   int index_begin = 0, int index_end = -1);
}

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
