/*!
 * \file closest_points_test.cpp
 * \brief Tests: Algorithm for pair of closest points
 */
#include <gtest/gtest.h>
#include "algolib/geometry/plane/closest_points.hpp"

namespace algep = algolib::geometry::plane;

TEST(ClosestPointsTest, findClosestPoints_WhenOnePoint_ThenThisPoint)
{
    // when
    std::pair<algep::point2d, algep::point2d> result =
            algep::find_closest_points({algep::point2d(2, 2)});
    // then
    EXPECT_EQ(std::make_pair(algep::point2d(2, 2), algep::point2d(2, 2)), result);
}

TEST(ClosestPointsTest, findClosestPoints_WhenTwoPoints_ThenThesePoints)
{
    // when
    std::pair<algep::point2d, algep::point2d> result =
            algep::find_closest_points({algep::point2d(2, 2), algep::point2d(4, 4)});
    // then
    EXPECT_EQ(std::make_pair(algep::point2d(2, 2), algep::point2d(4, 4)), result);
}

TEST(ClosestPointsTest, findClosestPoints_WhenThreePoints_ThenPairOfClosestPoints)
{
    // when
    std::pair<algep::point2d, algep::point2d> result = algep::find_closest_points(
            {algep::point2d(3, 2), algep::point2d(1, 1), algep::point2d(7, 0)});
    // then
    EXPECT_EQ(std::make_pair(algep::point2d(1, 1), algep::point2d(3, 2)), result);
}

TEST(ClosestPointsTest, findClosestPoints_WhenMultiplePoints_ThenPairOfClosestPoints)
{
    // when
    std::pair<algep::point2d, algep::point2d> result = algep::find_closest_points(
            {algep::point2d(1, 1), algep::point2d(-2, 2), algep::point2d(-4, 4),
             algep::point2d(3, -3), algep::point2d(0, -5), algep::point2d(1, 0),
             algep::point2d(-7, 2), algep::point2d(4, 5)});
    // then
    EXPECT_EQ(std::make_pair(algep::point2d(1, 1), algep::point2d(1, 0)), result);
}
