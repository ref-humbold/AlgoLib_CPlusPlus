/**!
 * \file fraction_test.cpp
 * \brief Tests: Structure of fraction
 */
#include <sstream>
#include <gtest/gtest.h>
#include "algolib/mathmat/fraction.hpp"

namespace alma = algolib::mathmat;

TEST(FractionTest, operatorDouble_ThenDoubleValue)
{
    // given
    alma::fraction frac(-129, 20);
    // when
    double result = static_cast<double>(frac);
    // then
    EXPECT_EQ(-6.45, result);
}

TEST(FractionTest, operatorInt_ThenIntegerValueRoundedTowardsZero)
{
    // given
    alma::fraction frac(-129, 20);
    // when
    int result = static_cast<int>(frac);
    // then
    EXPECT_EQ(-6, result);
}

TEST(FractionTest, operatorBool_WhenZero_ThenFalse)
{
    // given
    alma::fraction frac;
    // when
    bool result = static_cast<bool>(frac);
    // then
    EXPECT_FALSE(result);
}

TEST(FractionTest, operatorBool_WhenPositive_ThenTrue)
{
    // given
    alma::fraction frac(129, 20);
    // when
    bool result = static_cast<bool>(frac);
    // then
    EXPECT_TRUE(result);
}

TEST(FractionTest, operatorBool_WhenNegative_ThenTrue)
{
    // given
    alma::fraction frac(129, -20);
    // when
    bool result = static_cast<bool>(frac);
    // then
    EXPECT_TRUE(result);
}

TEST(FractionTest, operatorTilde_WhenPositive_ThenInversed)
{
    // given
    alma::fraction frac(7, 19);
    // when
    alma::fraction result = ~frac;
    // then
    EXPECT_EQ(alma::fraction(19, 7), result);
}

TEST(FractionTest, operatorTilde_WhenNegative_ThenInversed)
{
    // given
    alma::fraction frac(-7, 19);
    // when
    alma::fraction result = ~frac;
    // then
    EXPECT_EQ(alma::fraction(-19, 7), result);
}

TEST(FractionTest, operatorTilde_WhenZero_ThenDomainError)
{
    // given
    alma::fraction frac(0);
    // when
    auto exec = [&]() { return ~frac; };
    // then
    EXPECT_THROW(exec(), std::domain_error);
}

TEST(FractionTest, operatorUnaryPlus_ThenCopied)
{
    // given
    alma::fraction frac(7, 19);
    // when
    alma::fraction result = +frac;
    // then
    EXPECT_EQ(frac, result);
}

TEST(FractionTest, operatorUnaryMinus_WhenPositive_ThenNegative)
{
    // given
    alma::fraction frac(7, 19);
    // when
    alma::fraction result = -frac;
    // then
    EXPECT_EQ(alma::fraction(-7, 19), result);
}

TEST(FractionTest, operatorUnaryMinus_WhenNegative_ThenPositive)
{
    // given
    alma::fraction frac(-7, 19);
    // when
    alma::fraction result = -frac;
    // then
    EXPECT_EQ(alma::fraction(7, 19), result);
}

TEST(FractionTest, operatorUnaryMinus_WhenZero_ThenZero)
{
    // given
    alma::fraction frac(0);
    // when
    alma::fraction result = -frac;
    // then
    EXPECT_EQ(alma::fraction(0), result);
}

TEST(FractionTest, operatorShiftLeft_ThenStringRepresentation)
{
    // given
    alma::fraction frac(129, -20);
    std::ostringstream stream;
    // when
    stream << frac;
    // then
    EXPECT_EQ("-129/20", stream.str());
}
