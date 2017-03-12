// ALGORYTM WYZNACZANIA NAJBLIŻSZEJ PARY PUNKTÓW NA PŁASZCZYŹNIE
#ifndef NAJBLIZSZE_PUNKTY_HPP
#define NAJBLIZSZE_PUNKTY_HPP

#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>

using point2D = std::pair<double, double>;

namespace algolib
{
    namespace detail
    {
        /**
        ZNAJDOWANIE NAJBLIŻSZEJ PARY PUNKTÓW
        @param points_X lista punktów posortowana po współrzędnej x
        @param points_Y lista punktów posortowana po współrzędnej y
        @param index_begin początek fragmentu listy punktów po x
        @param index_end koniec fragmentu listy punktów po x
        @return para najbliższych punktów
        */
        std::pair<point2D, point2D> search_closest(std::vector<point2D> & pointsX,
            std::vector< std::pair<point2D, int> > & pointsY, int index_begin=0, int index_end=-1);
    }

    /**
    FUNKCJA OBSŁUGUJĄCA DO WYSZUKIWANIA PUNKTÓW
    @param points lista punktów
    @return para najbliższych punktów
    */
    std::pair<point2D, point2D> find_closest_points(const std::vector<point2D> & points);
}

#endif

