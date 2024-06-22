/*!
 * \file base_words_map_tests.cpp
 * \brief Tests: Structure of base words map using Karp-Miller-Rosenberg algorithm.
 */
#include <gtest/gtest.h>
#include "algolib/text/base_words_map.hpp"

namespace alte = algolib::text;

class BaseWordsMapTest : public ::testing::Test
{
protected:
    alte::base_words_map test_object;

public:
    BaseWordsMapTest() : test_object{alte::base_words_map("mississippi")}
    {
    }

    ~BaseWordsMapTest() override = default;
};

TEST_F(BaseWordsMapTest, code_WhenEmpty_ThenZeroAndZero)
{
    // when
    alte::base_words_map::code_t result = test_object.code(4, 0);

    // then
    EXPECT_EQ(std::make_pair(0UL, 0UL), result);
}

TEST_F(BaseWordsMapTest, code_WhenSingleCharacter_ThenCodeAndZero)
{
    // when
    alte::base_words_map::code_t result1 = test_object.code(1, 1);  // i
    alte::base_words_map::code_t result2 = test_object.code(0, 1);  // m
    alte::base_words_map::code_t result3 = test_object.code(8, 1);  // p
    alte::base_words_map::code_t result4 = test_object.code(3, 1);  // s
    // then
    EXPECT_EQ(std::make_pair(1UL, 0UL), result1);
    EXPECT_EQ(std::make_pair(2UL, 0UL), result2);
    EXPECT_EQ(std::make_pair(3UL, 0UL), result3);
    EXPECT_EQ(std::make_pair(4UL, 0UL), result4);
}

TEST_F(BaseWordsMapTest, code_WhenBaseWord_ThenCodeAndZero)
{
    // when
    alte::base_words_map::code_t result1 = test_object.code(0, 1);  // m
    alte::base_words_map::code_t result2 = test_object.code(4, 2);  // is
    alte::base_words_map::code_t result3 = test_object.code(8, 2);  // pp
    alte::base_words_map::code_t result4 = test_object.code(7, 8);  // ippi
    alte::base_words_map::code_t result5 = test_object.code(3, 4);  // siss
    // then
    EXPECT_EQ(std::make_pair(2UL, 0UL), result1);
    EXPECT_EQ(std::make_pair(6UL, 0UL), result2);
    EXPECT_EQ(std::make_pair(9UL, 0UL), result3);
    EXPECT_EQ(std::make_pair(12UL, 0UL), result4);
    EXPECT_EQ(std::make_pair(16UL, 0UL), result5);
}

TEST_F(BaseWordsMapTest, code_WhenComposedWord_ThenCodeAndCode)
{
    // when
    alte::base_words_map::code_t result1 = test_object.code(0, 3);  // mis
    alte::base_words_map::code_t result2 = test_object.code(0);  // mississippi
    // then
    EXPECT_EQ(std::make_pair(7UL, 6UL), result1);
    EXPECT_EQ(std::make_pair(20UL, 21UL), result2);
}

TEST_F(BaseWordsMapTest, code_WhenStartExceedsLength_ThenOutOfRange)
{
    // when
    auto exec = [&]() { return test_object.code(20, 1); };

    // then
    EXPECT_THROW(exec(), std::out_of_range);
}
