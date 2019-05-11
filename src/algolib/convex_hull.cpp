// Graham's algorithm for convex hull on a plane.
#include "algolib/convex_hull.hpp"

std::vector<point2D_t> algolib::find_convex_hull(std::vector<point2D_t> points)
{
    std::vector<point2D_t> hull;

    auto cross_product = [](const point2D_t & pt1, const point2D_t & pt2, const point2D_t & pt3) {
        return (pt1.first - pt2.first) * (pt3.second - pt2.second)
               - (pt3.first - pt2.first) * (pt1.second - pt2.second);
    };

    sort(points.begin(), points.end());
    hull.push_back(points[0]);
    hull.push_back(points[1]);

    for(auto it = points.begin() + 2; it != points.end(); ++it)
    {
        while(hull.size() > 1 && cross_product(*(hull.end() - 2), *(hull.end() - 1), *it) <= 0)
            hull.pop_back();

        hull.push_back(*it);
    }

    size_t upper_size = hull.size();

    for(auto it = points.rbegin() + 1; it != points.rend(); ++it)
    {
        while(hull.size() > upper_size
              && cross_product(*(hull.end() - 2), *(hull.end() - 1), *it) <= 0)
            hull.pop_back();

        hull.push_back(*it);
    }

    hull.pop_back();

    return hull;
}
