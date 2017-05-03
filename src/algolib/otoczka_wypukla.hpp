// OTOCZKA WYPUKŁA PUNKTÓW NA PŁASZCZYŹNIE
#ifndef OTOCZKA_WYPUKLA_HPP
#define OTOCZKA_WYPUKLA_HPP

#include <cstdlib>
#include <vector>
#include <algorithm>

using point2D_type = std::pair<double, double>;

namespace algolib
{
    /**
     * Wyznacza otoczkę wypukłą.
     * @param points lista punktów na płaszczyźnie
     * @return lista punktów otoczki
     */
    std::vector<point2D_type> find_convex_hull(std::vector<point2D_type> points);
}

#endif
