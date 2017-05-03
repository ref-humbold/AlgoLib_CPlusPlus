// ALGORYTM WYZNACZANIA NAJBLIŻSZEJ PARY PUNKTÓW NA PŁASZCZYŹNIE
#ifndef NAJBLIZSZE_PUNKTY_HPP
#define NAJBLIZSZE_PUNKTY_HPP

#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>

using point2D_type = std::pair<double, double>;

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
    std::pair<point2D_type, point2D_type> search_closest(std::vector<point2D_type> & pointsX,
        std::vector< std::pair<point2D_type, int> > & pointsY, int index_begin=0, int index_end=-1);
}

namespace algolib
{
    /**
     * Funkcja obsługująca do wyszukiwania punktów.
     * @param points lista punktów
     * @return para najbliższych punktów
     */
    std::pair<point2D_type, point2D_type> find_closest_points(const std::vector<point2D_type> & points);
}

#endif

