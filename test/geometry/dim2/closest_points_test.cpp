/*!
 * \file closest_points_test.cpp
 * \brief Tests: Algorithm for searching pair of closest points in 2D.
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
    EXPECT_EQ(std::make_pair(alge2::point_2d(1, 0), alge2::point_2d(1, 1)), result);
}

TEST(ClosestPointsTest, findClosestPoints_WhenAllLinearOnX_ThenPairOfClosestPoints)
{
    // when
    std::pair<alge2::point_2d, alge2::point_2d> result = alge2::find_closest_points(
            {alge2::point_2d(14, -40), alge2::point_2d(14, -3), alge2::point_2d(14, 36),
             alge2::point_2d(14, 7), alge2::point_2d(14, -24), alge2::point_2d(14, 1),
             alge2::point_2d(14, -14), alge2::point_2d(14, 19)});
    // then
    EXPECT_EQ(std::make_pair(alge2::point_2d(14, -3), alge2::point_2d(14, 1)), result);
}

TEST(ClosestPointsTest, findClosestPoints_WhenAllLinearOnY_ThenPairOfClosestPoints)
{
    // when
    std::pair<alge2::point_2d, alge2::point_2d> result = alge2::find_closest_points(
            {alge2::point_2d(-27, -6), alge2::point_2d(13, -6), alge2::point_2d(-8, -6),
             alge2::point_2d(30, -6), alge2::point_2d(6, -6), alge2::point_2d(-15, -6),
             alge2::point_2d(-3, -6), alge2::point_2d(22, -6)});
    // then
    EXPECT_EQ(std::make_pair(alge2::point_2d(-8, -6), alge2::point_2d(-3, -6)), result);
}
