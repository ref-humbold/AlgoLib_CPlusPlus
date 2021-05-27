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
