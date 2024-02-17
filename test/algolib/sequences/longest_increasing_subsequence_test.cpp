/*!
 * \file longest_increasing_subsequence_test.cpp
 * \brief Tests: Algorithm for longest increasing subsequence.
 */
#include <gtest/gtest.h>
#include "algolib/sequences/longest_increasing_subsequence.hpp"

namespace alse = algolib::sequences;

TEST(LongestIncreasingSubsequenceTest, findLis_WhenIncreasing_ThenAllElements)
{
    // given
    std::vector<int> sequence = {1, 3, 5, 7, 9, 11, 13, 15};
    // when
    std::vector<int> result = alse::find_lis(sequence);
    // then
    EXPECT_EQ(sequence, result);
}

TEST(LongestIncreasingSubsequenceTest, findLis_WhenDecreasing_ThenLastElementOnly)
{
    // when
    std::vector<int> result = alse::find_lis(std::vector<int>({12, 10, 8, 6, 4, 2}));
    // then
    EXPECT_EQ(std::vector<int>({2}), result);
}

TEST(LongestIncreasingSubsequenceTest, findLis_WhenMultipleSubsequences_ThenLeastLexicographically)
{
    // when
    std::vector<int> result = alse::find_lis(std::vector<int>({2, 1, 4, 3, 6, 5, 8, 7, 10}));
    // then
    EXPECT_EQ(std::vector<int>({1, 3, 5, 7, 10}), result);
}

TEST(LongestIncreasingSubsequenceTest, findLis_WhenSearchInMiddle_ThenLeastLexicographically)
{
    // when
    std::vector<int> result = alse::find_lis(std::vector<int>({0, 2, 4, 6, 8, 3, 5, 7, 8}));
    // then
    EXPECT_EQ(std::vector<int>({0, 2, 3, 5, 7, 8}), result);
}

TEST(LongestIncreasingSubsequenceTest,
     findLis_WhenIncreasingAndReversedComparator_ThenLastElementOnly)
{
    // when
    std::vector<int> result =
            alse::find_lis<int, std::greater<int>>(std::vector<int>({1, 3, 5, 7, 9, 11, 13, 15}));
    // then
    EXPECT_EQ(std::vector<int>({15}), result);
}

TEST(LongestIncreasingSubsequenceTest, findLis_WhenDecreasingAndReversedComparator_ThenAllElements)
{
    // given
    std::vector<int> sequence = {12, 10, 8, 6, 4, 2};
    // when
    std::vector<int> result = alse::find_lis<int, std::greater<int>>(sequence);
    // then
    EXPECT_EQ(sequence, result);
}
