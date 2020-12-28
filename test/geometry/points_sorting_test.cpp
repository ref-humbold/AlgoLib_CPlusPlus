/*!
 * \file points_sorting_test.cpp
 * \brief Tests: Algorithms for points sorting
 */
#include <gtest/gtest.h>
#include "algolib/geometry/points_sorting.hpp"

namespace alge = algolib::geometry;

TEST(PointsSortingTest, sortByX_When2D_ThenSortedStablyAscendingByFirstCoordinate)
{
    // given
    std::vector<alge::point2d> sequence = {
            alge::point2d(0.0, 0.0), alge::point2d(-2.0, -3.0), alge::point2d(-3.0, 2.0),
            alge::point2d(2.0, 3.0), alge::point2d(3.0, -2.0),  alge::point2d(-2.0, 3.0),
            alge::point2d(3.0, 2.0), alge::point2d(2.0, -3.0),  alge::point2d(-3.0, -2.0)};
    // when
    alge::sort_by_x(sequence);
    // then
    EXPECT_EQ(std::vector<alge::point2d>({alge::point2d(-3.0, 2.0), alge::point2d(-3.0, -2.0),
                                          alge::point2d(-2.0, -3.0), alge::point2d(-2.0, 3.0),
                                          alge::point2d(0.0, 0.0), alge::point2d(2.0, 3.0),
                                          alge::point2d(2.0, -3.0), alge::point2d(3.0, -2.0),
                                          alge::point2d(3.0, 2.0)}),
              sequence);
}

TEST(PointsSortingTest, sortByX_When3D_ThenSortedStablyAscendingByFirstCoordinate)
{
    // given
    std::vector<alge::point3d> sequence = {
            alge::point3d(0.0, 0.0, 0.0),    alge::point3d(2.0, 3.0, -5.0),
            alge::point3d(-2.0, -3.0, 5.0),  alge::point3d(2.0, -3.0, -5.0),
            alge::point3d(-2.0, -3.0, -5.0), alge::point3d(3.0, 2.0, 5.0),
            alge::point3d(-3.0, 2.0, 5.0)};
    // when
    alge::sort_by_x(sequence);
    // then
    EXPECT_EQ(std::vector<alge::point3d>(
                      {alge::point3d(-3.0, 2.0, 5.0), alge::point3d(-2.0, -3.0, 5.0),
                       alge::point3d(-2.0, -3.0, -5.0), alge::point3d(0.0, 0.0, 0.0),
                       alge::point3d(2.0, 3.0, -5.0), alge::point3d(2.0, -3.0, -5.0),
                       alge::point3d(3.0, 2.0, 5.0)}),
              sequence);
}

TEST(PointsSortingTest, sortByY_When2D_ThenSortedStablyAscendingByFirstCoordinate)
{
    // given
    std::vector<alge::point2d> sequence = {
            alge::point2d(0.0, 0.0), alge::point2d(-2.0, -3.0), alge::point2d(-3.0, 2.0),
            alge::point2d(2.0, 3.0), alge::point2d(3.0, -2.0),  alge::point2d(-2.0, 3.0),
            alge::point2d(3.0, 2.0), alge::point2d(2.0, -3.0),  alge::point2d(-3.0, -2.0)};
    // when
    alge::sort_by_y(sequence);
    // then
    EXPECT_EQ(std::vector<alge::point2d>({alge::point2d(-2.0, -3.0), alge::point2d(2.0, -3.0),
                                          alge::point2d(3.0, -2.0), alge::point2d(-3.0, -2.0),
                                          alge::point2d(0.0, 0.0), alge::point2d(-3.0, 2.0),
                                          alge::point2d(3.0, 2.0), alge::point2d(2.0, 3.0),
                                          alge::point2d(-2.0, 3.0)}),
              sequence);
}

TEST(PointsSortingTest, sortByY_When3D_ThenSortedStablyAscendingByFirstCoordinate)
{
    // given
    std::vector<alge::point3d> sequence = {
            alge::point3d(0.0, 0.0, 0.0),    alge::point3d(2.0, 3.0, -5.0),
            alge::point3d(-2.0, -3.0, 5.0),  alge::point3d(2.0, -3.0, -5.0),
            alge::point3d(-2.0, -3.0, -5.0), alge::point3d(3.0, 2.0, 5.0),
            alge::point3d(-3.0, 2.0, 5.0)};
    // when
    alge::sort_by_y(sequence);
    // then
    EXPECT_EQ(std::vector<alge::point3d>(
                      {alge::point3d(-2.0, -3.0, 5.0), alge::point3d(2.0, -3.0, -5.0),
                       alge::point3d(-2.0, -3.0, -5.0), alge::point3d(0.0, 0.0, 0.0),
                       alge::point3d(3.0, 2.0, 5.0), alge::point3d(-3.0, 2.0, 5.0),
                       alge::point3d(2.0, 3.0, -5.0)}),
              sequence);
}

TEST(PointsSortingTest, sortByZ_When3D_ThenSortedStablyAscendingByFirstCoordinate)
{
    // given
    std::vector<alge::point3d> sequence = {
            alge::point3d(0.0, 0.0, 0.0),    alge::point3d(2.0, 3.0, -5.0),
            alge::point3d(-2.0, -3.0, 5.0),  alge::point3d(2.0, -3.0, -5.0),
            alge::point3d(-2.0, -3.0, -5.0), alge::point3d(3.0, 2.0, 5.0),
            alge::point3d(-3.0, 2.0, 5.0)};
    // when
    alge::sort_by_z(sequence);
    // then
    EXPECT_EQ(std::vector<alge::point3d>(
                      {alge::point3d(2.0, 3.0, -5.0), alge::point3d(2.0, -3.0, -5.0),
                       alge::point3d(-2.0, -3.0, -5.0), alge::point3d(0.0, 0.0, 0.0),
                       alge::point3d(-2.0, -3.0, 5.0), alge::point3d(3.0, 2.0, 5.0),
                       alge::point3d(-3.0, 2.0, 5.0)}),
              sequence);
}

TEST(PointsSortingTest, sortByAngle)
{
    // given
    std::vector<alge::point2d> sequence = {
            alge::point2d(0.0, 0.0), alge::point2d(-2.0, -3.0), alge::point2d(-3.0, 2.0),
            alge::point2d(2.0, 3.0), alge::point2d(3.0, -2.0),  alge::point2d(-2.0, 3.0),
            alge::point2d(3.0, 2.0), alge::point2d(2.0, -3.0),  alge::point2d(-3.0, -2.0)};
    // when
    alge::sort_by_angle(sequence);
    // then
    EXPECT_EQ(std::vector<alge::point2d>({alge::point2d(0.0, 0.0), alge::point2d(3.0, 2.0),
                                          alge::point2d(2.0, 3.0), alge::point2d(-2.0, 3.0),
                                          alge::point2d(-3.0, 2.0), alge::point2d(-3.0, -2.0),
                                          alge::point2d(-2.0, -3.0), alge::point2d(2.0, -3.0),
                                          alge::point2d(3.0, -2.0)}),
              sequence);
}
