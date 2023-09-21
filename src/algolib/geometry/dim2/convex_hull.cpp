/*!
 * \file convex_hull.cpp
 * \brief Algorithm for convex hull (monotone chain) in 2D
 */
#include "algolib/geometry/dim2/convex_hull.hpp"
#include <algorithm>
#include "algolib/geometry/dim2/geometry_2d.hpp"
#include "algolib/geometry/dim2/vector_2d.hpp"

namespace alge2 = algolib::geometry::dim2;

namespace internal
{
    double cross_product(const alge2::point_2d & pt1,
                         const alge2::point_2d & pt2,
                         const alge2::point_2d & pt3)
    {
        return alge2::vector_2d::area(alge2::vector_2d(pt2, pt1), alge2::vector_2d(pt2, pt3));
    }

    std::vector<alge2::point_2d> create_half_hull(const std::vector<alge2::point_2d> & points)
    {
        std::vector<alge2::point_2d> hull;

        for(auto && pt : points)
        {
            while(hull.size() > 1 && cross_product(*(hull.end() - 2), *(hull.end() - 1), pt) >= 0)
                hull.pop_back();

            hull.push_back(pt);
        }

        return hull;
    }
}

std::vector<alge2::point_2d> alge2::find_convex_hull(std::vector<alge2::point_2d> points)
{
    if(points.size() < 3)
        return std::vector<alge2::point_2d>();

    sort_by_x(points);

    std::vector<alge2::point_2d> lower_hull = internal::create_half_hull(points);

    std::reverse(points.begin(), points.end());

    std::vector<alge2::point_2d> upper_hull = internal::create_half_hull(points);

    lower_hull.pop_back();
    lower_hull.insert(lower_hull.end(), upper_hull.begin(), upper_hull.end() - 1);
    return lower_hull;
}
