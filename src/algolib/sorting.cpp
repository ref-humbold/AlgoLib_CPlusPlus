// ALGORYTMY SORTOWANIA
#include "sorting.hpp"

int detail::choose_pivot(int size)
{
    srand(time(0));

    int candidate1 = rand() % size, candidate2 = rand() % size, candidate3 = rand() % size;

    if(std::min(candidate2, candidate3) <= candidate1
       && candidate1 <= std::max(candidate2, candidate3))
        return candidate2;
    else if(std::min(candidate1, candidate3) <= candidate2
            && candidate2 <= std::max(candidate1, candidate3))
        return candidate2;
    else
        return candidate3;
}

void algolib::angle_sort(std::vector<point2D_t> & points)
{
    auto angle = [](const point2D_t & pt) {
        double ang = atan2(pt.second, pt.first) * 180.0 / M_PI;

        return pt.second >= 0.0 ? ang : ang + 360.0;
    };

    auto radius = [](const point2D_t & pt) { return pt.first * pt.first + pt.second * pt.second; };

    auto comparator = [&](const point2D_t & pt1, const point2D_t & pt2) -> bool {
        double angle1 = angle(pt1), angle2 = angle(pt2);

        return angle1 != angle2 ? angle1 < angle2 : radius(pt1) <= radius(pt2);
    };

    std::sort(points.begin(), points.end(), comparator);
}

std::vector<point2D_t> algolib::angle_sorted(std::vector<point2D_t> points)
{
    angle_sort(points);

    return points;
}
