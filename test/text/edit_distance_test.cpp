/**!
 * \file edit distance.cpp
 * \brief Tests: Algorithms for edit distance
 */
#include <gtest/gtest.h>
#include "algolib/text/edit_distance.hpp"

namespace alte = algolib::text;

const double offset = 1e-6;

#pragma region count_levenshtein

TEST(EditDistanceTest, countLevenshtein_WhenSameText_ThenZero)
{
    // given
    std::string text = "qwertyuiop";
    // when
    double result = alte::count_levenshtein(text, text);
    // then
    EXPECT_EQ(0.0, result);
}

TEST(EditDistanceTest, countLevenshtein_WhenEmptySource_ThenSumOfInsertions)
{
    // given
    std::string text = "qwertyuiop";
    double insertionCost = 2.0;
    // when
    double result = alte::count_levenshtein("", text, insertionCost, 1.0, 1.0);
    // then
    EXPECT_NEAR(text.size() * insertionCost, result, offset);
}

TEST(EditDistanceTest, countLevenshtein_WhenEmptyDestination_ThenSumOfDeletions)
{
    // given
    std::string text = "qwertyuiop";
    double deletionCost = 2.0;
    // when
    double result = alte::count_levenshtein(text, "", 1.0, deletionCost, 1.0);
    // then
    EXPECT_NEAR(text.length() * deletionCost, result, offset);
}

TEST(EditDistanceTest, countLevenshtein_WhenNegativeCost_ThenInvalidArgument)
{
    // when
    auto exec = [&]() { return alte::count_levenshtein("a", "b", 1.0, 1.0, -1.0); };
    // then
    EXPECT_THROW(exec(), std::invalid_argument);
}

#pragma endregion
#pragma region count_lcs

TEST(EditDistanceTest, countLcs_WhenSameText_ThenZero)
{
    // given
    std::string text = "qwertyuiop";
    // when
    double result = alte::count_lcs(text, text);
    // then
    EXPECT_EQ(0.0, result);
}

TEST(EditDistanceTest, countLcs_WhenEmptySource_ThenSumOfInsertions)
{
    // given
    std::string text = "qwertyuiop";
    double insertionCost = 2.0;
    // when
    double result = alte::count_lcs("", text, insertionCost, 1.0);
    // then
    EXPECT_NEAR(text.size() * insertionCost, result, offset);
}

TEST(EditDistanceTest, countLcs_WhenEmptyDestination_ThenSumOfDeletions)
{
    // given
    std::string text = "qwertyuiop";
    double deletionCost = 2.0;
    // when
    double result = alte::count_lcs(text, "", 1.0, deletionCost);
    // then
    EXPECT_NEAR(text.length() * deletionCost, result, offset);
}

TEST(EditDistanceTest, countLcs_WhenNegativeCost_ThenInvalidArgument)
{
    // when
    auto exec = [&]() { return alte::count_lcs("a", "b", 1.0, -1.0); };
    // then
    EXPECT_THROW(exec(), std::invalid_argument);
}

#pragma endregion
#pragma region count_hamming

TEST(EditDistanceTest, countHamming_WhenSameText_ThenZero)
{
    // given
    std::string text = "qwertyuiop";
    // when
    double result = alte::count_hamming(text, text);
    // then
    EXPECT_EQ(0.0, result);
}

TEST(EditDistanceTest, countHamming_WhenEmpty_ThenZero)
{
    // when
    double result = alte::count_hamming("", "");
    // then
    EXPECT_EQ(0.0, result);
}

TEST(EditDistanceTest, countHamming_WhenDifferentLength_ThenInvalidArgument)
{
    // when
    auto exec = [&]() { return alte::count_hamming("qwerty", "asdf"); };
    // then
    EXPECT_THROW(exec(), std::invalid_argument);
}

TEST(EditDistanceTest, countHamming_WhenNegativeCost_ThenInvalidArgument)
{
    // when
    auto exec = [&]() { return alte::count_hamming("a", "b", -1.0); };
    // then
    EXPECT_THROW(exec(), std::invalid_argument);
}
