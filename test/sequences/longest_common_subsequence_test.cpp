/*!
 * \file longest_common_subsequence_test.cpp
 * \brief Tests: Algorithm for longest common subsequence
 */
#include <gtest/gtest.h>
#include "algolib/sequences/longest_common_subsequence.hpp"

using namespace std::string_literals;

namespace alse = algolib::sequences;

std::vector<int> codes(const std::string & text)
{
    std::vector<int> sequence;

    std::transform(text.begin(), text.end(), std::back_inserter(sequence),
                   [](const char c) { return +c; });
    return sequence;
}

TEST(LongestCommonSubsequenceTest, countLCSLength_WhenEmpty_ThenZero)
{
    // when
    size_t result = alse::count_lcs_length("qwertyuiop", "");
    // then
    EXPECT_EQ(0, result);
}

TEST(LongestCommonSubsequenceTest, countLcsLength_WhenRepeatedSingleElement_ThenOne)
{
    // when
    size_t result = alse::count_lcs_length("abcde", "eeee");
    // then
    EXPECT_EQ(1, result);
}

TEST(LongestCommonSubsequenceTest, countLcsLength_WhenSameText_ThenTextLength)
{
    // given
    std::string text = "qwertyuiop";
    // when
    size_t result = alse::count_lcs_length(text, text);
    // then
    EXPECT_EQ(text.size(), result);
}

TEST(LongestCommonSubsequenceTest, countLcsLength_WhenSubtext_ThenSubtextLength)
{
    // when
    size_t result = alse::count_lcs_length("qwertyuiop", "zxqwertyasdfuiopcvb");
    // then
    EXPECT_EQ("qwertyuiop"s.size(), result);
}

TEST(LongestCommonSubsequenceTest, countLcsLength_WhenDifferent_ThenZero)
{
    // when
    size_t result = alse::count_lcs_length("qwertyuiop", "asdfghjkl");
    // then
    EXPECT_EQ(0, result);
}

TEST(LongestCommonSubsequenceTest, countLcsLength_WhenCommonSubtext_ThenCommonSubtextLength)
{
    // when
    size_t result = alse::count_lcs_length("qwertyuiop", "zxrtyasdfuiopcvb");
    // then
    EXPECT_EQ("rtyuiop"s.size(), result);
}

TEST(LongestCommonSubsequenceTest, countLcsLength_WhenSameSequence_ThenSequenceLength)
{
    // given
    std::vector<int> sequence = codes("qwertyuiop");
    // when
    size_t result = alse::count_lcs_length(sequence, sequence);
    // then
    EXPECT_EQ(sequence.size(), result);
}

TEST(LongestCommonSubsequenceTest, countLcsLength_WhenCommonSubsequence_ThenCommonSubsequenceLength)
{
    // when
    size_t result = alse::count_lcs_length(codes("qwertyuiop"), codes("zxrtyasdfuiopcvb"));
    // then
    EXPECT_EQ("rtyuiop"s.size(), result);
}
