/*!
 * \file geometry.cpp
 * \brief Algorithms for basic geometrical operations in 3D.
 */
#include "algolib/geometry/dim3/geometry_3d.hpp"

namespace alge3 = algolib::geometry::dim3;

void alge3::sort_by_x(std::vector<alge3::point_3d> & points)
{
    auto comparator = [&](auto && pt1, const point_3d & pt2) { return pt1.x() < pt2.x(); };

    std::stable_sort(points.begin(), points.end(), comparator);
}

void alge3::sort_by_y(std::vector<alge3::point_3d> & points)
{
    auto comparator = [&](auto && pt1, const point_3d & pt2) { return pt1.y() < pt2.y(); };

    std::stable_sort(points.begin(), points.end(), comparator);
}

void alge3::sort_by_z(std::vector<alge3::point_3d> & points)
{
    auto comparator = [&](auto && pt1, const point_3d & pt2) { return pt1.z() < pt2.z(); };

    std::stable_sort(points.begin(), points.end(), comparator);
}

double alge3::distance(const alge3::point_3d & point1, const alge3::point_3d & point2)
{
    return sqrt((point2.x() - point1.x()) * (point2.x() - point1.x())
                + (point2.y() - point1.y()) * (point2.y() - point1.y())
                + (point2.z() - point1.z()) * (point2.z() - point1.z()));
}

alge3::point_3d alge3::translate(const alge3::point_3d & point, const alge3::vector_3d & vector)
{
    return point_3d(point.x() + vector.x(), point.y() + vector.y(), point.z() + vector.z());
}

alge3::point_3d alge3::reflect(const alge3::point_3d & point, const alge3::point_3d & centre)
{
    return point_3d(-point.x() + centre.x() + centre.x(), -point.y() + centre.y() + centre.y(),
            -point.z() + centre.z() + centre.z());
}
