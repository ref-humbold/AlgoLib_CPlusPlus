/*!
 * \file geometry.cpp
 * \brief Basic geometric operations in 3D
 */
#include "algolib/geometry/dim3/geometry_3d.hpp"

namespace alge3 = algolib::geometry::dim3;

void alge3::sort_by_x(std::vector<alge3::point_3d> & points)
{
    auto comparator = [&](const point_3d & pt1, const point_3d & pt2) { return pt1.x() < pt2.x(); };

    std::stable_sort(points.begin(), points.end(), comparator);
}

void alge3::sort_by_y(std::vector<alge3::point_3d> & points)
{
    auto comparator = [&](const point_3d & pt1, const point_3d & pt2) { return pt1.y() < pt2.y(); };

    std::stable_sort(points.begin(), points.end(), comparator);
}

void alge3::sort_by_z(std::vector<alge3::point_3d> & points)
{
    auto comparator = [&](const point_3d & pt1, const point_3d & pt2) { return pt1.z() < pt2.z(); };

    std::stable_sort(points.begin(), points.end(), comparator);
}

double alge3::distance(const alge3::point_3d & p1, const alge3::point_3d & p2)
{
    return sqrt((p2.x() - p1.x()) * (p2.x() - p1.x()) + (p2.y() - p1.y()) * (p2.y() - p1.y())
                + (p2.z() - p1.z()) * (p2.z() - p1.z()));
}

alge3::point_3d alge3::translate(const alge3::point_3d & p, const alge3::vector_3d & v)
{
    return point_3d(p.x() + v.x(), p.y() + v.y(), p.z() + v.z());
}
