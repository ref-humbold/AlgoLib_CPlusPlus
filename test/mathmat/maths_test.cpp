/**!
 * \file maths_test.cpp
 * \brief Tests: Algorithms for basic mathematical computations
 */
#include <gtest/gtest.h>
#include "algolib/mathmat/maths.hpp"

namespace alma = algolib::mathmat;

#pragma region gcd

TEST(MathsTest, gcd_WhenNumbersAreComposite_ThenReturnsGCD)
{
    long long int number1 = 161LL;
    long long int number2 = 46LL;

    long long int result = alma::gcd(number1, number2);

    EXPECT_EQ(23LL, result);
}

TEST(MathsTest, gcd_WhenNumbersArePrime_ThenReturnsOne)
{
    long long int number1 = 127LL;
    long long int number2 = 41LL;

    long long int result = alma::gcd(number1, number2);

    EXPECT_EQ(1LL, result);
}

TEST(MathsTest, gcd_WhenNumbersAreMutuallyPrime_ThenReturnsOne)
{
    long long int number1 = 119LL;
    long long int number2 = 57LL;

    long long int result = alma::gcd(number1, number2);

    EXPECT_EQ(1LL, result);
}

TEST(MathsTest, gcd_WhenNumber1IsMultipleOfNumber2_ThenReturnsNumber2)
{
    long long int number1 = 272LL;
    long long int number2 = 34LL;

    long long int result = alma::gcd(number1, number2);

    EXPECT_EQ(number2, result);
}

TEST(MathsTest, gcd_WhenNumber2IsZero_ThenReturnsNumber1)
{
    long long int number1 = 96LL;
    long long int number2 = 0LL;

    long long int result = alma::gcd(number1, number2);

    EXPECT_EQ(number1, result);
}

#pragma endregion
#pragma region lcm

TEST(MathsTest, lcm_WhenNumbersAreComposite_ThenReturnsLCM)
{
    long long int number1 = 161LL;
    long long int number2 = 46LL;

    long long int result = alma::lcm(number1, number2);

    EXPECT_EQ(322LL, result);
}

TEST(MathsTest, lcm_WhenNumbersArePrime_ThenReturnsProduct)
{
    long long int number1 = 127LL;
    long long int number2 = 41LL;

    long long int result = alma::lcm(number1, number2);

    EXPECT_EQ(5207LL, result);
}

TEST(MathsTest, lcm_WhenNumbersAreMutuallyPrime_ThenReturnsProduct)
{
    long long int number1 = 119LL;
    long long int number2 = 57LL;

    long long int result = alma::lcm(number1, number2);

    EXPECT_EQ(6783LL, result);
}

TEST(MathsTest, lcm_WhenNumber1IsMultipleOfNumber2_ThenReturnsNumber1)
{
    long long int number1 = 272LL;
    long long int number2 = 34LL;

    long long int result = alma::lcm(number1, number2);

    EXPECT_EQ(number1, result);
}

TEST(MathsTest, lcm_WhenNumber2IsZero_ThenReturnsZero)
{
    long long int number1 = 96LL;
    long long int number2 = 0LL;

    long long int result = alma::lcm(number1, number2);

    EXPECT_EQ(0LL, result);
}

#pragma endregion
#pragma region powerMod

TEST(MathsTest, powerMod_WhenBaseIsZero_ThenReturnsZero)
{
    long long int number1 = 0LL;
    long long int number2 = 14LL;
    long long int number3 = 0LL;

    long long int result = alma::power_mod(number1, number2, number3);

    EXPECT_EQ(0LL, result);
}

TEST(MathsTest, powerMod_WhenExponentIsZero_ThenReturnsOne)
{
    long long int number1 = 14LL;
    long long int number2 = 0LL;
    long long int number3 = 0LL;

    long long int result = alma::power_mod(number1, number2, number3);

    EXPECT_EQ(1LL, result);
}

TEST(MathsTest, powerMod_WhenBaseAndExponentAreZero_ThenThrowsDomainError)
{
    long long int number1 = 0LL;
    long long int number2 = 0LL;
    long long int number3 = 0LL;

    EXPECT_THROW(alma::power_mod(number1, number2, number3), std::domain_error);
}

TEST(MathsTest, powerMod_WhenBaseAndExponentArePositive)
{
    long long int number1 = 3LL;
    long long int number2 = 10LL;
    long long int number3 = 0LL;

    long long int result = alma::power_mod(number1, number2, number3);

    EXPECT_EQ(59049LL, result);
}

TEST(MathsTest, powerMod_WhenBaseIsNegativeAndExponentIsEven)
{
    long long int number1 = -3LL;
    long long int number2 = 10LL;
    long long int number3 = 0LL;

    long long int result = alma::power_mod(number1, number2, number3);

    EXPECT_EQ(59049LL, result);
}

