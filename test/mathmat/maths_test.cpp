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
    long long result = alma::gcd(161, 46);
    // then
    EXPECT_EQ(23LL, result);
}

TEST(MathsTest, gcd_WhenNumbersArePrime_ThenOne)
{
    // when
    long long result = alma::gcd(127, 41);
    // then
    EXPECT_EQ(1LL, result);
}

TEST(MathsTest, gcd_WhenNumbersAreMutuallyPrime_ThenOne)
{
    // when
    long long result = alma::gcd(119, 57);
    // then
    EXPECT_EQ(1LL, result);
}

TEST(MathsTest, gcd_WhenOneNumberIsMultipleOfAnother_ThenLessNumber)
{
    // given
    long long number = 34LL;
    // when
    long long result = alma::gcd(272, number);
    // then
    EXPECT_EQ(number, result);
}

TEST(MathsTest, gcd_WhenOneNumberIsZero_ThenAnotherNumber)
{
    // given
    long long number1 = 96LL;
    // when
    long long result = alma::gcd(number1, 0);
    // then
    EXPECT_EQ(number1, result);
}

#pragma endregion
#pragma region lcm

TEST(MathsTest, lcm_WhenNumbersAreComposite_ThenLCM)
{
    // when
    long long result = alma::lcm(161, 46);
    // then
    EXPECT_EQ(322LL, result);
}

TEST(MathsTest, lcm_WhenNumbersArePrime_ThenProduct)
{
    // when
    long long result = alma::lcm(127, 41);
    // then
    EXPECT_EQ(5207LL, result);
}

TEST(MathsTest, lcm_WhenNumbersAreMutuallyPrime_ThenProduct)
{
    // when
    long long result = alma::lcm(119, 57);
    // then
    EXPECT_EQ(6783LL, result);
}

TEST(MathsTest, lcm_WhenNumberIsMultipleOfNumber_ThenGreaterNumber)
{
    // given
    long long number = 272LL;
    // when
    long long result = alma::lcm(number, 34);
    // then
    EXPECT_EQ(number, result);
}

TEST(MathsTest, lcm_WhenOneNumberIsZero_ThenZero)
{
    // when
    long long result = alma::lcm(96, 0);
    // then
    EXPECT_EQ(0LL, result);
}

#pragma endregion
#pragma region powerMod

TEST(MathsTest, powerMod_WhenBaseIsZero_ThenZero)
{
    // when
    long long result = alma::power_mod(0, 14, 0);
    // then
    EXPECT_EQ(0LL, result);
}

TEST(MathsTest, powerMod_WhenExponentIsZero_ThenOne)
{
    // when
    long long result = alma::power_mod(14, 0, 0);
    // then
    EXPECT_EQ(1LL, result);
}

TEST(MathsTest, powerMod_WhenBaseAndExponentAreZero_ThenThrowsDomainError)
{
    // when
    auto exec = [&]() { return alma::power_mod(0, 0, 0); };
    // then
    EXPECT_THROW(exec(), std::domain_error);
}

TEST(MathsTest, powerMod_WhenBaseAndExponentArePositive)
{
    // when
    long long result = alma::power_mod(3, 10, 0);
    // then
    EXPECT_EQ(59049LL, result);
}

TEST(MathsTest, powerMod_WhenBaseIsNegativeAndExponentIsEven)
{
    // when
    long long result = alma::power_mod(-3, 10, 0);
    // then
    EXPECT_EQ(59049LL, result);
}

TEST(MathsTest, powerMod_WhenBaseIsNegativeAndExponentIsOdd)
{
    // when
    long long result = alma::power_mod(-3, 9, 0);
    // then
    EXPECT_EQ(-19683LL, result);
}

TEST(MathsTest, powerMod_WhenExponentIsNegative_ThenThrowsDomainError)
{
    // when
    auto exec = [&]() { return alma::power_mod(-3, -10, 0); };
    // then
    EXPECT_THROW(exec(), std::domain_error);
}

TEST(MathsTest, powerMod_WhenModuloAndBaseArePositive)
{
    // when
    long long result = alma::power_mod(5, 11, 10000);
    // then
    EXPECT_EQ(8125LL, result);
}

TEST(MathsTest, powerMod_WhenModuloIsPositiveAndBaseIsNegative)
{
    // when
    long long result = alma::power_mod(-5, 11, 10000);
    // then
    EXPECT_EQ(1875LL, result);
}

#pragma endregion
#pragma region multMod

TEST(MathsTest, multMod_WhenFirstFactorIsZero_ThenZero)
{
    // when
    long long result = alma::mult_mod(0, 14, 0);
    // then
    EXPECT_EQ(0LL, result);
}

TEST(MathsTest, multMod_WhenSecondFactorIsZero_ThenZero)
{
    // when
    long long result = alma::mult_mod(14, 0, 0);
    // then
    EXPECT_EQ(0LL, result);
}

TEST(MathsTest, multMod_WhenFactorsAreZero_ThenZero)
{
    // when
    long long result = alma::mult_mod(0, 0, 0);
    // then
    EXPECT_EQ(0LL, result);
}

TEST(MathsTest, multMod_WhenOneFactorIsNegativeAndAnotherIsPositive_ThenNegative)
{
    // when
    long long result = alma::mult_mod(-3, 10, 0);
    // then
    EXPECT_EQ(-30LL, result);
}

TEST(MathsTest, multMod_WhenOneFactorIsPositiveAndAnotherIsNegative_ThenNegative)
{
    // when
    long long result = alma::mult_mod(3, -10, 0);
    // then
    EXPECT_EQ(-30LL, result);
}

TEST(MathsTest, multMod_WhenFactorsAreNegative_ThenPositive)
{
    // when
    long long result = alma::mult_mod(-3, -10, 0);
    // then
    EXPECT_EQ(30LL, result);
}

TEST(MathsTest, multMod_WhenModuloAndFactorsArePositive)
{
    // when
    long long result = alma::mult_mod(547, 312, 10000);
    // then
    EXPECT_EQ(664LL, result);
}

TEST(MathsTest, multMod_WhenModuloIsPositiveAndFirstFactorIsNegative)
{
    // when
    long long result = alma::mult_mod(-547, 312, 10000);
    // then
    EXPECT_EQ(9336LL, result);
}

TEST(MathsTest, multMod_WhenModuloIsPositiveAndSecondFactorIsNegative)
{
    // when
    long long result = alma::mult_mod(547, -312, 10000);
    // then
    EXPECT_EQ(9336LL, result);
}

TEST(MathsTest, multMod_WhenModuloIsPositiveAndFactorsAreNegative)
{
    // when
    long long result = alma::mult_mod(-547, -312, 10000);
    // then
    EXPECT_EQ(664LL, result);
}

#pragma endregion
