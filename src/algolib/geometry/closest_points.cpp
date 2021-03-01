/*!
 * \file closest_points.cpp
 * \brief Algorithm for pair of closest points on a plane
 */
#include "algolib/geometry/closest_points.hpp"
#include <cmath>
#include <algorithm>
#include <memory>
#include "algolib/geometry/geometry.hpp"
#include "algolib/geometry/points_sorting.hpp"

namespace alge = algolib::geometry;

namespace
{
    // Finds closest pair of points among three of them.
    std::pair<alge::point2d, alge::point2d> search_three(const std::vector<alge::point2d> & pointsX,
                                                         int index_begin, int index_end)
    {
        int index_middle = index_begin + 1;
        double distance12 = distance(pointsX[index_begin], pointsX[index_middle]);
        double distance23 = distance(pointsX[index_middle], pointsX[index_end]);
        double distance31 = distance(pointsX[index_begin], pointsX[index_end]);

        if(distance12 <= distance23 && distance12 <= distance31)
            return std::make_pair(pointsX[index_begin], pointsX[index_middle]);

        if(distance23 <= distance12 && distance23 <= distance31)
            return std::make_pair(pointsX[index_middle], pointsX[index_end]);

        return std::make_pair(pointsX[index_begin], pointsX[index_end]);
    }

    // Finds closest pair inside a belt of specified width.
    // The resulting distance should not be less than belt width.
    std::unique_ptr<std::pair<alge::point2d, alge::point2d>>
            check_belt(const std::vector<alge::point2d> & pointsY, double middleX,
                       double belt_width)
    {
        std::unique_ptr<std::pair<alge::point2d, alge::point2d>> closest_pair;
        std::vector<int> belt_points;
        double min_distance = belt_width;

        for(size_t i = 0; i < pointsY.size(); ++i)
            if(pointsY[i].x() >= middleX - belt_width && pointsY[i].x() <= middleX + belt_width)
                belt_points.emplace_back(i);

        for(size_t i = 1; i < belt_points.size(); ++i)
            for(size_t j = i + 1; j < belt_points.size(); ++j)
            {
                alge::point2d pt1 = pointsY[belt_points[i]];
                alge::point2d pt2 = pointsY[belt_points[j]];

                if(pt2.y() > pt1.y() + belt_width)
                    break;

                if((pt1.x() <= middleX && pt2.x() > middleX)
                   || (pt1.x() > middleX && pt2.x() <= middleX))
                {
                    double actual_distance = distance(pt1, pt2);

                    if(actual_distance < min_distance)
                    {
                        std::vector<alge::point2d> closest = {pt1, pt2};

                        alge::sort_by_x(closest);
                        min_distance = actual_distance;
                        closest_pair.reset(new std::pair<alge::point2d, alge::point2d>(closest[0],
                                                                                       closest[1]));
                    }
                }
            }

        return closest_pair;
    }

    // Searches for a pair of closest points in specified sublist of points.
    // Points are specified sorted by X coordinate and by Y coordinate.
    // (index_begin & index_end inclusive)
    std::pair<alge::point2d, alge::point2d>
            search_closest(const std::vector<alge::point2d> & pointsX,
                           const std::vector<alge::point2d> & pointsY, int index_begin = 0,
                           int index_end = -1)
    {
        index_begin = (index_begin + pointsX.size()) % pointsX.size();
        index_end = (index_end + pointsX.size()) % pointsX.size();

        if(index_end - index_begin <= 1)
            return std::make_pair(pointsX[index_begin], pointsX[index_end]);

        if(index_end - index_begin == 2)
            return search_three(pointsX, index_begin, index_end);

        int index_middle = (index_begin + index_end) / 2;
        double middleX = (pointsX[index_middle].x() + pointsX[index_middle + 1].x()) / 2;
        std::vector<alge::point2d> pointsYL, pointsYR;

        for(auto & pt : pointsY)
            if(pt.x() <= index_middle)
                pointsYL.push_back(pt);
            else
                pointsYR.push_back(pt);

        std::pair<alge::point2d, alge::point2d> closestL =
                search_closest(pointsX, pointsYL, index_begin, index_middle);
        std::pair<alge::point2d, alge::point2d> closestR =
                search_closest(pointsX, pointsYR, index_middle + 1, index_end);
        std::pair<alge::point2d, alge::point2d> closest_pair =
                distance(closestL.first, closestL.second)
                                <= distance(closestR.first, closestR.second)
                        ? closestL
                        : closestR;
        std::unique_ptr<std::pair<alge::point2d, alge::point2d>> belt_pair =
                check_belt(pointsY, middleX, distance(closest_pair.first, closest_pair.second));

        return belt_pair ? *belt_pair : closest_pair;
    }
}

std::pair<alge::point2d, alge::point2d>
        alge::find_closest_points(const std::vector<alge::point2d> & points)
{
    std::vector<alge::point2d> pointsX = points;
    std::vector<alge::point2d> pointsY = points;

    alge::sort_by_x(pointsX);
    alge::sort_by_y(pointsY);
    return search_closest(pointsX, pointsY);
}
