// TESTY DLA PODCIĄGU SPÓJNEGO O MAKSYMALNEJ SUMIE
#include <gtest/gtest.h>
#include "algolib/maximum_subarray.hpp"

TEST(MaximumSubarrayTest, testFindMaximumSubarray1)
{
    std::vector<double> sequence = {3.5, 4.8, -1.6, 7.7, 2.1, -9.3, 0.8};

    std::vector<double> result = algolib::find_maximum_subarray(sequence);

    EXPECT_EQ(std::vector<double>({3.5, 4.8, -1.6, 7.7, 2.1}), result);
}

TEST(MaximumSubarrayTest, testFindMaximumSubarray2)
{
    std::vector<double> sequence = {-9.3, -1.2, 3.5, 4.8, -10.6, 7.7, 2.1, 0.8, 4.0};

    std::vector<double> result = algolib::find_maximum_subarray(sequence);

    EXPECT_EQ(std::vector<double>({7.7, 2.1, 0.8, 4.0}), result);
}

TEST(MaximumSubarrayTest, testFindMaximumSubarrayWhenAllElementsAreNegative)
{
    std::vector<double> sequence = {-9.0, -2.4, -3.07, -1.93, -12.67};

    std::vector<double> result = algolib::find_maximum_subarray(sequence);

    EXPECT_EQ(std::vector<double>(), result);
}

TEST(MaximumSubarrayTest, testFindMaximumalSum1)
{
    std::vector<double> sequence = {3.5, 4.8, -1.6, 7.7, 2.1, -9.3, 0.8};

    double result = algolib::find_maximal_sum(sequence);

    EXPECT_DOUBLE_EQ(16.5, result);
}

TEST(MaximumSubarrayTest, testFindMaximumalSum2)
{
    std::vector<double> sequence = {-9.3, -1.2, 3.5, 4.8, -10.6, 7.7, 2.1, 0.8, 4.0};

    double result = algolib::find_maximal_sum(sequence);

    EXPECT_DOUBLE_EQ(14.6, result);
}

TEST(MaximumSubarrayTest, testFindMaximumalSumWhenAllElementsAreNegative)
{
    std::vector<double> sequence = {-9.0, -2.4, -3.07, -1.93, -12.67};

    double result = algolib::find_maximal_sum(sequence);

    EXPECT_DOUBLE_EQ(0.0, result);
}
