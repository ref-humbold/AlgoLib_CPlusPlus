/**
 * @file convex_hull.hpp
 * @brief Graham's algorithm for convex hull on a plane.
 */
#ifndef CONVEX_HULL_HPP_
#define CONVEX_HULL_HPP_

#include <cstdlib>
#include <algorithm>
#include <vector>
#include "points_sorting.hpp"

namespace algolib
{
    namespace geometry
    {
        /**
         * Wyznacza otoczkę wypukłą.
         * @param points lista punktów na płaszczyźnie
         * @return lista punktów otoczki
         */
        std::vector<point2d> find_convex_hull(std::vector<point2d> points);
    }
}

#endif
