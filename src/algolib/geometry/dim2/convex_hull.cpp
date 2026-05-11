/*!
 * \file convex_hull.cpp
 * \brief Algorithm for convex hull in 2D (Graham's scan).
 */
#include "algolib/geometry/dim2/convex_hull.hpp"
#include <algorithm>
#include "algolib/geometry/dim2/geometry_2d.hpp"
#include "algolib/geometry/dim2/vector_2d.hpp"

namespace alge2 = algolib::geometry::dim2;

double cross_product(
        const alge2::point_2d & pt1,
        const alge2::point_2d & pt2,
        const alge2::point_2d & pt3)
{
    return alge2::vector_2d::area(alge2::vector_2d(pt2, pt1), alge2::vector_2d(pt2, pt3));
}

// Collects points of convex hull for given points.
std::vector<alge2::point_2d> collect_hull(const std::vector<alge2::point_2d> & points)
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

std::vector<alge2::point_2d> alge2::find_andrew_convex_hull(std::vector<point_2d> points)
{
    if(points.size() < 3)
        return std::vector<point_2d>();

    sort_by_x(points);

    std::vector<point_2d> lower_hull = collect_hull(points);

    std::reverse(points.begin(), points.end());

    std::vector<point_2d> upper_hull = collect_hull(points);

    lower_hull.pop_back();
    lower_hull.insert(lower_hull.end(), upper_hull.begin(), upper_hull.end() - 1);
    return lower_hull;
}

std::vector<alge2::point_2d> alge2::find_graham_convex_hull(const std::vector<point_2d> & points)
{
    if(points.size() < 3)
        return std::vector<point_2d>();

    point_2d min_point = *std::min_element(
            points.begin(), points.end(), [](const point_2d & p1, const point_2d & p2)
            { return p1.y() == p2.y() ? p1.x() < p2.x() : p1.y() < p2.y(); });
    vector_2d moving(point_2d(0, 0), min_point);
    std::vector<point_2d> angle_points;

    std::transform(
            points.begin(), points.end(), std::back_inserter(angle_points),
            [&](const point_2d & p) { return translate(p, -moving); });

    sort_by_angle(angle_points);

    std::vector<point_2d> hull = collect_hull(angle_points);
    std::vector<point_2d> hull_points;

    std::transform(
            hull.begin(), hull.end(), std::back_inserter(hull_points),
            [&](const point_2d & p) { return translate(p, moving); });

    return hull_points;
}
