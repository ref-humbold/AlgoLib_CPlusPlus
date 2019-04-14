/**
 * @file convex_hull.hpp
 * @brief Graham's algorithm for convex hull on a plane.
 */
#ifndef _CONVEX_HULL_HPP_
#define _CONVEX_HULL_HPP_

#include <cstdlib>
#include <algorithm>
#include <vector>

using point2D_t = std::pair<double, double>;

namespace algolib
{
    /**
     * Wyznacza otoczkę wypukłą.
     * @param points lista punktów na płaszczyźnie
     * @return lista punktów otoczki
     */
    std::vector<point2D_t> find_convex_hull(std::vector<point2D_t> points);
}

#endif
