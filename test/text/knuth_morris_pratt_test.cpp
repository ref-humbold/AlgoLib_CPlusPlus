/*!
 * \file knuth_morris_pratt_test.cpp
 * \brief Tests: Knuth-Morris-Pratt algorithm for pattern searching.
 */
#include <gtest/gtest.h>
#include "algolib/text/knuth_morris_pratt.hpp"

namespace alte = algolib::text;

TEST(KnuthMorrisPrattTest, kmpSearch_WhenPatternFoundOnce_ThenSingleOccurrence)
{
    // when
    std::vector<size_t> result = alte::kmp_search("abcde", "a");
    // then
    EXPECT_EQ(std::vector<size_t>({0}), result);
}

TEST(KnuthMorrisPrattTest, kmpSearch_WhenPatternFoundTwice_ThenTwoOccurrences)
{
    // when
    std::vector<size_t> result = alte::kmp_search("abcdae", "a");
    // then
    EXPECT_EQ(std::vector<size_t>({0, 4}), result);
}

TEST(KnuthMorrisPrattTest, kmpSearch_WhenPatternFoundTwiceAndIntersects_ThenTwoOccurrences)
{
    // when
    std::vector<size_t> result = alte::kmp_search("aaabcde", "aa");
    // then
    EXPECT_EQ(std::vector<size_t>({0, 1}), result);
}

TEST(KnuthMorrisPrattTest, kmpSearch_WhenPatternNotFound_ThenEmpty)
{
    // when
    std::vector<size_t> result = alte::kmp_search("abcde", "x");
    // then
    EXPECT_EQ(std::vector<size_t>(), result);
}

TEST(KnuthMorrisPrattTest, kmpSearch_WhenPatternIsEmptyString_ThenEmpty)
{
    // when
    std::vector<size_t> result = alte::kmp_search("abcde", "");
    // then
    EXPECT_EQ(std::vector<size_t>(), result);
}

TEST(KnuthMorrisPrattTest, kmpSearch_WhenTextIsEmptyString_ThenEmpty)
{
    // when
    std::vector<size_t> result = alte::kmp_search("", "a");
    // then
    EXPECT_EQ(std::vector<size_t>(), result);
}
