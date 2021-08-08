/*!
 * \file geometry_2d_test.cpp
 * \brief Tests: Algorithms for basic geometrical computations in 2D
 */
#include <gtest/gtest.h>
#include "algolib/geometry/dim2/geometry_2d.hpp"

namespace alge2 = algolib::geometry::dim2;

TEST(Geometry2DTest, sortByX_ThenSortedStablyAscendingByFirstCoordinate)
{
    // given
    std::vector<alge2::point_2d> sequence = {
            alge2::point_2d(0.0, 0.0), alge2::point_2d(-2.0, -3.0), alge2::point_2d(-3.0, 2.0),
            alge2::point_2d(2.0, 3.0), alge2::point_2d(3.0, -2.0),  alge2::point_2d(-2.0, 3.0),
            alge2::point_2d(3.0, 2.0), alge2::point_2d(2.0, -3.0),  alge2::point_2d(-3.0, -2.0)};
    // when
    alge2::sort_by_x(sequence);
    // then
    EXPECT_EQ(std::vector<alge2::point_2d>({alge2::point_2d(-3.0, 2.0), alge2::point_2d(-3.0, -2.0),
                                            alge2::point_2d(-2.0, -3.0), alge2::point_2d(-2.0, 3.0),
                                            alge2::point_2d(0.0, 0.0), alge2::point_2d(2.0, 3.0),
                                            alge2::point_2d(2.0, -3.0), alge2::point_2d(3.0, -2.0),
                                            alge2::point_2d(3.0, 2.0)}),
              sequence);
}

TEST(Geometry2DTest, sortByY_ThenSortedStablyAscendingByFirstCoordinate)
{
    // given
    std::vector<alge2::point_2d> sequence = {
            alge2::point_2d(0.0, 0.0), alge2::point_2d(-2.0, -3.0), alge2::point_2d(-3.0, 2.0),
            alge2::point_2d(2.0, 3.0), alge2::point_2d(3.0, -2.0),  alge2::point_2d(-2.0, 3.0),
            alge2::point_2d(3.0, 2.0), alge2::point_2d(2.0, -3.0),  alge2::point_2d(-3.0, -2.0)};
    // when
    alge2::sort_by_y(sequence);
    // then
    EXPECT_EQ(std::vector<alge2::point_2d>({alge2::point_2d(-2.0, -3.0), alge2::point_2d(2.0, -3.0),
                                            alge2::point_2d(3.0, -2.0), alge2::point_2d(-3.0, -2.0),
                                            alge2::point_2d(0.0, 0.0), alge2::point_2d(-3.0, 2.0),
                                            alge2::point_2d(3.0, 2.0), alge2::point_2d(2.0, 3.0),
                                            alge2::point_2d(-2.0, 3.0)}),
              sequence);
}

TEST(Geometry2DTest, sortByAngle_ThenSortedAscendingByAngleInDegrees)
{
    // given
    std::vector<alge2::point_2d> sequence = {
            alge2::point_2d(0.0, 0.0), alge2::point_2d(-2.0, -3.0), alge2::point_2d(-3.0, 2.0),
            alge2::point_2d(2.0, 3.0), alge2::point_2d(3.0, -2.0),  alge2::point_2d(-2.0, 3.0),
            alge2::point_2d(3.0, 2.0), alge2::point_2d(2.0, -3.0),  alge2::point_2d(-3.0, -2.0)};
    // when
    alge2::sort_by_angle(sequence);
    // then
    EXPECT_EQ(std::vector<alge2::point_2d>({alge2::point_2d(0.0, 0.0), alge2::point_2d(3.0, 2.0),
                                            alge2::point_2d(2.0, 3.0), alge2::point_2d(-2.0, 3.0),
                                            alge2::point_2d(-3.0, 2.0), alge2::point_2d(-3.0, -2.0),
                                            alge2::point_2d(-2.0, -3.0), alge2::point_2d(2.0, -3.0),
                                            alge2::point_2d(3.0, -2.0)}),
              sequence);
}

TEST(Geometry2DTest, distance_WhenDifferentPoints_ThenDistance)
{
    // when
    double result = alge2::distance(alge2::point_2d(4.0, 5.0), alge2::point_2d(-2.0, -3.0));
    // then
    EXPECT_EQ(10.0, result);
}

TEST(Geometry2DTest, distance_WhenSamePoint_ThenZero)
{
    // given
    alge2::point_2d point(13.5, 6.5);
    // when
    double result = alge2::distance(point, point);
    // then
    EXPECT_EQ(0.0, result);
}

TEST(Geometry2DTest, translate_ThenPointTranslated)
{
    // when
    alge2::point_2d result =
            alge2::translate(alge2::point_2d(13.7, 6.5), alge2::vector_2d(-10.4, 3.3));
    // then
    EXPECT_EQ(alge2::point_2d(3.3, 9.8), result);
}

TEST(Geometry2DTest, translate_WhenZeroVector_ThenSamePoint)
{
    // given
    alge2::point_2d point(13.5, 6.5);
    // when
    alge2::point_2d result = alge2::translate(point, alge2::vector_2d(0.0, 0.0));
    // then
    EXPECT_EQ(point, result);
}
