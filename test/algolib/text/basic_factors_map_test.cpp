/*!
 * \file basic_factors_map_test.cpp
 * \brief Tests: Structure of basic factors map using Karp-Miller-Rosenberg algorithm.
 */
#include <gtest/gtest.h>
#include "algolib/text/basic_factors_map.hpp"

namespace alte = algolib::text;

class BasicFactorsMapTest : public ::testing::Test
{
protected:
    alte::basic_factors_map test_object;

public:
    BasicFactorsMapTest() : test_object{alte::basic_factors_map("mississippi")}
    {
    }

    ~BasicFactorsMapTest() override = default;
};

TEST_F(BasicFactorsMapTest, code_WhenSingleCharacter_ThenCode)
{
    // when
    alte::basic_factors_map::code_t result1 = test_object.code(1, 1);
    alte::basic_factors_map::code_t result2 = test_object.code(0, 1);
    alte::basic_factors_map::code_t result3 = test_object.code(8, 1);
    alte::basic_factors_map::code_t result4 = test_object.code(3, 1);
    // then
    EXPECT_EQ(std::make_pair(1UL, 0UL), result1);
    EXPECT_EQ(std::make_pair(2UL, 0UL), result2);
    EXPECT_EQ(std::make_pair(3UL, 0UL), result3);
    EXPECT_EQ(std::make_pair(4UL, 0UL), result4);
}

TEST_F(BasicFactorsMapTest, code_WhenBaseWord_ThenCode)
{
    // when
    alte::basic_factors_map::code_t result1 = test_object.code(0, 1);
    alte::basic_factors_map::code_t result2 = test_object.code(4, 2);
    alte::basic_factors_map::code_t result3 = test_object.code(8, 2);
    alte::basic_factors_map::code_t result4 = test_object.code(7);
    alte::basic_factors_map::code_t result5 = test_object.code(3, 4);
    // then
    EXPECT_EQ(std::make_pair(2UL, 0UL), result1);
    EXPECT_EQ(std::make_pair(6UL, 0UL), result2);
    EXPECT_EQ(std::make_pair(9UL, 0UL), result3);
    EXPECT_EQ(std::make_pair(12UL, 0UL), result4);
    EXPECT_EQ(std::make_pair(16UL, 0UL), result5);
}

TEST_F(BasicFactorsMapTest, code_WhenComposedWord_ThenCode)
{
    // when
    alte::basic_factors_map::code_t result1 = test_object.code(0, 3);
    alte::basic_factors_map::code_t result2 = test_object.code(0);
    // then
    EXPECT_EQ(std::make_pair(7UL, 6UL), result1);
    EXPECT_EQ(std::make_pair(20UL, 21UL), result2);
}

TEST_F(BasicFactorsMapTest, code_WhenLengthIsZero_ThenInvalidArgument)
{
    // when
    auto exec = [&]() { return test_object.code(4, 0); };

    // then
    EXPECT_THROW(exec(), std::invalid_argument);
}

TEST_F(BasicFactorsMapTest, code_WhenInvalidStartIndex_ThenOutOfRange)
{
    // when
    auto exec = [&]() { return test_object.code(22, 1); };

    // then
    EXPECT_THROW(exec(), std::out_of_range);
}

TEST_F(BasicFactorsMapTest, code_WhenInvalidLength_ThenOutOfRange)
{
    // when
    auto exec = [&]() { return test_object.code(4, 20); };

    // then
    EXPECT_THROW(exec(), std::out_of_range);
}
