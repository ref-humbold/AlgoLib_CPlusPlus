/*!
 * \file convex_hull_test.cpp
 * \brief Tests: Algorithm for convex hull in 2D (monotone chain).
 */
#include <gtest/gtest.h>
#include "algolib/geometry/dim2/convex_hull.hpp"

namespace alge2 = algolib::geometry::dim2;

TEST(ConvexHullTest, findConvexHull_WhenOnePoint_ThenEmpty)
{
    // when
    std::vector<alge2::point_2d> result = alge2::find_convex_hull({alge2::point_2d(3.0, 2.0)});

    // then
    EXPECT_TRUE(result.empty());
}

TEST(ConvexHullTest, findConvexHull_WhenTwoPoints_ThenEmpty)
{
    // when
    std::vector<alge2::point_2d> result =
            alge2::find_convex_hull({alge2::point_2d(2.0, 3.0), alge2::point_2d(3.0, 2.0)});

    // then
    EXPECT_TRUE(result.empty());
}

TEST(ConvexHullTest, findConvexHull_WhenThreePoints_ThenThesePointsAreHull)
{
    // given
    std::vector<alge2::point_2d> points = {
            alge2::point_2d(1.0, -1.0), alge2::point_2d(5.0, 1.0), alge2::point_2d(3.0, 4.0)};

    // when
    std::vector<alge2::point_2d> result = alge2::find_convex_hull(points);

    // then
    EXPECT_EQ(points, result);
}

TEST(ConvexHullTest, findConvexHull_ThenPointsInHull)
{
    // when
    std::vector<alge2::point_2d> result = alge2::find_convex_hull(
            {alge2::point_2d(1, -3), alge2::point_2d(-4, 6), alge2::point_2d(-5, -7),
             alge2::point_2d(-8, -7), alge2::point_2d(-3, -4), alge2::point_2d(5, 9),
             alge2::point_2d(-1, -8), alge2::point_2d(-5, 10), alge2::point_2d(8, 0),
             alge2::point_2d(3, -6), alge2::point_2d(-2, 1), alge2::point_2d(-2, 8),
             alge2::point_2d(10, 2), alge2::point_2d(6, 3), alge2::point_2d(-7, 7),
             alge2::point_2d(6, -4)});

    // then
    EXPECT_EQ(
            std::vector<alge2::point_2d>(
                    {alge2::point_2d(-8, -7), alge2::point_2d(-1, -8), alge2::point_2d(3, -6),
                     alge2::point_2d(6, -4), alge2::point_2d(10, 2), alge2::point_2d(5, 9),
                     alge2::point_2d(-5, 10), alge2::point_2d(-7, 7)}),
            result);
}

TEST(ConvexHullTest, findConvexHull_WhenMultiplePointsAreCollinear_ThenInnerPointsOmitted)
{
    // when
    std::vector<alge2::point_2d> result = alge2::find_convex_hull(
            {alge2::point_2d(-1, -3), alge2::point_2d(-3, -3), alge2::point_2d(-3, -1),
             alge2::point_2d(2, -3), alge2::point_2d(-3, 5), alge2::point_2d(0, -3),
             alge2::point_2d(7, -3), alge2::point_2d(-3, -2)});

    // then
    EXPECT_EQ(
            std::vector<alge2::point_2d>(
                    {alge2::point_2d(-3, -3), alge2::point_2d(7, -3), alge2::point_2d(-3, 5)}),
            result);
}
