// OTOCZKA WYPUKŁA PUNKTÓW NA PŁASZCZYŹNIE
#ifndef OTOCZKA_WYPUKLA_HPP
#define OTOCZKA_WYPUKLA_HPP

#include <cstdlib>
#include <vector>
#include <algorithm>

using point2D_t = std::pair<double, double>;

namespace algolib
{
    /**
    WYZNACZA OTOCZKĘ WYPUKŁĄ
    @param points lista punktów na płaszczyźnie
    @return lista punktów otoczki
    */
    std::vector<point2D_t> find_convex_hull(std::vector<point2D_t> points);
}

#endif
