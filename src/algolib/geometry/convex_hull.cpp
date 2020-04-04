/*!
 * \file convex_hull.cpp
 * \brief Algorithm for convex hull on a plane (monotone chain)
 */
#include "algolib/geometry/convex_hull.hpp"

namespace alge = algolib::geometry;

namespace
{
    double cross_product(const alge::point2d & pt1, const alge::point2d & pt2,
                         const alge::point2d & pt3)
    {
        return (pt1.x() - pt2.x()) * (pt3.y() - pt2.y())
               - (pt3.x() - pt2.x()) * (pt1.y() - pt2.y());
    }

    void add_point(const alge::point2d & point, std::vector<alge::point2d> & hull, size_t min_size)
    {
        while(hull.size() > min_size
              && cross_product(*(hull.end() - 2), *(hull.end() - 1), point) <= 0)
            hull.pop_back();

        hull.push_back(point);
    }
}

std::vector<alge::point2d> alge::find_convex_hull(std::vector<alge::point2d> points)
{
    std::vector<alge::point2d> hull;

    sort_by_x(points);
    hull.push_back(points[0]);
    hull.push_back(points[1]);

    for(auto it = points.begin() + 2; it != points.end(); ++it)
        add_point(*it, hull, 1);

    size_t upper_size = hull.size();

    for(auto it = points.rbegin() + 1; it != points.rend(); ++it)
        add_point(*it, hull, upper_size);

    hull.pop_back();

    return hull;
}
