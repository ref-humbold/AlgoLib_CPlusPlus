// Tests: Points sorting algorithms.
#include <gtest/gtest.h>
#include "algolib/geometry/points_sorting.hpp"

namespace alge = algolib::geometry;

TEST(PointsSortingTest, testAngleSort)
{
    std::vector<alge::point2d> sequence = {
            alge::p2d(0.0, 0.0),  alge::p2d(-2.0, -3.0), alge::p2d(-3.0, -2.0),
            alge::p2d(3.0, -2.0), alge::p2d(-2.0, 3.0),  alge::p2d(3.0, 2.0),
            alge::p2d(2.0, -3.0), alge::p2d(2.0, 3.0),   alge::p2d(-3.0, 2.0)};

    alge::angle_sort(sequence);

    EXPECT_EQ(std::vector<alge::point2d>(
                      {alge::p2d(0.0, 0.0), alge::p2d(3.0, 2.0), alge::p2d(2.0, 3.0),
                       alge::p2d(-2.0, 3.0), alge::p2d(-3.0, 2.0), alge::p2d(-3.0, -2.0),
                       alge::p2d(-2.0, -3.0), alge::p2d(2.0, -3.0), alge::p2d(3.0, -2.0)}),
              sequence);
}

TEST(PointsSortingTest, testAngleSortWhenAllEqual)
{
    std::vector<alge::point2d> sequence = {
            alge::p2d(1.0, 2.0), alge::p2d(1.0, 2.0), alge::p2d(1.0, 2.0),
            alge::p2d(1.0, 2.0), alge::p2d(1.0, 2.0), alge::p2d(1.0, 2.0),
            alge::p2d(1.0, 2.0), alge::p2d(1.0, 2.0), alge::p2d(1.0, 2.0)};

    alge::angle_sort(sequence);

    EXPECT_EQ(std::vector<alge::point2d>(
                      {alge::p2d(1.0, 2.0), alge::p2d(1.0, 2.0), alge::p2d(1.0, 2.0),
                       alge::p2d(1.0, 2.0), alge::p2d(1.0, 2.0), alge::p2d(1.0, 2.0),
                       alge::p2d(1.0, 2.0), alge::p2d(1.0, 2.0), alge::p2d(1.0, 2.0)}),
              sequence);
}

TEST(PointsSortingTest, testAngleSortWhenEmptyVector)
{
    std::vector<alge::point2d> sequence;

    alge::angle_sort(sequence);

    EXPECT_EQ(std::vector<alge::point2d>(), sequence);
}
