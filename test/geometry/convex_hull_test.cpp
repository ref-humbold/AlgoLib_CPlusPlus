/*!
 * \file convex_hull_test.cpp
 * \brief Tests: Algorithm for convex hull on a plane (monotone chain)
 */
#include <gtest/gtest.h>
#include "algolib/geometry/convex_hull.hpp"

namespace alge = algolib::geometry;

TEST(ConvexHullTest, findConvexHull_whenOnePoint_thenEmptyConvexHull)
{
    // when
    std::vector<alge::point2d> result = alge::find_convex_hull({alge::point2d(3.0, 2.0)});
    // then
    EXPECT_TRUE(result.empty());
}

TEST(ConvexHullTest, findConvexHull_whenTwoPoints_thenEmptyConvexHull)
{
    // when
    std::vector<alge::point2d> result =
            alge::find_convex_hull({alge::point2d(2.0, 3.0), alge::point2d(3.0, 2.0)});
    // then
    EXPECT_TRUE(result.empty());
}

TEST(ConvexHullTest, findConvexHull_whenThreePoints_thenThesePointsAreConvexHull)
{
    // given
    std::vector<alge::point2d> points = {alge::point2d(1.0, -1.0), alge::point2d(5.0, 1.0),
                                         alge::point2d(3.0, 4.0)};
    // when
    std::vector<alge::point2d> result = alge::find_convex_hull(points);
    // then
    EXPECT_EQ(points, result);
}

TEST(ConvexHullTest, findConvexHull_thenPointsInConvexHull)
{
    // when
    std::vector<alge::point2d> result = alge::find_convex_hull(
            {alge::point2d(1, -3), alge::point2d(-4, 6), alge::point2d(-5, -7),
             alge::point2d(-8, -7), alge::point2d(-3, -4), alge::point2d(5, 9),
             alge::point2d(-1, -8), alge::point2d(-5, 10), alge::point2d(8, 0),
             alge::point2d(3, -6), alge::point2d(-2, 1), alge::point2d(-2, 8), alge::point2d(10, 2),
             alge::point2d(6, 3), alge::point2d(-7, 7), alge::point2d(6, -4)});
    // then
    EXPECT_EQ(std::vector<alge::point2d>({alge::point2d(-8, -7), alge::point2d(-1, -8),
                                          alge::point2d(3, -6), alge::point2d(6, -4),
                                          alge::point2d(10, 2), alge::point2d(5, 9),
                                          alge::point2d(-5, 10), alge::point2d(-7, 7)}),
              result);
}

TEST(ConvexHullTest, findConvexHull_whenMultiplePointsAreCollinear_thenConvexHullOmitsInnerPoints)
{
    // when
    std::vector<alge::point2d> result = alge::find_convex_hull(
            {alge::point2d(-1, -3), alge::point2d(-3, -3), alge::point2d(-3, -1),
             alge::point2d(2, -3), alge::point2d(-3, 5), alge::point2d(0, -3), alge::point2d(7, -3),
             alge::point2d(-3, -2)});
    // then
    EXPECT_EQ(std::vector<alge::point2d>(
                      {alge::point2d(-3, -3), alge::point2d(7, -3), alge::point2d(-3, 5)}),
              result);
}
