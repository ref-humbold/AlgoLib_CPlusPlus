/**!
 * \file maths_test.cpp
 * \brief Tests: Algorithms for basic mathematical computations
 */
#include <gtest/gtest.h>
#include "algolib/mathmat/maths.hpp"

namespace alma = algolib::mathmat;

#pragma region gcd

TEST(MathsTest, gcd_WhenNumbersAreComposite_ThenGCD)
{
    // when
    int result = alma::gcd(161, 46);
    // then
    EXPECT_EQ(23, result);
}

TEST(MathsTest, gcd_WhenNumbersArePrime_ThenOne)
{
    // when
    int result = alma::gcd(127, 41);
    // then
    EXPECT_EQ(1, result);
}

TEST(MathsTest, gcd_WhenNumbersAreMutuayPrime_ThenOne)
{
    // when
    int result = alma::gcd(119, 57);
    // then
    EXPECT_EQ(1, result);
}

TEST(MathsTest, gcd_WhenOneNumberIsMultipleOfAnother_ThenLessNumber)
{
    // given
    int number = 34;
    // when
    int result = alma::gcd(272, number);
    // then
    EXPECT_EQ(number, result);
}

TEST(MathsTest, gcd_WhenOneNumberIsZero_ThenAnotherNumber)
{
    // given
    int number1 = 96;
    // when
    int result = alma::gcd(number1, 0);
    // then
    EXPECT_EQ(number1, result);
}

#pragma endregion
#pragma region lcm

TEST(MathsTest, lcm_WhenNumbersAreComposite_ThenLCM)
{
    // when
    int result = alma::lcm(161, 46);
    // then
    EXPECT_EQ(322, result);
}

TEST(MathsTest, lcm_WhenNumbersArePrime_ThenProduct)
{
    // when
    int result = alma::lcm(127, 41);
    // then
    EXPECT_EQ(5207, result);
}

TEST(MathsTest, lcm_WhenNumbersAreMutuayPrime_ThenProduct)
{
    // when
    int result = alma::lcm(119, 57);
    // then
    EXPECT_EQ(6783, result);
}

TEST(MathsTest, lcm_WhenNumberIsMultipleOfNumber_ThenGreaterNumber)
{
    // given
    int number = 272;
    // when
    int result = alma::lcm(number, 34);
    // then
    EXPECT_EQ(number, result);
}

TEST(MathsTest, lcm_WhenOneNumberIsZero_ThenZero)
{
    // when
    int result = alma::lcm(96, 0);
    // then
    EXPECT_EQ(0, result);
}

#pragma endregion
#pragma region multMod

TEST(MathsTest, multMod_WhenFirstFactorIsZero_ThenZero)
{
    // when
    int result = alma::mult_mod(0, 14, 0);
    // then
    EXPECT_EQ(0, result);
}

TEST(MathsTest, multMod_WhenSecondFactorIsZero_ThenZero)
{
    // when
    int result = alma::mult_mod(14, 0, 0);
    // then
    EXPECT_EQ(0, result);
}

TEST(MathsTest, multMod_WhenFactorsAreZero_ThenZero)
{
    // when
    int result = alma::mult_mod(0, 0, 0);
    // then
    EXPECT_EQ(0, result);
}

TEST(MathsTest, multMod_WhenOneFactorIsNegativeAndAnotherIsPositive_ThenNegative)
{
    // when
    int result = alma::mult_mod(-3, 10, 0);
    // then
    EXPECT_EQ(-30, result);
}

TEST(MathsTest, multMod_WhenOneFactorIsPositiveAndAnotherIsNegative_ThenNegative)
{
    // when
    int result = alma::mult_mod(3, -10, 0);
    // then
    EXPECT_EQ(-30, result);
}

TEST(MathsTest, multMod_WhenFactorsAreNegative_ThenPositive)
{
    // when
    int result = alma::mult_mod(-3, -10, 0);
    // then
    EXPECT_EQ(30, result);
}

TEST(MathsTest, multMod_WhenModuloAndFactorsArePositive)
{
    // when
    int result = alma::mult_mod(547, 312, 10000);
    // then
    EXPECT_EQ(664, result);
}

TEST(MathsTest, multMod_WhenModuloIsPositiveAndFirstFactorIsNegative)
{
    // when
    int result = alma::mult_mod(-547, 312, 10000);
    // then
    EXPECT_EQ(9336, result);
}

TEST(MathsTest, multMod_WhenModuloIsPositiveAndSecondFactorIsNegative)
{
    // when
    int result = alma::mult_mod(547, -312, 10000);
    // then
    EXPECT_EQ(9336, result);
}

TEST(MathsTest, multMod_WhenModuloIsPositiveAndFactorsAreNegative)
{
    // when
    int result = alma::mult_mod(-547, -312, 10000);
    // then
    EXPECT_EQ(664, result);
}

TEST(MathsTest, multMod_WhenModuloIsNegative_ThenDomainError)
{
    // when
    auto exec = [&]() { alma::mult_mod(-547, -312, -10000); };
    // then
    EXPECT_THROW(exec(), std::domain_error);
}

#pragma endregion
#pragma region powerMod

TEST(MathsTest, powerMod_WhenBaseIsZero_ThenZero)
{
    // when
    int result = alma::power_mod(0, 14, 0);
    // then
    EXPECT_EQ(0, result);
}

TEST(MathsTest, powerMod_WhenExponentIsZero_ThenOne)
{
    // when
    int result = alma::power_mod(14, 0, 0);
    // then
    EXPECT_EQ(1, result);
}

TEST(MathsTest, powerMod_WhenBaseAndExponentAreZero_ThenDomainError)
{
    // when
    auto exec = [&]() { return alma::power_mod(0, 0, 0); };
    // then
    EXPECT_THROW(exec(), std::domain_error);
}

TEST(MathsTest, powerMod_WhenBaseAndExponentArePositive)
{
    // when
    int result = alma::power_mod(3, 10, 0);
    // then
    EXPECT_EQ(59049, result);
}

TEST(MathsTest, powerMod_WhenBaseIsNegativeAndExponentIsEven)
{
    // when
    int result = alma::power_mod(-3, 10, 0);
    // then
    EXPECT_EQ(59049, result);
}

TEST(MathsTest, powerMod_WhenBaseIsNegativeAndExponentIsOdd)
{
    // when
    int result = alma::power_mod(-3, 9, 0);
    // then
    EXPECT_EQ(-19683, result);
}

TEST(MathsTest, powerMod_WhenExponentIsNegative_ThenDomainError)
{
    // when
    auto exec = [&]() { return alma::power_mod(-3, -10, 0); };
    // then
    EXPECT_THROW(exec(), std::domain_error);
}

TEST(MathsTest, powerMod_WhenModuloAndBaseArePositive)
{
    // when
    int result = alma::power_mod(5, 11, 10000);
    // then
    EXPECT_EQ(8125, result);
}

TEST(MathsTest, powerMod_WhenModuloIsPositiveAndBaseIsNegative)
{
    // when
    int result = alma::power_mod(-5, 11, 10000);
    // then
    EXPECT_EQ(1875, result);
}

TEST(MathsTest, powerMod_WhenModuloIsNegative_ThenDomainError)
{
    // then
    auto exec = [&]() { return alma::power_mod(-5, 11, -10000); };
    // then
    EXPECT_THROW(exec(), std::domain_error);
}

#pragma endregion
