// Algorithm for closest pair of points on a plane.
#include "algolib/geometry/closest_points.hpp"

namespace alge = algolib::geometry;

namespace
{
    double distance(const alge::point2d & pt1, const alge::point2d & pt2)
    {
        double dx = pt1.x() - pt2.x(), dy = pt1.y() - pt2.y();

        return dx * dx + dy * dy;
    }

    std::pair<alge::point2d, alge::point2d> search_three(const std::vector<alge::point2d> & pointsX,
                                                         int index_begin, int index_end)
    {
        int index_middle = index_begin + 1;
        double distance12, distance23, distance31;

        distance12 = distance(pointsX[index_begin], pointsX[index_middle]);
        distance23 = distance(pointsX[index_middle], pointsX[index_end]);
        distance31 = distance(pointsX[index_begin], pointsX[index_end]);

        if(distance12 <= distance23 && distance12 <= distance31)
            return std::make_pair(pointsX[index_begin], pointsX[index_middle]);

        if(distance23 <= distance12 && distance23 <= distance31)
            return std::make_pair(pointsX[index_middle], pointsX[index_end]);

        return std::make_pair(pointsX[index_begin], pointsX[index_end]);
    }

    std::pair<alge::point2d, alge::point2d>
            search_closest(const std::vector<alge::point2d> & pointsX,
                           const std::vector<alge::point2d> & pointsY, int index_begin = 0,
                           int index_end = -1)
    {
        index_begin = (index_begin + pointsX.size()) % pointsX.size();
        index_end = (index_end + pointsX.size()) % pointsX.size();

        if(index_end - index_begin == 1)
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
        double min_distance = std::min(distance(closestL.first, closestL.second),
                                       distance(closestR.first, closestR.second));
        std::pair<alge::point2d, alge::point2d> closest_points =
                distance(closestL.first, closestL.second)
                                <= distance(closestR.first, closestR.second)
                        ? closestL
                        : closestR;
        double middle_width = min_distance;
        std::vector<std::pair<int, bool>> middle_points;

        for(size_t i = 0; i < pointsY.size(); ++i)
            if(pointsY[i].x() >= middleX - middle_width && pointsY[i].x() <= middleX + middle_width)
                middle_points.emplace_back(i, pointsY[i].x() <= middleX);

        for(size_t i = 1; i < middle_points.size(); ++i)
            for(int j = i - 1; j >= 0; --j)
                if(middle_points[i].second != middle_points[j].second)
                {
                    alge::point2d pt1 = pointsY[middle_points[i].first];
                    alge::point2d pt2 = pointsY[middle_points[j].first];

                    if(pt1.y() <= pt2.y() + middle_width)
                        break;

                    double actual_distance = distance(pt1, pt2);

                    if(actual_distance < min_distance)
                    {
                        min_distance = actual_distance;
                        closest_points = std::make_pair(pt1, pt2);
                    }
                }

        return closest_points;
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
