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

TEST(Geometry2DTest, sortByAngle)
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
