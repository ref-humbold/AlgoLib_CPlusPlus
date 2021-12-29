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
    EXPECT_NEAR(0.0, result, offset);
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

#pragma endregion

#pragma region count_lcs

TEST(EditDistanceTest, countLCS_WhenSameText_ThenZero)
{
    // given
    std::string text = "qwertyuiop";
    // when
    double result = alte::count_lcs(text, text);
    // then
    EXPECT_NEAR(0.0, result, offset);
}

TEST(EditDistanceTest, countLCS_WhenEmptySource_ThenSumOfInsertions)
{
    // given
    std::string text = "qwertyuiop";
    double insertionCost = 2.0;
    // when
    double result = alte::count_lcs("", text, insertionCost, 1.0);
    // then
    EXPECT_NEAR(text.size() * insertionCost, result, offset);
}

TEST(EditDistanceTest, countLCS_WhenEmptyDestination_ThenSumOfDeletions)
{
    // given
    std::string text = "qwertyuiop";
    double deletionCost = 2.0;
    // when
    double result = alte::count_lcs(text, "", 1.0, deletionCost);
    // then
    EXPECT_NEAR(text.length() * deletionCost, result, offset);
}

#pragma endregion
