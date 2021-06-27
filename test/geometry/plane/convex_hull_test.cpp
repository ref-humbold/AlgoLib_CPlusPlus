/*!
 * \file convex_hull_test.cpp
 * \brief Tests: Algorithm for convex hull (monotone chain) in 2D
 */
#include <gtest/gtest.h>
#include "algolib/geometry/plane/convex_hull.hpp"

namespace algep = algolib::geometry::plane;

TEST(ConvexHullTest, findConvexHull_WhenOnePoint_ThenEmpty)
{
    // when
    std::vector<algep::point_2d> result = algep::find_convex_hull({algep::point_2d(3.0, 2.0)});
    // then
    EXPECT_TRUE(result.empty());
}

TEST(ConvexHullTest, findConvexHull_WhenTwoPoints_ThenEmpty)
{
    // when
    std::vector<algep::point_2d> result =
            algep::find_convex_hull({algep::point_2d(2.0, 3.0), algep::point_2d(3.0, 2.0)});
    // then
    EXPECT_TRUE(result.empty());
}

TEST(ConvexHullTest, findConvexHull_WhenThreePoints_ThenThesePointsAreHull)
{
    // given
    std::vector<algep::point_2d> points = {algep::point_2d(1.0, -1.0), algep::point_2d(5.0, 1.0),
                                           algep::point_2d(3.0, 4.0)};
    // when
    std::vector<algep::point_2d> result = algep::find_convex_hull(points);
    // then
    EXPECT_EQ(points, result);
}

TEST(ConvexHullTest, findConvexHull_ThenPointsInHull)
{
    // when
    std::vector<algep::point_2d> result = algep::find_convex_hull(
            {algep::point_2d(1, -3), algep::point_2d(-4, 6), algep::point_2d(-5, -7),
             algep::point_2d(-8, -7), algep::point_2d(-3, -4), algep::point_2d(5, 9),
             algep::point_2d(-1, -8), algep::point_2d(-5, 10), algep::point_2d(8, 0),
             algep::point_2d(3, -6), algep::point_2d(-2, 1), algep::point_2d(-2, 8),
             algep::point_2d(10, 2), algep::point_2d(6, 3), algep::point_2d(-7, 7),
             algep::point_2d(6, -4)});
    // then
    EXPECT_EQ(std::vector<algep::point_2d>({algep::point_2d(-8, -7), algep::point_2d(-1, -8),
                                            algep::point_2d(3, -6), algep::point_2d(6, -4),
                                            algep::point_2d(10, 2), algep::point_2d(5, 9),
                                            algep::point_2d(-5, 10), algep::point_2d(-7, 7)}),
              result);
}

TEST(ConvexHullTest, findConvexHull_WhenMultiplePointsAreCollinear_ThenInnerPointsOmitted)
{
    // when
    std::vector<algep::point_2d> result = algep::find_convex_hull(
            {algep::point_2d(-1, -3), algep::point_2d(-3, -3), algep::point_2d(-3, -1),
             algep::point_2d(2, -3), algep::point_2d(-3, 5), algep::point_2d(0, -3),
             algep::point_2d(7, -3), algep::point_2d(-3, -2)});
    // then
    EXPECT_EQ(std::vector<algep::point_2d>(
                      {algep::point_2d(-3, -3), algep::point_2d(7, -3), algep::point_2d(-3, 5)}),
              result);
}
