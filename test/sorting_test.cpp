// TESTY DLA ALGORYTMÓW SORTOWANIA TOPOLOGICZNEGO"""
#include <gtest/gtest.h>
#include "algolib/sorting.hpp"

TEST(SortingTest, testAngleSort)
{
    std::vector<point2D_t> sequence = {
        std::make_pair(0.0, 0.0),  std::make_pair(-2.0, -3.0), std::make_pair(-3.0, -2.0),
        std::make_pair(3.0, -2.0), std::make_pair(-2.0, 3.0),  std::make_pair(3.0, 2.0),
        std::make_pair(2.0, -3.0), std::make_pair(2.0, 3.0),   std::make_pair(-3.0, 2.0)};

    algolib::angle_sort(sequence);

    EXPECT_EQ(std::vector<point2D_t>({std::make_pair(0.0, 0.0), std::make_pair(3.0, 2.0),
                                      std::make_pair(2.0, 3.0), std::make_pair(-2.0, 3.0),
                                      std::make_pair(-3.0, 2.0), std::make_pair(-3.0, -2.0),
                                      std::make_pair(-2.0, -3.0), std::make_pair(2.0, -3.0),
                                      std::make_pair(3.0, -2.0)}),
              sequence);
};

TEST(SortingTest, testAngleSortWhenAllEqual)
{
    std::vector<point2D_t> sequence = {
        std::make_pair(1.0, 2.0), std::make_pair(1.0, 2.0), std::make_pair(1.0, 2.0),
        std::make_pair(1.0, 2.0), std::make_pair(1.0, 2.0), std::make_pair(1.0, 2.0),
        std::make_pair(1.0, 2.0), std::make_pair(1.0, 2.0), std::make_pair(1.0, 2.0)};

    algolib::angle_sort(sequence);

    EXPECT_EQ(std::vector<point2D_t>(
                  {std::make_pair(1.0, 2.0), std::make_pair(1.0, 2.0), std::make_pair(1.0, 2.0),
                   std::make_pair(1.0, 2.0), std::make_pair(1.0, 2.0), std::make_pair(1.0, 2.0),
                   std::make_pair(1.0, 2.0), std::make_pair(1.0, 2.0), std::make_pair(1.0, 2.0)}),
              sequence);
};

TEST(SortingTest, testAngleSortWhenEmptyVector)
{
    std::vector<point2D_t> sequence;

    algolib::angle_sort(sequence);

    EXPECT_EQ(std::vector<point2D_t>(), sequence);
};
