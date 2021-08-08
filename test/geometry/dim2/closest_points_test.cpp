/*!
 * \file closest_points_test.cpp
 * \brief Tests: Algorithm for pair of closest points in 2D
 */
#include <gtest/gtest.h>
#include "algolib/geometry/dim2/closest_points.hpp"

namespace alge2 = algolib::geometry::dim2;

TEST(ClosestPointsTest, findClosestPoints_WhenOnePoint_ThenThisPoint)
{
    // when
    std::pair<alge2::point_2d, alge2::point_2d> result =
            alge2::find_closest_points({alge2::point_2d(2, 2)});
    // then
    EXPECT_EQ(std::make_pair(alge2::point_2d(2, 2), alge2::point_2d(2, 2)), result);
}

TEST(ClosestPointsTest, findClosestPoints_WhenTwoPoints_ThenThesePoints)
{
    // when
    std::pair<alge2::point_2d, alge2::point_2d> result =
            alge2::find_closest_points({alge2::point_2d(2, 2), alge2::point_2d(4, 4)});
    // then
    EXPECT_EQ(std::make_pair(alge2::point_2d(2, 2), alge2::point_2d(4, 4)), result);
}

TEST(ClosestPointsTest, findClosestPoints_WhenThreePoints_ThenPairOfClosestPoints)
{
    // when
    std::pair<alge2::point_2d, alge2::point_2d> result = alge2::find_closest_points(
            {alge2::point_2d(3, 2), alge2::point_2d(1, 1), alge2::point_2d(7, 0)});
    // then
    EXPECT_EQ(std::make_pair(alge2::point_2d(1, 1), alge2::point_2d(3, 2)), result);
}

TEST(ClosestPointsTest, findClosestPoints_WhenMultiplePoints_ThenPairOfClosestPoints)
{
    // when
    std::pair<alge2::point_2d, alge2::point_2d> result = alge2::find_closest_points(
            {alge2::point_2d(1, 1), alge2::point_2d(-2, 2), alge2::point_2d(-4, 4),
             alge2::point_2d(3, -3), alge2::point_2d(0, -5), alge2::point_2d(1, 0),
             alge2::point_2d(-7, 2), alge2::point_2d(4, 5)});
    // then
    EXPECT_EQ(std::make_pair(alge2::point_2d(1, 1), alge2::point_2d(1, 0)), result);
}
