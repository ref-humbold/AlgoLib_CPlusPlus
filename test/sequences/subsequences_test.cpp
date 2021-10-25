/*!
 * \file subsequences_test.cpp
 * \brief Tests: Algorithms for subsequences
 */
#include <gtest/gtest.h>
#include "algolib/sequences/subsequences.hpp"

namespace alse = algolib::sequences;

#pragma region longest_increasing

TEST(SubsequencesTest, longestIncreasing_WhenIncreasing_ThenAllElements)
{
    // given
    std::vector<int> sequence = {1, 3, 5, 7, 9, 11, 13, 15};
    // when
    std::vector<int> result = alse::longest_increasing(sequence);
    // then
    EXPECT_EQ(sequence, result);
}

TEST(SubsequencesTest, longestIncreasing_WhenDecreasing_ThenLastElementOnly)
{
    // given
    std::vector<int> sequence = {12, 10, 8, 6, 4, 2};
    // when
    std::vector<int> result = alse::longest_increasing(sequence);
    // then
    EXPECT_EQ(std::vector<int>({2}), result);
}

TEST(SubsequencesTest, longestIncreasing_WhenMultipleSubsequences_ThenLeastLexicographically)
{
    // given
    std::vector<int> sequence = {2, 1, 4, 3, 6, 5, 8, 7, 10};
    // when
    std::vector<int> result = alse::longest_increasing(sequence);
    // then
    EXPECT_EQ(std::vector<int>({1, 3, 5, 7, 10}), result);
}

TEST(SubsequencesTest, longestIncreasing_WhenIncreasingAndReversedComparator_ThenLastElementOnly)
{
    // given
    std::vector<int> sequence = {1, 3, 5, 7, 9, 11, 13, 15};
    // when
    std::vector<int> result = alse::longest_increasing<int, std::greater<int>>(sequence);
    // then
    EXPECT_EQ(std::vector<int>({15}), result);
}

TEST(SubsequencesTest, longestIncreasing_WhenDecreasingAndReversedComparator_ThenAllElements)
{
    // given
    std::vector<int> sequence = {12, 10, 8, 6, 4, 2};
    // when
    std::vector<int> result = alse::longest_increasing<int, std::greater<int>>(sequence);
    // then
    EXPECT_EQ(sequence, result);
}

#pragma endregion
#pragma region maximum_subarray

TEST(SubsequencesTest, maximumSubarray_WhenNegativeIsLessThanSubsum_ThenIncludeNegative)
{
    // given
    std::vector<double> sequence = {3.5, 4.8, -1.6, 7.7, 2.1, -9.3, 0.8};
    // when
    std::vector<double> result = alse::maximum_subarray(sequence);
    // then
    EXPECT_EQ(std::vector<double>({3.5, 4.8, -1.6, 7.7, 2.1}), result);
}

TEST(SubsequencesTest, maximumSubarray_WhenNegativeIsGreaterThanSubsum_ThenExcludeNegative)
{
    // given
    std::vector<double> sequence = {-9.3, -1.2, 3.5, 4.8, -10.6, 7.7, 2.1, 0.8, 4.0};
    // when
    std::vector<double> result = alse::maximum_subarray(sequence);
    // then
    EXPECT_EQ(std::vector<double>({7.7, 2.1, 0.8, 4.0}), result);
}

TEST(SubsequencesTest, maximumSubarray_WhenAllElementsAreNegative_ThenEmpty)
{
    // given
    std::vector<double> sequence = {-9.0, -2.4, -3.07, -1.93, -12.67};
    // when
    std::vector<double> result = alse::maximum_subarray(sequence);
    // then
    EXPECT_EQ(std::vector<double>(), result);
}

#pragma endregion
#pragma region maximal_subsum

TEST(SubsequencesTest, maximalSubsum_WhenNegativeIsLessThanSubsum_ThenIncludeNegative)
{
    // given
    std::vector<double> sequence = {3.5, 4.8, -1.6, 7.7, 2.1, -9.3, 0.8};
    // when
    double result = alse::maximal_subsum(sequence);
    // then
    EXPECT_DOUBLE_EQ(16.5, result);
}

TEST(SubsequencesTest, maximalSubsum_WhenNegativeIsGreaterThanSubsum_ThenExcludeNegative)
{
    // given
    std::vector<double> sequence = {-9.3, -1.2, 3.5, 4.8, -10.6, 7.7, 2.1, 0.8, 4.0};
    // when
    double result = alse::maximal_subsum(sequence);
    // then
    EXPECT_DOUBLE_EQ(14.6, result);
}

TEST(SubsequencesTest, maximalSubsum_WhenAllElementsAreNegative_ThenZero)
{
    // given
    std::vector<double> sequence = {-9.0, -2.4, -3.07, -1.93, -12.67};
    // when
    double result = alse::maximal_subsum(sequence);
    // then
    EXPECT_DOUBLE_EQ(0.0, result);
}

#pragma endregion
