/*!
 * \file closest_points.cpp
 * \brief Algorithm for pair of closest points in 2D
 */
#include "algolib/geometry/dim2/closest_points.hpp"
#include <cmath>
#include <algorithm>
#include <optional>
#include "algolib/geometry/dim2/geometry_2d.hpp"

namespace alge2 = algolib::geometry::dim2;

namespace internal
{
    // Finds closest pair of points among three of them.
    std::pair<alge2::point_2d, alge2::point_2d> search_three(const alge2::point_2d & point1,
                                                             const alge2::point_2d & point2,
                                                             const alge2::point_2d & point3)
    {
        double distance12 = distance(point1, point2);
        double distance23 = distance(point2, point3);
        double distance31 = distance(point3, point1);

        if(distance12 <= distance23 && distance12 <= distance31)
            return std::make_pair(point1, point2);

        if(distance23 <= distance12 && distance23 <= distance31)
            return std::make_pair(point2, point3);

        return std::make_pair(point1, point3);
    }

    // Finds closest pair inside a belt of given width.
    // The resulting distance should not be less than belt width.
    std::optional<std::pair<alge2::point_2d, alge2::point_2d>>
            check_belt(const std::vector<alge2::point_2d> & pointsY, double middleX, double width)
    {
        std::optional<std::pair<alge2::point_2d, alge2::point_2d>> closest_pair = std::nullopt;
        std::vector<int> belt_points;
        double min_distance = width;

        for(size_t i = 0; i < pointsY.size(); ++i)
            if(pointsY[i].x() >= middleX - width && pointsY[i].x() <= middleX + width)
                belt_points.emplace_back(i);

        for(size_t i = 1; i < belt_points.size(); ++i)
            for(size_t j = i + 1; j < belt_points.size(); ++j)
            {
                alge2::point_2d pt1 = pointsY[belt_points[i]];
                alge2::point_2d pt2 = pointsY[belt_points[j]];

                if(pt2.y() > pt1.y() + width)
                    break;

                if((pt1.x() <= middleX && pt2.x() >= middleX)
                   || (pt1.x() > middleX && pt2.x() <= middleX))
                {
                    double actual_distance = distance(pt1, pt2);

                    if(actual_distance < min_distance)
                    {
                        std::vector<alge2::point_2d> closest = {pt1, pt2};

                        alge2::sort_by_x(closest);
                        min_distance = actual_distance;
                        closest_pair = std::make_optional(std::make_pair(closest[0], closest[1]));
                    }
                }
            }

        return closest_pair;
    }

    // Searches for a pair of closest points in given sublist of points.
    // Points are given sorted by X coordinate and by Y coordinate.
    std::pair<alge2::point_2d, alge2::point_2d>
            search_closest(std::vector<alge2::point_2d>::const_iterator pointsX_begin,
                           std::vector<alge2::point_2d>::const_iterator pointsX_end,
                           const std::vector<alge2::point_2d> & pointsY)
    {
        std::ptrdiff_t diff = pointsX_end - pointsX_begin;

        if(diff <= 2)
            return std::make_pair(*pointsX_begin, *(pointsX_end - 1));

        if(diff == 3)
            return search_three(*pointsX_begin, *(pointsX_begin + 1), *(pointsX_begin + 2));

        std::vector<alge2::point_2d>::const_iterator pointsX_middle = pointsX_begin + diff / 2;
        std::vector<alge2::point_2d> pointsYL, pointsYR;

        for(auto & pt : pointsY)
            if(pt.x() < pointsX_middle->x()
               || (pt.x() == pointsX_middle->x() && pt.y() < pointsX_middle->y()))
                pointsYL.push_back(pt);
            else
                pointsYR.push_back(pt);

        std::pair<alge2::point_2d, alge2::point_2d> closestL =
                search_closest(pointsX_begin, pointsX_middle, pointsYL);
        std::pair<alge2::point_2d, alge2::point_2d> closestR =
                search_closest(pointsX_middle, pointsX_end, pointsYR);
        std::pair<alge2::point_2d, alge2::point_2d> closest_pair =
                distance(closestL.first, closestL.second)
                                <= distance(closestR.first, closestR.second)
                        ? closestL
                        : closestR;
        std::optional<std::pair<alge2::point_2d, alge2::point_2d>> belt_pair = check_belt(
                pointsY, pointsX_middle->x(), distance(closest_pair.first, closest_pair.second));

        return belt_pair.value_or(closest_pair);
    }
}

std::pair<alge2::point_2d, alge2::point_2d>
        alge2::find_closest_points(const std::vector<alge2::point_2d> & points)
{
    std::vector<point_2d> pointsX = points;
    std::vector<point_2d> pointsY = points;

    sort_by_y(pointsX);
    sort_by_x(pointsX);
    sort_by_y(pointsY);
    return internal::search_closest(pointsX.cbegin(), pointsX.cend(), pointsY);
}
