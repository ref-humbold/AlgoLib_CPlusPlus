/*!
 * \file convex_hull.cpp
 * \brief Algorithm for convex hull (monotone chain) in 2D
 */
#include "algolib/geometry/2d/convex_hull.hpp"
#include <algorithm>
#include "algolib/geometry/2d/geometry_2d.hpp"
#include "algolib/geometry/2d/vector_2d.hpp"

namespace algep = algolib::geometry::plane;

namespace internal
{
    double cross_product(const algep::point_2d & pt1, const algep::point_2d & pt2,
                         const algep::point_2d & pt3)
    {
        return algep::vector_2d::area(algep::vector_2d::between(pt2, pt1),
                                      algep::vector_2d::between(pt2, pt3));
    }

    std::vector<algep::point_2d> create_half_hull(const std::vector<algep::point_2d> & points)
    {
        std::vector<algep::point_2d> hull;

        for(auto && pt : points)
        {
            while(hull.size() > 1 && cross_product(*(hull.end() - 2), *(hull.end() - 1), pt) >= 0)
                hull.pop_back();

            hull.push_back(pt);
        }

        return hull;
    }
}

std::vector<algep::point_2d> algep::find_convex_hull(std::vector<algep::point_2d> points)
{
    if(points.size() < 3)
        return std::vector<algep::point_2d>();

    sort_by_x(points);

    std::vector<algep::point_2d> lower_hull = internal::create_half_hull(points);

    std::reverse(points.begin(), points.end());

    std::vector<algep::point_2d> upper_hull = internal::create_half_hull(points);

    lower_hull.pop_back();
    lower_hull.insert(lower_hull.end(), upper_hull.begin(), upper_hull.end() - 1);
    return lower_hull;
}
