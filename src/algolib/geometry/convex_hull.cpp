/*!
 * \file convex_hull.cpp
 * \brief Algorithm for convex hull on a plane (monotone chain)
 */
#include "algolib/geometry/convex_hull.hpp"
#include <algorithm>
#include "algolib/geometry/geometry.hpp"
#include "algolib/geometry/points_sorting.hpp"

namespace alge = algolib::geometry;

namespace
{
    double cross_product(const alge::point2d & pt1, const alge::point2d & pt2,
                         const alge::point2d & pt3)
    {
        return alge::vector2d::area(alge::make_vector(pt2, pt1), alge::make_vector(pt2, pt3));
    }

    std::vector<alge::point2d> create_half_hull(const std::vector<alge::point2d> & points)
    {
        std::vector<alge::point2d> hull;

        for(auto && pt : points)
        {
            while(hull.size() > 1 && cross_product(*(hull.end() - 2), *(hull.end() - 1), pt) >= 0)
                hull.pop_back();

            hull.push_back(pt);
        }

        return hull;
    }
}

std::vector<alge::point2d> alge::find_convex_hull(std::vector<alge::point2d> points)
{
    if(points.size() < 3)
        return std::vector<alge::point2d>();

    sort_by_x(points);

    std::vector<alge::point2d> lower_hull = create_half_hull(points);

    std::reverse(points.begin(), points.end());

    std::vector<alge::point2d> upper_hull = create_half_hull(points);

    lower_hull.pop_back();
    lower_hull.insert(lower_hull.end(), upper_hull.begin(), upper_hull.end() - 1);
    return lower_hull;
}
