// ALGORYTM WYZNACZANIA NAJBLIŻSZEJ PARY PUNKTÓW NA PŁASZCZYŹNIE
#include "najblizsze_punkty.hpp"

std::pair<point2D_type, point2D_type> detail::search_closest(std::vector<point2D_type> & pointsX,
    std::vector< std::pair<point2D_type, int> > & pointsY, int index_begin, int index_end)
{
    index_begin = (index_begin+pointsX.size())%pointsX.size();
    index_end = (index_end+pointsX.size())%pointsX.size();

    auto distance = [](const point2D_type & pt1, const point2D_type & pt2)
        {
            double dx = pt1.first-pt2.first, dy = pt1.second-pt2.second;

            return dx*dx+dy*dy;
        };

    if(index_end-index_begin == 1)
        return std::make_pair(pointsX[index_begin], pointsX[index_end]);

    if(index_end-index_begin == 2)
    {
        int index_middle = index_begin+1;
        double distance12, distance23, distance31;

        distance12 = distance(pointsX[index_begin], pointsX[index_middle]);
        distance23 = distance(pointsX[index_middle], pointsX[index_end]);
        distance31 = distance(pointsX[index_begin], pointsX[index_end]);

        if(distance12 <= distance23 && distance12 <= distance31)
            return std::make_pair(pointsX[index_begin], pointsX[index_middle]);
        else if(distance23 <= distance12 && distance23 <= distance31)
            return std::make_pair(pointsX[index_middle], pointsX[index_end]);
        else
            return std::make_pair(pointsX[index_begin], pointsX[index_end]);
    }

    int index_middle = (index_begin+index_end)/2;
    double middleX = (pointsX[index_middle].first+pointsX[index_middle+1].first)/2;
    std::vector< std::pair<point2D_type, int> > pointsYL, pointsYR;
    std::vector< std::pair<int, bool> > belt_points;

    for(size_t i = 0; i < pointsY.size(); ++i)
        if(pointsY[i].second <= index_middle)
            pointsYL.push_back(pointsY[i]);
        else
            pointsYR.push_back(pointsY[i]);

    std::pair<point2D_type, point2D_type> closest_points;
    std::pair<point2D_type, point2D_type> closestL =
        search_closest(pointsX, pointsYL, index_begin, index_middle);
    std::pair<point2D_type, point2D_type> closestR =
        search_closest(pointsX, pointsYR, index_middle+1, index_end);

    double min_distance = std::min(distance(closestL.first, closestL.second),
        distance(closestR.first, closestR.second));
    double belt_width = min_distance;

    for(size_t i = 0; i < pointsY.size(); ++i)
        if(pointsY[i].first.first >= middleX-belt_width && pointsY[i].first.first <= middleX+belt_width)
            belt_points.push_back(std::make_pair(i, pointsY[i].second <= index_middle));

    for(size_t i = 1; i < belt_points.size(); ++i)
        for(int j = i-1; j >= 0; --j)
            if(belt_points[i].second != belt_points[j].second)
            {
                point2D_type pt1 = pointsY[belt_points[i].first].first;
                point2D_type pt2 = pointsY[belt_points[j].first].first;

                if(pt1.second <= pt2.second+belt_width)
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

std::pair<point2D_type, point2D_type> algolib::find_closest_points(const std::vector<point2D_type> & points)
{
    std::vector<point2D_type> pointsX = points;
    std::vector< std::pair<point2D_type, int> > pointsY;

    std::sort(pointsX.begin(), pointsX.end());

    for(size_t i = 0; i < pointsX.size(); ++i)
        pointsY.push_back(std::make_pair(
            std::make_pair(pointsY[i].first.second, pointsY[i].first.first), i));

    std::sort(pointsY.rbegin(), pointsY.rend());

    for(size_t i = 0; i < pointsY.size(); ++i)
        std::swap(pointsY[i].first.first, pointsY[i].first.second);

    return detail::search_closest(pointsX, pointsY);
}

