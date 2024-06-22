/*!
 * \file maximum_subarray_test.cpp
 * \brief Tests: Algorithms for maximum subarray.
 */
#include <gtest/gtest.h>
#include "algolib/sequences/maximum_subarray.hpp"

namespace alse = algolib::sequences;

#pragma region find_maximum_subarray

TEST(MaximumSubarrayTest, findMaximumSubarray_WhenAllElementsArePositive_ThenWholeSequence)
{
    // given
    std::vector<double> sequence = {9.0, 2.4, 3.07, 1.93, 12.67};

    // when
    std::vector<double> result = alse::find_maximum_subarray(sequence);

    // then
    EXPECT_EQ(sequence, result);
}

TEST(MaximumSubarrayTest, findMaximumSubarray_WhenNegativeIsLessThanSubsum_ThenIncludeNegative)
{
    // when
    std::vector<double> result =
            alse::find_maximum_subarray(std::vector<double>({3.5, 4.8, -1.6, 7.7, 2.1, -9.3, 0.8}));

    // then
    EXPECT_EQ(std::vector<double>({3.5, 4.8, -1.6, 7.7, 2.1}), result);
}

TEST(MaximumSubarrayTest, findMaximumSubarray_WhenNegativeIsGreaterThanSubsum_ThenExcludeNegative)
{
    // when
    std::vector<double> result = alse::find_maximum_subarray(
            std::vector<double>({-9.3, -1.2, 3.5, 4.8, -10.6, 7.7, 2.1, 0.8, 4.0}));

    // then
    EXPECT_EQ(std::vector<double>({7.7, 2.1, 0.8, 4.0}), result);
}

TEST(MaximumSubarrayTest, findMaximumSubarray_WhenAllElementsAreNegative_ThenEmpty)
{
    // when
    std::vector<double> result =
            alse::find_maximum_subarray(std::vector<double>({-9.0, -2.4, -3.07, -1.93, -12.67}));

    // then
    EXPECT_EQ(std::vector<double>(), result);
}

#pragma endregion
#pragma region count_maximal_subsum

TEST(MaximumSubarrayTest, countMaximalSubsum_WhenAllElementsArePositive_ThenSumOfAll)
{
    // when
    double result = alse::count_maximal_subsum(std::vector<double>({9.0, 2.4, 3.07, 1.93, 12.67}));

    // then
    EXPECT_DOUBLE_EQ(29.07, result);
}

TEST(MaximumSubarrayTest, countMaximalSubsum_WhenNegativeIsLessThanSubsum_ThenIncludeNegative)
{
    // when
    double result =
            alse::count_maximal_subsum(std::vector<double>({3.5, 4.8, -1.6, 7.7, 2.1, -9.3, 0.8}));

    // then
    EXPECT_DOUBLE_EQ(16.5, result);
}

TEST(MaximumSubarrayTest, countMaximalSubsum_WhenNegativeIsGreaterThanSubsum_ThenExcludeNegative)
{
    // when
    double result = alse::count_maximal_subsum(
            std::vector<double>({-9.3, -1.2, 3.5, 4.8, -10.6, 7.7, 2.1, 0.8, 4.0}));

    // then
    EXPECT_DOUBLE_EQ(14.6, result);
}

TEST(MaximumSubarrayTest, countMaximalSubsum_WhenAllElementsAreNegative_ThenZero)
{
    // when
    double result =
            alse::count_maximal_subsum(std::vector<double>({-9.0, -2.4, -3.07, -1.93, -12.67}));

    // then
    EXPECT_DOUBLE_EQ(0.0, result);
}

#pragma endregion
