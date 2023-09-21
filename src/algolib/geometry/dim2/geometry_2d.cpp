/*!
 * \file geometry_2d.cpp
 * \brief Basic geometric operations in 2D
 */
#include "algolib/geometry/dim2/geometry_2d.hpp"

namespace alge2 = algolib::geometry::dim2;

void alge2::sort_by_x(std::vector<alge2::point_2d> & points)
{
    auto comparator = [&](auto && pt1, const alge2::point_2d & pt2) { return pt1.x() < pt2.x(); };

    std::stable_sort(points.begin(), points.end(), comparator);
}

void alge2::sort_by_y(std::vector<alge2::point_2d> & points)
{
    auto comparator = [&](auto && pt1, const alge2::point_2d & pt2) { return pt1.y() < pt2.y(); };

    std::stable_sort(points.begin(), points.end(), comparator);
}

void alge2::sort_by_angle(std::vector<alge2::point_2d> & points)
{
    auto comparator = [&](auto && pt1, const alge2::point_2d & pt2)
    {
        double angle1 = pt1.angle_deg(), angle2 = pt2.angle_deg();

        return angle1 != angle2 ? angle1 < angle2 : pt1.radius() < pt2.radius();
    };

    std::sort(points.begin(), points.end(), comparator);
}

double alge2::distance(const alge2::point_2d & point1, const alge2::point_2d & point2)
{
    return sqrt((point2.x() - point1.x()) * (point2.x() - point1.x())
                + (point2.y() - point1.y()) * (point2.y() - point1.y()));
}

alge2::point_2d alge2::translate(const alge2::point_2d & point, const alge2::vector_2d & vector)
{
    return point_2d(point.x() + vector.x(), point.y() + vector.y());
}

alge2::point_2d alge2::reflect(const alge2::point_2d & point, const alge2::point_2d & centre)
{
    return point_2d(-point.x() + centre.x() + centre.x(), -point.y() + centre.y() + centre.y());
}
