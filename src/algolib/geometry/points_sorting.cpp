#include "algolib/geometry/points_sorting.hpp"

namespace alge = algolib::geometry;

void alge::angle_sort(std::vector<alge::point2d> & points)
{
    auto comparator = [&](const alge::point2d & pt1, const alge::point2d & pt2) -> bool {
        double angle1 = pt1.angle(), angle2 = pt2.angle();

        return angle1 != angle2 ? angle1 < angle2 : pt1.radius() < pt2.radius();
    };

    std::sort(points.begin(), points.end(), comparator);
}
