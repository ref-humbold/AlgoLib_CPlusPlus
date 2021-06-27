/*!
 * \file geometry.cpp
 * \brief Basic geometric operations in 3D
 */
#include "algolib/geometry/dim3/geometry_3d.hpp"

namespace alges = algolib::geometry::space;

void alges::sort_by_x(std::vector<alges::point_3d> & points)
{
    auto comparator = [&](const point_3d & pt1, const point_3d & pt2) { return pt1.x() < pt2.x(); };

    std::stable_sort(points.begin(), points.end(), comparator);
}

void alges::sort_by_y(std::vector<alges::point_3d> & points)
{
    auto comparator = [&](const point_3d & pt1, const point_3d & pt2) { return pt1.y() < pt2.y(); };

    std::stable_sort(points.begin(), points.end(), comparator);
}

void alges::sort_by_z(std::vector<alges::point_3d> & points)
{
    auto comparator = [&](const point_3d & pt1, const point_3d & pt2) { return pt1.z() < pt2.z(); };

    std::stable_sort(points.begin(), points.end(), comparator);
}

double alges::distance(const alges::point_3d & p1, const alges::point_3d & p2)
{
    return sqrt((p2.x() - p1.x()) * (p2.x() - p1.x()) + (p2.y() - p1.y()) * (p2.y() - p1.y())
                + (p2.z() - p1.z()) * (p2.z() - p1.z()));
}

alges::point_3d alges::translate(const alges::point_3d & p, const alges::vector_3d & v)
{
    return point_3d(p.x() + v.x(), p.y() + v.y(), p.z() + v.z());
}