TEST(MathsTest, powerMod_WhenBaseIsNegativeAndExponentIsOdd)
{
    long long int number1 = -3LL;
    long long int number2 = 9LL;
    long long int number3 = 0LL;

    long long int result = alma::power_mod(number1, number2, number3);

    EXPECT_EQ(-19683LL, result);
}

TEST(MathsTest, powerMod_WhenExponentIsNegative_ThenThrowsDomainError)
{
    long long int number1 = 3LL;
    long long int number2 = -10LL;
    long long int number3 = 0LL;

    EXPECT_THROW(alma::power_mod(number1, number2, number3), std::domain_error);
}

TEST(MathsTest, powerMod_WhenModuloAndBaseArePositive)
{
    long long int number1 = 5LL;
    long long int number2 = 11LL;
    long long int number3 = 10000LL;

    long long int result = alma::power_mod(number1, number2, number3);

    EXPECT_EQ(8125LL, result);
}

TEST(MathsTest, powerMod_WhenModuloIsPositiveAndBaseIsNegative)
{
    long long int number1 = -5LL;
    long long int number2 = 11LL;
    long long int number3 = 10000LL;

    long long int result = alma::power_mod(number1, number2, number3);

    EXPECT_EQ(1875LL, result);
}

#pragma endregion
#pragma region multMod

TEST(MathsTest, multMod_WhenFactor1IsZero_ThenReturnsZero)
{
    long long int number1 = 0LL;
    long long int number2 = 14LL;
    long long int number3 = 0LL;

    long long int result = alma::mult_mod(number1, number2, number3);

    EXPECT_EQ(0LL, result);
}

TEST(MathsTest, multMod_WhenFactor2IsZero_ThenReturnsZero)
{
    long long int number1 = 14LL;
    long long int number2 = 0LL;
    long long int number3 = 0LL;

    long long int result = alma::mult_mod(number1, number2, number3);

    EXPECT_EQ(0LL, result);
}

TEST(MathsTest, multMod_WhenFactorsAreZero_ThenReturnsZero)
{
    long long int number1 = 0LL;
    long long int number2 = 0LL;
    long long int number3 = 0LL;

    long long int result = alma::mult_mod(number1, number2, number3);

    EXPECT_EQ(0LL, result);
}

TEST(MathsTest, multMod_WhenFactor1IsNegativeAndFactor2IsPositive)
{
    long long int number1 = -3LL;
    long long int number2 = 10LL;
    long long int number3 = 0LL;

    long long int result = alma::mult_mod(number1, number2, number3);

    EXPECT_EQ(-30LL, result);
}

TEST(MathsTest, multMod_WhenFactor1IsPositiveAndFactor2IsNegative)
{
    long long int number1 = 3LL;
    long long int number2 = -10LL;
    long long int number3 = 0LL;

    long long int result = alma::mult_mod(number1, number2, number3);

    EXPECT_EQ(-30LL, result);
}

TEST(MathsTest, multMod_WhenFactorsAreNegative)
{
    long long int number1 = -3LL;
    long long int number2 = -10LL;
    long long int number3 = 0LL;

    long long int result = alma::mult_mod(number1, number2, number3);

    EXPECT_EQ(30LL, result);
}

TEST(MathsTest, multMod_WhenModuloAndFactorsArePositive)
{
    long long int number1 = 547LL;
    long long int number2 = 312LL;
    long long int number3 = 10000LL;

    long long int result = alma::mult_mod(number1, number2, number3);

    EXPECT_EQ(664LL, result);
}

TEST(MathsTest, multMod_WhenModuloIsPositiveAndFactor1IsNegative)
{
    long long int number1 = -547LL;
    long long int number2 = 312LL;
    long long int number3 = 10000LL;

    long long int result = alma::mult_mod(number1, number2, number3);

    EXPECT_EQ(9336LL, result);
}

TEST(MathsTest, multMod_WhenModuloIsPositiveAndFactor2IsNegative)
{
    long long int number1 = 547LL;
    long long int number2 = -312LL;
    long long int number3 = 10000LL;

    long long int result = alma::mult_mod(number1, number2, number3);

    EXPECT_EQ(9336LL, result);
}

TEST(MathsTest, multMod_WhenModuloIsPositiveAndFactorsAreNegative)
{
    long long int number1 = -547LL;
    long long int number2 = -312LL;
    long long int number3 = 10000LL;

    long long int result = alma::mult_mod(number1, number2, number3);

    EXPECT_EQ(664LL, result);
}

#pragma endregion
