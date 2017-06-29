#include <gtest/gtest.h>
#include "../algolib/kmp.hpp"

TEST(KMPTest, testKMPWhenPatternFoundOnce)
{
    std::string text = "abcde";
    std::string pattern = "a";

    std::vector<size_t> result = algolib::kmp(text, pattern);

    ASSERT_EQ(std::vector<size_t>({0}), result);
}

TEST(KMPTest, testKMPWhenPatternFoundTwice)
{
    std::string text = "abcdae";
    std::string pattern = "a";

    std::vector<size_t> result = algolib::kmp(text, pattern);

    ASSERT_EQ(std::vector<size_t>({0, 4}), result);
}

TEST(KMPTest, testKMPWhenPatternFoundTwiceAndIntersects)
{
    std::string text = "aaabcde";
    std::string pattern = "aa";

    std::vector<size_t> result = algolib::kmp(text, pattern);

    ASSERT_EQ(std::vector<size_t>({0, 1}), result);
}

TEST(KMPTest, testKMPWhenPatternNotFound)
{
    std::string text = "abcde";
    std::string pattern = "x";

    std::vector<size_t> result = algolib::kmp(text, pattern);

    ASSERT_EQ(std::vector<size_t>(), result);
}

TEST(KMPTest, testKMPWhenPatternIsEmptyString)
{
    std::string text = "abcde";
    std::string pattern = "";

    std::vector<size_t> result = algolib::kmp(text, pattern);

    ASSERT_EQ(std::vector<size_t>(), result);
}

TEST(KMPTest, testKMPWhenTextIsEmptyString)
{
    std::string text = "";
    std::string pattern = "a";

    std::vector<size_t> result = algolib::kmp(text, pattern);

    ASSERT_EQ(std::vector<size_t>(), result);
}
