/*!
 * \file geometry2d_test.cpp
 * \brief Basic geometric operations in 2 dimensions
 */
#include <gtest/gtest.h>
#include "algolib/geometry/plane/geometry2d.hpp"

namespace algep = algolib::geometry::plane;

TEST(Geometry2DTest, sortByX_ThenSortedStablyAscendingByFirstCoordinate)
{
    // given
    std::vector<algep::point2d> sequence = {
            algep::point2d(0.0, 0.0), algep::point2d(-2.0, -3.0), algep::point2d(-3.0, 2.0),
            algep::point2d(2.0, 3.0), algep::point2d(3.0, -2.0),  algep::point2d(-2.0, 3.0),
            algep::point2d(3.0, 2.0), algep::point2d(2.0, -3.0),  algep::point2d(-3.0, -2.0)};
    // when
    algep::sort_by_x(sequence);
    // then
    EXPECT_EQ(std::vector<algep::point2d>({algep::point2d(-3.0, 2.0), algep::point2d(-3.0, -2.0),
                                           algep::point2d(-2.0, -3.0), algep::point2d(-2.0, 3.0),
                                           algep::point2d(0.0, 0.0), algep::point2d(2.0, 3.0),
                                           algep::point2d(2.0, -3.0), algep::point2d(3.0, -2.0),
                                           algep::point2d(3.0, 2.0)}),
              sequence);
}

TEST(Geometry2DTest, sortByY_ThenSortedStablyAscendingByFirstCoordinate)
{
    // given
    std::vector<algep::point2d> sequence = {
            algep::point2d(0.0, 0.0), algep::point2d(-2.0, -3.0), algep::point2d(-3.0, 2.0),
            algep::point2d(2.0, 3.0), algep::point2d(3.0, -2.0),  algep::point2d(-2.0, 3.0),
            algep::point2d(3.0, 2.0), algep::point2d(2.0, -3.0),  algep::point2d(-3.0, -2.0)};
    // when
    algep::sort_by_y(sequence);
    // then
    EXPECT_EQ(std::vector<algep::point2d>({algep::point2d(-2.0, -3.0), algep::point2d(2.0, -3.0),
                                           algep::point2d(3.0, -2.0), algep::point2d(-3.0, -2.0),
                                           algep::point2d(0.0, 0.0), algep::point2d(-3.0, 2.0),
                                           algep::point2d(3.0, 2.0), algep::point2d(2.0, 3.0),
                                           algep::point2d(-2.0, 3.0)}),
              sequence);
}

TEST(Geometry2DTest, sortByAngle_ThenSortedAscendingByAngleInDegrees)
{
    // given
    std::vector<algep::point2d> sequence = {
            algep::point2d(0.0, 0.0), algep::point2d(-2.0, -3.0), algep::point2d(-3.0, 2.0),
            algep::point2d(2.0, 3.0), algep::point2d(3.0, -2.0),  algep::point2d(-2.0, 3.0),
            algep::point2d(3.0, 2.0), algep::point2d(2.0, -3.0),  algep::point2d(-3.0, -2.0)};
    // when
    algep::sort_by_angle(sequence);
    // then
    EXPECT_EQ(std::vector<algep::point2d>({algep::point2d(0.0, 0.0), algep::point2d(3.0, 2.0),
                                           algep::point2d(2.0, 3.0), algep::point2d(-2.0, 3.0),
                                           algep::point2d(-3.0, 2.0), algep::point2d(-3.0, -2.0),
                                           algep::point2d(-2.0, -3.0), algep::point2d(2.0, -3.0),
                                           algep::point2d(3.0, -2.0)}),
              sequence);
}

TEST(Geometry2DTest, distance_WhenDifferentPoints_ThenDistance)
{
    // when
    double result = algep::distance(algep::point2d(4.0, 5.0), algep::point2d(-2.0, -3.0));
    // then
    EXPECT_EQ(10.0, result);
}

TEST(Geometry2DTest, distance_WhenSamePoint_ThenZero)
{
    // given
    algep::point2d point(13.5, 6.5);
    // when
    double result = algep::distance(point, point);
    // then
    EXPECT_EQ(0.0, result);
}

TEST(Geometry2DTest, translate_ThenPointTranslated)
{
    // when
    algep::point2d result =
            algep::translate(algep::point2d(13.7, 6.5), algep::vector2d(-10.4, 3.3));
    // then
    EXPECT_EQ(algep::point2d(3.3, 9.8), result);
}

TEST(Geometry2DTest, translate_WhenZeroVector_ThenSamePoint)
{
    // given
    algep::point2d point(13.5, 6.5);
    // when
    algep::point2d result = algep::translate(point, algep::vector2d(0.0, 0.0));
    // then
    EXPECT_EQ(point, result);
}
