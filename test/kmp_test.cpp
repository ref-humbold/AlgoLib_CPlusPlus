//! TESTY DLA ALGORYTMU KNUTHA-MORRISA-PRATTA
#include <gtest/gtest.h>
#include "algolib/text/kmp.hpp"

namespace alte = algolib::text;

TEST(KMPTest, kmp_whenPatternFoundOnce)
{
    std::string text = "abcde";
    std::string pattern = "a";

    std::vector<size_t> result = alte::kmp(text, pattern);

    EXPECT_EQ(std::vector<size_t>({0}), result);
}

TEST(KMPTest, kmp_whenPatternFoundTwice)
{
    std::string text = "abcdae";
    std::string pattern = "a";

    std::vector<size_t> result = alte::kmp(text, pattern);

    EXPECT_EQ(std::vector<size_t>({0, 4}), result);
}

TEST(KMPTest, kmp_whenPatternFoundTwiceAndIntersects)
{
    std::string text = "aaabcde";
    std::string pattern = "aa";

    std::vector<size_t> result = alte::kmp(text, pattern);

    EXPECT_EQ(std::vector<size_t>({0, 1}), result);
}

TEST(KMPTest, kmp_whenPatternNotFound)
{
    std::string text = "abcde";
    std::string pattern = "x";

    std::vector<size_t> result = alte::kmp(text, pattern);

    EXPECT_EQ(std::vector<size_t>(), result);
}

TEST(KMPTest, kmp_whenPatternIsEmptyString)
{
    std::string text = "abcde";
    std::string pattern = "";

    std::vector<size_t> result = alte::kmp(text, pattern);

    EXPECT_EQ(std::vector<size_t>(), result);
}

TEST(KMPTest, kmp_whenTextIsEmptyString)
{
    std::string text = "";
    std::string pattern = "a";

    std::vector<size_t> result = alte::kmp(text, pattern);

    EXPECT_EQ(std::vector<size_t>(), result);
}
