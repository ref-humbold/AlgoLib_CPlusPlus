/*!
 * \file points_sorting.cpp
 * \brief Algorithms for points sorting
 */
#include "algolib/geometry/points_sorting.hpp"

namespace alge = algolib::geometry;

void alge::sort_by_x(std::vector<algolib::geometry::point2d> & points)
{
    auto comparator = [&](const alge::point2d & pt1, const alge::point2d & pt2) {
        return pt1.x() < pt2.x();
    };

    std::stable_sort(points.begin(), points.end(), comparator);
}

void alge::sort_by_x(std::vector<algolib::geometry::point3d> & points)
{
    auto comparator = [&](const alge::point3d & pt1, const alge::point3d & pt2) {
        return pt1.x() < pt2.x();
    };

    std::stable_sort(points.begin(), points.end(), comparator);
}

void alge::sort_by_y(std::vector<alge::point2d> & points)
{
    auto comparator = [&](const alge::point2d & pt1, const alge::point2d & pt2) {
        return pt1.y() < pt2.y();
    };

    std::stable_sort(points.begin(), points.end(), comparator);
}

void alge::sort_by_y(std::vector<alge::point3d> & points)
{
    auto comparator = [&](const alge::point3d & pt1, const alge::point3d & pt2) {
        return pt1.y() < pt2.y();
    };

    std::stable_sort(points.begin(), points.end(), comparator);
}

void alge::sort_by_z(std::vector<alge::point3d> & points)
{
    auto comparator = [&](const alge::point3d & pt1, const alge::point3d & pt2) {
        return pt1.z() < pt2.z();
    };

    std::stable_sort(points.begin(), points.end(), comparator);
}

void alge::sort_by_angle(std::vector<alge::point2d> & points)
{
    auto comparator = [&](const alge::point2d & pt1, const alge::point2d & pt2) {
        double angle1 = pt1.angle_deg(), angle2 = pt2.angle_deg();

        return angle1 != angle2 ? angle1 < angle2 : pt1.radius() < pt2.radius();
    };

    std::sort(points.begin(), points.end(), comparator);
}
