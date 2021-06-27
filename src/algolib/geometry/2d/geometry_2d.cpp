/*!
 * \file geometry_2d.cpp
 * \brief Basic geometric operations in 2D
 */
#include "algolib/geometry/2d/geometry_2d.hpp"

namespace algep = algolib::geometry::plane;

void algep::sort_by_x(std::vector<algep::point_2d> & points)
{
    auto comparator = [&](const algep::point_2d & pt1, const algep::point_2d & pt2) {
        return pt1.x() < pt2.x();
    };

    std::stable_sort(points.begin(), points.end(), comparator);
}

void algep::sort_by_y(std::vector<algep::point_2d> & points)
{
    auto comparator = [&](const algep::point_2d & pt1, const algep::point_2d & pt2) {
        return pt1.y() < pt2.y();
    };

    std::stable_sort(points.begin(), points.end(), comparator);
}

void algep::sort_by_angle(std::vector<algep::point_2d> & points)
{
    auto comparator = [&](const algep::point_2d & pt1, const algep::point_2d & pt2) {
        double angle1 = pt1.angle_deg(), angle2 = pt2.angle_deg();

        return angle1 != angle2 ? angle1 < angle2 : pt1.radius() < pt2.radius();
    };

    std::sort(points.begin(), points.end(), comparator);
}

double algep::distance(const algep::point_2d & p1, const algep::point_2d & p2)
{
    return sqrt((p2.x() - p1.x()) * (p2.x() - p1.x()) + (p2.y() - p1.y()) * (p2.y() - p1.y()));
}

algep::point_2d algep::translate(const algep::point_2d & p, const algep::vector_2d & v)
{
    return point_2d(p.x() + v.x(), p.y() + v.y());
}
