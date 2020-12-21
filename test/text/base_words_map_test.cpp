/*!
 * \file base_words_map_tests.cpp
 * \brief Tests: Structure of base words map using Karp-Miller-Rosenberg algorithm
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

TEST_F(BaseWordsMapTest, code_whenEmpty_thenZeroAndZero)
{
    // when
    std::pair<size_t, size_t> result = test_object.code(4, 0);
    // then
    EXPECT_EQ(std::make_pair(0UL, 0UL), result);
}

TEST_F(BaseWordsMapTest, code_whenSingleCharacter_thenCodeAndZero)
{
    // when
    std::pair<size_t, size_t> result1 = test_object.code(1, 1);  // i
    std::pair<size_t, size_t> result2 = test_object.code(0, 1);  // m
    std::pair<size_t, size_t> result3 = test_object.code(8, 1);  // p
    std::pair<size_t, size_t> result4 = test_object.code(3, 1);  // s
    // then
    EXPECT_EQ(std::make_pair(1UL, 0UL), result1);
    EXPECT_EQ(std::make_pair(2UL, 0UL), result2);
    EXPECT_EQ(std::make_pair(3UL, 0UL), result3);
    EXPECT_EQ(std::make_pair(4UL, 0UL), result4);
}

TEST_F(BaseWordsMapTest, code_whenBaseWord_thenCodeAndZero)
{
    // when
    std::pair<size_t, size_t> result1 = test_object.code(0, 1);  // m
    std::pair<size_t, size_t> result2 = test_object.code(4, 2);  // is
    std::pair<size_t, size_t> result3 = test_object.code(8, 2);  // pp
    std::pair<size_t, size_t> result4 = test_object.code(7);  // ippi
    std::pair<size_t, size_t> result5 = test_object.code(3, 4);  // siss
    // then
    EXPECT_EQ(std::make_pair(2UL, 0UL), result1);
    EXPECT_EQ(std::make_pair(6UL, 0UL), result2);
    EXPECT_EQ(std::make_pair(9UL, 0UL), result3);
    EXPECT_EQ(std::make_pair(12UL, 0UL), result4);
    EXPECT_EQ(std::make_pair(16UL, 0UL), result5);
}

TEST_F(BaseWordsMapTest, code_whenComposedWord_thenCodeAndCode)
{
    // when
    std::pair<size_t, size_t> result1 = test_object.code(0, 3);  // mis
    std::pair<size_t, size_t> result2 = test_object.code(0);  // mississippi
    // then
    EXPECT_EQ(std::make_pair(7UL, 6UL), result1);
    EXPECT_EQ(std::make_pair(20UL, 21UL), result2);
}
