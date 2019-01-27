// TESTS FOR SUFFIX ARRAY STRUCTURE
#include <gtest/gtest.h>
#include "algolib/text/suffix_array.hpp"

namespace alte = algolib::text;

class SuffixArrayTest : public ::testing::Test
{
protected:
    alte::suffix_array test_object;

public:
    SuffixArrayTest() : test_object{alte::suffix_array("mississippi")}
    {
    }

    virtual ~SuffixArrayTest()
    {
    }
};

TEST_F(SuffixArrayTest, testSize)
{
    size_t result = test_object.size();

    EXPECT_EQ(11, result);
}

TEST_F(SuffixArrayTest, testOperatorIndex)
{
    std::string result0 = test_object[0];
    std::string result1 = test_object[3];
    std::string result2 = test_object[6];
    std::string result3 = test_object[9];

    EXPECT_EQ("i", result0);
    EXPECT_EQ("ississippi", result1);
    EXPECT_EQ("ppi", result2);
    EXPECT_EQ("ssippi", result3);
}

TEST_F(SuffixArrayTest, testAt)
{
    std::string result0 = test_object.at(0);
    std::string result1 = test_object.at(3);
    std::string result2 = test_object.at(6);
    std::string result3 = test_object.at(9);

    EXPECT_EQ("i", result0);
    EXPECT_EQ("ississippi", result1);
    EXPECT_EQ("ppi", result2);
    EXPECT_EQ("ssippi", result3);
}

TEST_F(SuffixArrayTest, testAtWhenOutOfRange)
{
    EXPECT_THROW(test_object.at(20), std::out_of_range);
}

TEST_F(SuffixArrayTest, testIndexAt)
{
    size_t result0 = test_object.index_at(0);
    size_t result1 = test_object.index_at(3);
    size_t result2 = test_object.index_at(6);
    size_t result3 = test_object.index_at(9);

    EXPECT_EQ(10, result0);
    EXPECT_EQ(1, result1);
    EXPECT_EQ(8, result2);
    EXPECT_EQ(5, result3);
}

TEST_F(SuffixArrayTest, testIndexAtWhenOutOfRange)
{
    EXPECT_THROW(test_object.index_at(20), std::out_of_range);
}

TEST_F(SuffixArrayTest, testIndexOf)
{
    size_t result0 = test_object.index_of(0);
    size_t result1 = test_object.index_of(3);
    size_t result2 = test_object.index_of(6);
    size_t result3 = test_object.index_of(9);

    EXPECT_EQ(4, result0);
    EXPECT_EQ(8, result1);
    EXPECT_EQ(7, result2);
    EXPECT_EQ(5, result3);
}

TEST_F(SuffixArrayTest, testIndexWhenOutOfRange)
{
    EXPECT_THROW(test_object.index_of(20), std::out_of_range);
}

TEST_F(SuffixArrayTest, testLCPWhenSameSuffix)
{
    size_t result = test_object.lcp(4, 4);

    EXPECT_EQ(7, result);
}

TEST_F(SuffixArrayTest, testLCPWhenDifferentSuffix1)
{
    size_t result = test_object.lcp(1, 10);

    EXPECT_EQ(1, result);
}

TEST_F(SuffixArrayTest, testLCPWhenDifferentSuffix2)
{
    size_t result = test_object.lcp(9, 6);

    EXPECT_EQ(0, result);
}

TEST_F(SuffixArrayTest, testLCPWhenSwapSuffix)
{
    size_t result0 = test_object.lcp(2, 5);
    size_t result1 = test_object.lcp(5, 2);

    ASSERT_EQ(3, result0);
    EXPECT_EQ(result0, result1);
}
