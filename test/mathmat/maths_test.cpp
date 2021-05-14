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
    long result = alma::gcd(161L, 46L);
    // then
    EXPECT_EQ(23L, result);
}

TEST(MathsTest, gcd_WhenNumbersArePrime_ThenOne)
{
    // when
    long long result = alma::gcd(127LL, 41LL);
    // then
    EXPECT_EQ(1LL, result);
}

TEST(MathsTest, gcd_WhenNumbersAreMutuayPrime_ThenOne)
{
    // when
    int result = alma::gcd(119, 57);
    // then
    EXPECT_EQ(1, result);
}

TEST(MathsTest, gcd_WhenOneOfNumbersIsMultipleOfAnother_ThenLessNumber)
{
    // given
    int number = 34;
    // when
    int result = alma::gcd(number, number * 6);
    // then
    EXPECT_EQ(number, result);
}

TEST(MathsTest, gcd_WhenOneOfNumbersIsZero_ThenAnotherNumber)
{
    // given
    int number = 96;
    // when
    int result = alma::gcd(number, 0);
    // then
    EXPECT_EQ(number, result);
}

#pragma endregion
#pragma region lcm

TEST(MathsTest, lcm_WhenNumbersAreComposite_ThenLCM)
{
    // when
    long result = alma::lcm(161L, 46L);
    // then
    EXPECT_EQ(322L, result);
}

TEST(MathsTest, lcm_WhenNumbersArePrime_ThenProduct)
{
    // when
    long long result = alma::lcm(127L, 41L);
    // then
    EXPECT_EQ(5207L, result);
}

TEST(MathsTest, lcm_WhenNumbersAreMutuayPrime_ThenProduct)
{
    // when
    int result = alma::lcm(119, 57);
    // then
    EXPECT_EQ(6783, result);
}

TEST(MathsTest, lcm_WhenOneOfNumbersIsMultipleOfAnother_ThenGreaterNumber)
{
    // given
    int number = 34;
    // when
    int result = alma::lcm(number, number * 6);
    // then
    EXPECT_EQ(number * 6, result);
}

TEST(MathsTest, lcm_WhenOneOfNumbersIsZero_ThenZero)
{
    // when
    int result = alma::lcm(96, 0);
    // then
    EXPECT_EQ(0, result);
}

#pragma endregion
#pragma region mult

TEST(MathsTest, multiply_WhenFirstFactorIsZero_ThenZero)
{
    // when
    int result = alma::multiply(0, 14);
    // then
    EXPECT_EQ(0, result);
}

TEST(MathsTest, multiply_WhenSecondFactorIsZero_ThenZero)
{
    // when
    int result = alma::multiply(14, 0);
    // then
    EXPECT_EQ(0, result);
}

TEST(MathsTest, multiply_WhenFactorsAreZero_ThenZero)
{
    // when
    int result = alma::multiply(0, 0);
    // then
    EXPECT_EQ(0, result);
}

TEST(MathsTest, multiply_WhenFactorsArePositive_ThenResultIsPositive)
{
    // when
    int result = alma::multiply(3, 10);
    // then
    EXPECT_EQ(30, result);
}

TEST(MathsTest, multiply_WhenFirstFactorIsNegativeAndSecondFactorIsPositive_ThenResultIsNegative)
{
    // when
    int result = alma::multiply(-3, 10);
    // then
    EXPECT_EQ(-30, result);
}

TEST(MathsTest, multiply_WhenFirstFactorIsPositiveAndSecondFactorIsNegative_ThenResultIsNegative)
{
    // when
    long result = alma::multiply(3L, -10L);
    // then
    EXPECT_EQ(-30L, result);
}

TEST(MathsTest, multiply_WhenFactorsAreNegative_ThenResultIsPositive)
{
    // when
    long long result = alma::multiply(-3LL, -10LL);
    // then
    EXPECT_EQ(30LL, result);
}

TEST(MathsTest, multiply_WhenModuloAndFactorsArePositive)
{
    // when
    int result = alma::multiply(547, 312, 10000);
    // then
    EXPECT_EQ(664, result);
}

TEST(MathsTest, multiply_WhenModuloIsPositiveAndFirstFactorIsNegative)
{
    // when
    int result = alma::multiply(-547, 312, 10000);
    // then
    EXPECT_EQ(9336L, result);
}

TEST(MathsTest, multiply_WhenModuloIsPositiveAndSecondFactorIsNegative)
{
    // when
    long result = alma::multiply(547L, -312L, 10000L);
    // then
    EXPECT_EQ(9336LL, result);
}

TEST(MathsTest, multiply_WhenModuloIsPositiveAndFactorsAreNegative)
{
    // when
    long long result = alma::multiply(-547LL, -312LL, 10000LL);
    // then
    EXPECT_EQ(664LL, result);
}

TEST(MathsTest, multiply_WhenModuloIsNegative_ThenDomainError)
{
    // when
    auto exec = [&]() { alma::multiply(-547, -312, -10000); };
    // then
    EXPECT_THROW(exec(), std::domain_error);
}

#pragma endregion
#pragma region power

TEST(MathsTest, power_WhenBaseIsZero_ThenZero)
{
    // when
    int result = alma::power(0, 14);
    // then
    EXPECT_EQ(0, result);
}

TEST(MathsTest, power_WhenExponentIsZero_ThenOne)
{
    // when
    int result = alma::power(14, 0);
    // then
    EXPECT_EQ(1, result);
}

TEST(MathsTest, power_WhenBaseAndExponentAreZero_ThenDomainError)
{
    // when
    auto exec = [&]() { return alma::power(0, 0); };
    // then
    EXPECT_THROW(exec(), std::domain_error);
}

TEST(MathsTest, power_WhenBaseAndExponentArePositive_ThenResultIsPositive)
{
    // when
    int result = alma::power(3, 10);
    // then
    EXPECT_EQ(59049, result);
}

TEST(MathsTest, power_WhenBaseIsNegativeAndExponentIsEven_ThenResultIsPositive)
{
    // when
    long result = alma::power(-3L, 10L);
    // then
    EXPECT_EQ(59049L, result);
}

TEST(MathsTest, power_WhenBaseIsNegativeAndExponentIsOdd_ThenResultIsNegative)
{
    // when
    long long result = alma::power(-3LL, 9LL);
    // then
    EXPECT_EQ(-19683LL, result);
}

TEST(MathsTest, power_WhenExponentIsNegative_ThenDomainError)
{
    // when
    auto exec = [&]() { return alma::power(-3, -10); };
    // then
    EXPECT_THROW(exec(), std::domain_error);
}

TEST(MathsTest, power_WhenModuloAndBaseArePositive)
{
    // when
    int result = alma::power(5, 11, 10000);
    // then
    EXPECT_EQ(8125, result);
}

TEST(MathsTest, power_WhenModuloIsPositiveAndBaseIsNegativeAndExponentIsOdd)
{
    // when
    long result = alma::power(-5L, 11L, 10000L);
    // then
    EXPECT_EQ(1875L, result);
}

TEST(MathsTest, power_WhenModuloIsPositiveAndBaseIsNegativeAndExponentIsEven)
{
    // when
    long long result = alma::power(-5LL, 12LL, 10000LL);
    // then
    EXPECT_EQ(625LL, result);
}

TEST(MathsTest, power_WhenModuloIsNegative_ThenDomainError)
{
    // then
    auto exec = [&]() { return alma::power(-5, 11, -10000); };
    // then
    EXPECT_THROW(exec(), std::domain_error);
}

#pragma endregion
