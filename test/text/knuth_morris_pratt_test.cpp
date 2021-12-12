/*!
 * \file knuth_morris_pratt_test.cpp
 * \brief Tests: Knuth-Morris-Pratt algorithm for pattern searching
 */
#include <gtest/gtest.h>
#include "algolib/text/knuth_morris_pratt.hpp"

namespace alte = algolib::text;

TEST(KMPTest, kmp_WhenPatternFoundOnce_ThenSingleOccurrence)
{
    // when
    std::vector<size_t> result = alte::kmp("abcde", "a");
    // then
    EXPECT_EQ(std::vector<size_t>({0}), result);
}

TEST(KMPTest, kmp_WhenPatternFoundTwice_ThenTwoOccurrences)
{
    // when
    std::vector<size_t> result = alte::kmp("abcdae", "a");
    // then
    EXPECT_EQ(std::vector<size_t>({0, 4}), result);
}

TEST(KMPTest, kmp_WhenPatternFoundTwiceAndIntersects_ThenTwoOccurrences)
{
    // when
    std::vector<size_t> result = alte::kmp("aaabcde", "aa");
    // then
    EXPECT_EQ(std::vector<size_t>({0, 1}), result);
}

TEST(KMPTest, kmp_WhenPatternNotFound_ThenEmpty)
{
    // when
    std::vector<size_t> result = alte::kmp("abcde", "x");
    // then
    EXPECT_EQ(std::vector<size_t>(), result);
}

TEST(KMPTest, kmp_WhenPatternIsEmptyString_ThenEmpty)
{
    // when
    std::vector<size_t> result = alte::kmp("abcde", "");
    // then
    EXPECT_EQ(std::vector<size_t>(), result);
}

TEST(KMPTest, kmp_WhenTextIsEmptyString_ThenEmpty)
{
    // when
    std::vector<size_t> result = alte::kmp("", "a");
    // then
    EXPECT_EQ(std::vector<size_t>(), result);
}
