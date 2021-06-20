/*!
 * \file geometry3d_test.cpp
 * \brief Tests: Basic geometric operations in 3 dimensions
 */
#include <gtest/gtest.h>
#include "algolib/geometry/space/geometry3d.hpp"

namespace alges = algolib::geometry::space;

TEST(Geometry3DTest, sortByX_ThenSortedStablyAscendingByFirstCoordinate)
{
    // given
    std::vector<alges::point3d> sequence = {
            alges::point3d(0.0, 0.0, 0.0),    alges::point3d(2.0, 3.0, -5.0),
            alges::point3d(-2.0, -3.0, 5.0),  alges::point3d(2.0, -3.0, -5.0),
            alges::point3d(-2.0, -3.0, -5.0), alges::point3d(3.0, 2.0, 5.0),
            alges::point3d(-3.0, 2.0, 5.0)};
    // when
    alges::sort_by_x(sequence);
    // then
    EXPECT_EQ(std::vector<alges::point3d>(
                      {alges::point3d(-3.0, 2.0, 5.0), alges::point3d(-2.0, -3.0, 5.0),
                       alges::point3d(-2.0, -3.0, -5.0), alges::point3d(0.0, 0.0, 0.0),
                       alges::point3d(2.0, 3.0, -5.0), alges::point3d(2.0, -3.0, -5.0),
                       alges::point3d(3.0, 2.0, 5.0)}),
              sequence);
}

TEST(Geometry3DTest, sortByY_ThenSortedStablyAscendingByFirstCoordinate)
{
    // given
    std::vector<alges::point3d> sequence = {
            alges::point3d(0.0, 0.0, 0.0),    alges::point3d(2.0, 3.0, -5.0),
            alges::point3d(-2.0, -3.0, 5.0),  alges::point3d(2.0, -3.0, -5.0),
            alges::point3d(-2.0, -3.0, -5.0), alges::point3d(3.0, 2.0, 5.0),
            alges::point3d(-3.0, 2.0, 5.0)};
    // when
    alges::sort_by_y(sequence);
    // then
    EXPECT_EQ(std::vector<alges::point3d>(
                      {alges::point3d(-2.0, -3.0, 5.0), alges::point3d(2.0, -3.0, -5.0),
                       alges::point3d(-2.0, -3.0, -5.0), alges::point3d(0.0, 0.0, 0.0),
                       alges::point3d(3.0, 2.0, 5.0), alges::point3d(-3.0, 2.0, 5.0),
                       alges::point3d(2.0, 3.0, -5.0)}),
              sequence);
}

TEST(Geometry3DTest, sortByZ_ThenSortedStablyAscendingByFirstCoordinate)
{
    // given
    std::vector<alges::point3d> sequence = {
            alges::point3d(0.0, 0.0, 0.0),    alges::point3d(2.0, 3.0, -5.0),
            alges::point3d(-2.0, -3.0, 5.0),  alges::point3d(2.0, -3.0, -5.0),
            alges::point3d(-2.0, -3.0, -5.0), alges::point3d(3.0, 2.0, 5.0),
            alges::point3d(-3.0, 2.0, 5.0)};
    // when
    alges::sort_by_z(sequence);
    // then
    EXPECT_EQ(std::vector<alges::point3d>(
                      {alges::point3d(2.0, 3.0, -5.0), alges::point3d(2.0, -3.0, -5.0),
                       alges::point3d(-2.0, -3.0, -5.0), alges::point3d(0.0, 0.0, 0.0),
                       alges::point3d(-2.0, -3.0, 5.0), alges::point3d(3.0, 2.0, 5.0),
                       alges::point3d(-3.0, 2.0, 5.0)}),
              sequence);
}

TEST(Geometry3DTest, distance_WhenDifferentPoints_ThenDistance)
{
    // when
    double result = alges::distance(alges::point3d(4.0, 8.0, 5.0), alges::point3d(-2.0, -1.0, 3.0));
    // then
    EXPECT_EQ(11.0, result);
}

TEST(Geometry3DTest, distance_WhenSamePoint_ThenZero)
{
    // given
    alges::point3d point(13.5, 6.5, -4.2);
    // when
    double result = alges::distance(point, point);
    // then
    EXPECT_EQ(0.0, result);
}

TEST(Geometry3DTest, translate_ThenPointTranslated)
{
    // when
    alges::point3d result =
            alges::translate(alges::point3d(13.7, 6.5, -4.2), alges::vector3d(-10.4, 3.3, 1.1));
    // then
    EXPECT_EQ(alges::point3d(3.3, 9.8, -3.1), result);
}

TEST(Geometry3DTest, translate_WhenZeroVector_ThenSamePoint)
{
    // given
    alges::point3d point(13.5, 6.5, -4.2);
    // when
    alges::point3d result = alges::translate(point, alges::vector3d(0.0, 0.0, 0.0));
    // then
    EXPECT_EQ(point, result);
}
