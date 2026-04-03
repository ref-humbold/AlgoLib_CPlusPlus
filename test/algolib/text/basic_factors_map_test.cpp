/*!
 * \file basic_factors_map_test.cpp
 * \brief Tests: Structure of basic factors map using Karp-Miller-Rosenberg algorithm.
 */
#include <gtest/gtest.h>
#include "algolib/text/basic_factors_map.hpp"

namespace alte = algolib::text;

struct RangeParams
{
    RangeParams(int start, int length) : start{start}, length{length}
    {
    }

    RangeParams(int start) : start{start}, length{std::nullopt}
    {
    }

    const int start;
    const std::optional<int> length;
};

struct RangeExpectedParams : public RangeParams
{
    RangeExpectedParams(int start, int length, const alte::basic_factors_map::code_t & expected)
        : RangeParams(start, length), expected{expected}
    {
    }

    RangeExpectedParams(int start, const alte::basic_factors_map::code_t & expected)
        : RangeParams(start), expected{expected}
    {
    }

    const alte::basic_factors_map::code_t expected;
};

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

class BasicFactorsMapTest_ValidRange : public BasicFactorsMapTest,
                                       public testing::WithParamInterface<RangeExpectedParams>
{
};

INSTANTIATE_TEST_SUITE_P(
        ,
        BasicFactorsMapTest_ValidRange,
        testing::Values(
                RangeExpectedParams(1, 1, std::make_pair(1UL, 0UL)),
                RangeExpectedParams(0, 1, std::make_pair(2UL, 0UL)),
                RangeExpectedParams(8, 1, std::make_pair(3UL, 0UL)),
                RangeExpectedParams(3, 1, std::make_pair(4UL, 0UL)),
                RangeExpectedParams(4, 2, std::make_pair(6UL, 0UL)),
                RangeExpectedParams(8, 2, std::make_pair(9UL, 0UL)),
                RangeExpectedParams(7, std::make_pair(12UL, 0UL)),
                RangeExpectedParams(3, 4, std::make_pair(16UL, 0UL)),
                RangeExpectedParams(0, 3, std::make_pair(7UL, 6UL)),
                RangeExpectedParams(0, std::make_pair(20UL, 21UL))));

class BasicFactorsMapTest_InvalidRange : public BasicFactorsMapTest,
                                         public testing::WithParamInterface<RangeParams>
{
};

INSTANTIATE_TEST_SUITE_P(
        ,
        BasicFactorsMapTest_InvalidRange,
        testing::Values(RangeParams(22), RangeParams(18, 10), RangeParams(4, 20)));

TEST_P(BasicFactorsMapTest_ValidRange, code_WhenValidRange_ThenCode)
{
    // given
    auto params = GetParam();

    // when
    alte::basic_factors_map::code_t result =
            params.length.has_value() ? test_object.code(params.start, *params.length)
                                      : test_object.code(params.start);

    // then
    EXPECT_EQ(params.expected, result);
}

TEST_F(BasicFactorsMapTest, code_WhenLengthIsZero_ThenInvalidArgument)
{
    // when
    auto exec = [&]() { return test_object.code(4, 0); };

    // then
    EXPECT_THROW(exec(), std::invalid_argument);
}

TEST_P(BasicFactorsMapTest_InvalidRange, code_WhenInvalidRange_ThenOutOfRange)
{
    // given
    auto params = GetParam();

    // when
    auto exec = [&]()
    {
        return params.length.has_value() ? test_object.code(params.start, *params.length)
                                         : test_object.code(params.start);
    };

    // then
    EXPECT_THROW(exec(), std::out_of_range);
}
