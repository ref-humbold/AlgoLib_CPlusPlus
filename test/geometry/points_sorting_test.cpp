/*!
 * \file points_sorting_test.cpp
 * \brief Tests: Algorithms for points sorting
 */
#include <gtest/gtest.h>
#include "algolib/geometry/points_sorting.hpp"

namespace alge = algolib::geometry;

TEST(PointsSortingTest, sortByAngle)
{
    std::vector<alge::point2d> sequence = {
            alge::point2d(0.0, 0.0),  alge::point2d(-2.0, -3.0), alge::point2d(-3.0, -2.0),
            alge::point2d(3.0, -2.0), alge::point2d(-2.0, 3.0),  alge::point2d(3.0, 2.0),
            alge::point2d(2.0, -3.0), alge::point2d(2.0, 3.0),   alge::point2d(-3.0, 2.0)};

    alge::sort_by_angle(sequence);

    EXPECT_EQ(std::vector<alge::point2d>({alge::point2d(0.0, 0.0), alge::point2d(3.0, 2.0),
                                          alge::point2d(2.0, 3.0), alge::point2d(-2.0, 3.0),
                                          alge::point2d(-3.0, 2.0), alge::point2d(-3.0, -2.0),
                                          alge::point2d(-2.0, -3.0), alge::point2d(2.0, -3.0),
                                          alge::point2d(3.0, -2.0)}),
              sequence);
}

TEST(PointsSortingTest, sortByAngle_whenAllEqual)
{
    std::vector<alge::point2d> sequence = {
            alge::point2d(1.0, 2.0), alge::point2d(1.0, 2.0), alge::point2d(1.0, 2.0),
            alge::point2d(1.0, 2.0), alge::point2d(1.0, 2.0), alge::point2d(1.0, 2.0),
            alge::point2d(1.0, 2.0), alge::point2d(1.0, 2.0), alge::point2d(1.0, 2.0)};

    alge::sort_by_angle(sequence);

    EXPECT_EQ(std::vector<alge::point2d>(
                      {alge::point2d(1.0, 2.0), alge::point2d(1.0, 2.0), alge::point2d(1.0, 2.0),
                       alge::point2d(1.0, 2.0), alge::point2d(1.0, 2.0), alge::point2d(1.0, 2.0),
                       alge::point2d(1.0, 2.0), alge::point2d(1.0, 2.0), alge::point2d(1.0, 2.0)}),
              sequence);
}

TEST(PointsSortingTest, sortByAngle_whenEmptyVector)
{
    std::vector<alge::point2d> sequence;

    alge::sort_by_angle(sequence);

    EXPECT_EQ(std::vector<alge::point2d>(), sequence);
}

TEST(PointsSortingTest, sortByX)
{
    std::vector<alge::point2d> sequence = {
            alge::point2d(0.0, 0.0),  alge::point2d(-2.0, -3.0), alge::point2d(-3.0, -2.0),
            alge::point2d(3.0, -2.0), alge::point2d(-2.0, 3.0),  alge::point2d(3.0, 2.0),
            alge::point2d(2.0, -3.0), alge::point2d(2.0, 3.0),   alge::point2d(-3.0, 2.0)};

    alge::sort_by_x(sequence);

    EXPECT_EQ(std::vector<alge::point2d>({alge::point2d(-3.0, -2.0), alge::point2d(-3.0, 2.0),
                                          alge::point2d(-2.0, -3.0), alge::point2d(-2.0, 3.0),
                                          alge::point2d(0.0, 0.0), alge::point2d(2.0, -3.0),
                                          alge::point2d(2.0, 3.0), alge::point2d(3.0, -2.0),
                                          alge::point2d(3.0, 2.0)}),
              sequence);
}

TEST(PointsSortingTest, sortByY)
{
    std::vector<alge::point2d> sequence = {
            alge::point2d(0.0, 0.0),  alge::point2d(-2.0, -3.0), alge::point2d(-3.0, -2.0),
            alge::point2d(3.0, -2.0), alge::point2d(-2.0, 3.0),  alge::point2d(3.0, 2.0),
            alge::point2d(2.0, -3.0), alge::point2d(2.0, 3.0),   alge::point2d(-3.0, 2.0)};

    alge::sort_by_y(sequence);

    EXPECT_EQ(std::vector<alge::point2d>({alge::point2d(-2.0, -3.0), alge::point2d(2.0, -3.0),
                                          alge::point2d(-3.0, -2.0), alge::point2d(3.0, -2.0),
                                          alge::point2d(0.0, 0.0), alge::point2d(-3.0, 2.0),
                                          alge::point2d(3.0, 2.0), alge::point2d(-2.0, 3.0),
                                          alge::point2d(2.0, 3.0)}),
              sequence);
}
