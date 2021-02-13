/*!
 * \file closest_points_test.cpp
 * \brief Tests: Algorithm for pair of closest points on a plane
 */
#include <gtest/gtest.h>
#include "algolib/geometry/closest_points.hpp"

namespace alge = algolib::geometry;

TEST(ClosestPointsTest, findClosestPoints_WhenOnePoint_ThenThisPoint)
{
    // when
    std::pair<alge::point2d, alge::point2d> result =
            alge::find_closest_points({alge::point2d(2, 2)});
    // then
    EXPECT_EQ(std::make_pair(alge::point2d(2, 2), alge::point2d(2, 2)), result);
}

TEST(ClosestPointsTest, findClosestPoints_WhenTwoPoints_ThenThesePoints)
{
    // when
    std::pair<alge::point2d, alge::point2d> result =
            alge::find_closest_points({alge::point2d(2, 2), alge::point2d(4, 4)});
    // then
    EXPECT_EQ(std::make_pair(alge::point2d(2, 2), alge::point2d(4, 4)), result);
}

TEST(ClosestPointsTest, findClosestPoints_WhenThreePoints_ThenPairOfClosestPoints)
{
    // when
    std::pair<alge::point2d, alge::point2d> result = alge::find_closest_points(
            {alge::point2d(3, 2), alge::point2d(1, 1), alge::point2d(7, 0)});
    // then
    EXPECT_EQ(std::make_pair(alge::point2d(1, 1), alge::point2d(3, 2)), result);
}
