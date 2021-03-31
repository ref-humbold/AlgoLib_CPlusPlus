/**!
 * \file fraction_test.cpp
 * \brief Tests: Structure of fraction
 */
#include <gtest/gtest.h>
#include "algolib/mathmat/fraction.hpp"

namespace alma = algolib::mathmat;

TEST(FractionTest, inverse_WhenPositive)
{
    // given
    alma::fraction frac(7, 19);
    // when
    alma::fraction result = ~frac;
    // then
    EXPECT_EQ(alma::fraction(19, 7), result);
}

TEST(FractionTest, inverse_WhenNegative)
{
    // given
    alma::fraction frac(-7, 19);
    // when
    alma::fraction result = ~frac;
    // then
    EXPECT_EQ(alma::fraction(-19, 7), result);
}

TEST(FractionTest, inverse_WhenZero_ThenThrowsDomainError)
{
    // given
    alma::fraction frac(0);
    // when
    auto exec = [&]() { return ~frac; };
    // then
    EXPECT_THROW(exec(), std::domain_error);
}

TEST(FractionTest, reverse_WhenPositive)
{
    // given
    alma::fraction frac(7, 19);
    // when
    alma::fraction result = -frac;
    // then
    EXPECT_EQ(alma::fraction(-7, 19), result);
}

TEST(FractionTest, reverse_WhenNegative)
{
    // given
    alma::fraction frac(-7, 19);
    // when
    alma::fraction result = -frac;
    // then
    EXPECT_EQ(alma::fraction(7, 19), result);
}

TEST(FractionTest, reverse_WhenZero_ThenZero)
{
    // given
    alma::fraction frac(0);
    // when
    alma::fraction result = -frac;
    // then
    EXPECT_EQ(alma::fraction(0), result);
}

TEST(FractionTest, convertToDouble)
{
    // given
    alma::fraction frac(-129, 20);
    // when
    double result = static_cast<double>(frac);
    // then
    EXPECT_EQ(-6.45, result);
}

TEST(FractionTest, convertToInt)
{
    // given
    alma::fraction frac(-129, 20);
    // when
    int result = static_cast<int>(frac);
    // then
    EXPECT_EQ(-6, result);
}

TEST(FractionTest, hash_WhenFraction_ThenXor)
{
    // given
    alma::fraction frac(-129, 20);
    // when
    size_t result = std::hash<alma::fraction>()(frac);
    // then
    EXPECT_EQ(-129 ^ 20, result);
}
