// OTOCZKA WYPUKŁA PUNKTÓW NA PŁASZCZYŹNIE
#include "otoczka_wypukla.hpp"

std::vector<point2D> algolib::find_convex_hull(std::vector<point2D> points)
{
    std::vector<point2D> hull;

    auto is_angle_convex = [](const point2D & pt1, const point2D pt2, const point2D pt3)
        {
            return (pt1.first-pt2.first)*(pt3.second-pt2.second)
                -(pt3.first-pt2.first)*(pt1.second-pt2.second) > 0;
        };

    sort(points.begin(), points.end());
    hull.push_back(points[0]);
    hull.push_back(points[1]);

    for(auto it = points.begin()+2; it != points.end(); ++it)
    {
         while( hull.size() > 1
                && !is_angle_convex(*(hull.end()-2), *(hull.end()-1), *it) )
            hull.pop_back();

        hull.push_back(*it);
    }

    size_t upper_size = hull.size();

    for(auto it = points.rbegin()+2; it != points.rend(); ++it)
    {
        while( hull.size() > upper_size
               && !is_angle_convex(*(hull.end()-2), *(hull.end()-1), *it) )
            hull.pop_back();

        hull.push_back(*it);
    }

    hull.pop_back();

    return hull;
}

