//! TESTY DLA ALGORYTMÓW MATEMATYCZNYCH
#include <gtest/gtest.h>
#include "algolib/mathmat/maths.hpp"

namespace alma = algolib::mathmat;

#pragma region gcd

TEST(MathsTest, gcd_whenNumbersAreComposite_thenReturnsGCD)
{
    long long int number1 = 161LL;
    long long int number2 = 46LL;

    long long int result = alma::gcd(number1, number2);

    EXPECT_EQ(23LL, result);
}

TEST(MathsTest, gcd_whenNumbersArePrime_thenReturnsOne)
{
    long long int number1 = 127LL;
    long long int number2 = 41LL;

    long long int result = alma::gcd(number1, number2);

    EXPECT_EQ(1LL, result);
}

TEST(MathsTest, gcd_whenNumbersAreMutuallyPrime_thenReturnsOne)
{
    long long int number1 = 119LL;
    long long int number2 = 57LL;

    long long int result = alma::gcd(number1, number2);

    EXPECT_EQ(1LL, result);
}

TEST(MathsTest, gcd_whenNumber1IsMultipleOfNumber2_thenReturnsNumber2)
{
    long long int number1 = 272LL;
    long long int number2 = 34LL;

    long long int result = alma::gcd(number1, number2);

    EXPECT_EQ(number2, result);
}

TEST(MathsTest, gcd_whenNumber2IsZero_thenReturnsNumber1)
{
    long long int number1 = 96LL;
    long long int number2 = 0LL;

    long long int result = alma::gcd(number1, number2);

    EXPECT_EQ(number1, result);
}

#pragma endregion
#pragma region lcm

TEST(MathsTest, lcm_whenNumbersAreComposite_thenReturnsLCM)
{
    long long int number1 = 161LL;
    long long int number2 = 46LL;

    long long int result = alma::lcm(number1, number2);

    EXPECT_EQ(322LL, result);
}

TEST(MathsTest, lcm_whenNumbersArePrime_thenReturnsProduct)
{
    long long int number1 = 127LL;
    long long int number2 = 41LL;

    long long int result = alma::lcm(number1, number2);

    EXPECT_EQ(5207LL, result);
}

TEST(MathsTest, lcm_whenNumbersAreMutuallyPrime_thenReturnsProduct)
{
    long long int number1 = 119LL;
    long long int number2 = 57LL;

    long long int result = alma::lcm(number1, number2);

    EXPECT_EQ(6783LL, result);
}

TEST(MathsTest, lcm_whenNumber1IsMultipleOfNumber2_thenReturnsNumber1)
{
    long long int number1 = 272LL;
    long long int number2 = 34LL;

    long long int result = alma::lcm(number1, number2);

    EXPECT_EQ(number1, result);
}

TEST(MathsTest, lcm_whenNumber2IsZero_thenReturnsZero)
{
    long long int number1 = 96LL;
    long long int number2 = 0LL;

    long long int result = alma::lcm(number1, number2);

    EXPECT_EQ(0LL, result);
}

#pragma endregion
#pragma region powerMod

TEST(MathsTest, powerMod_whenBaseIsZero_thenReturnsZero)
{
    long long int number1 = 0LL;
    long long int number2 = 14LL;
    long long int number3 = 0LL;

    long long int result = alma::power_mod(number1, number2, number3);

    EXPECT_EQ(0LL, result);
}

TEST(MathsTest, powerMod_whenExponentIsZero_thenReturnsOne)
{
    long long int number1 = 14LL;
    long long int number2 = 0LL;
    long long int number3 = 0LL;

    long long int result = alma::power_mod(number1, number2, number3);

    EXPECT_EQ(1LL, result);
}

TEST(MathsTest, powerMod_whenBaseAndExponentAreZero_thenThrowsDomainError)
{
    long long int number1 = 0LL;
    long long int number2 = 0LL;
    long long int number3 = 0LL;

    EXPECT_THROW(alma::power_mod(number1, number2, number3), std::domain_error);
}

TEST(MathsTest, powerMod_whenBaseAndExponentArePositive)
{
    long long int number1 = 3LL;
    long long int number2 = 10LL;
    long long int number3 = 0LL;

    long long int result = alma::power_mod(number1, number2, number3);

    EXPECT_EQ(59049LL, result);
}

TEST(MathsTest, powerMod_whenBaseIsNegativeAndExponentIsEven)
{
    long long int number1 = -3LL;
    long long int number2 = 10LL;
    long long int number3 = 0LL;

    long long int result = alma::power_mod(number1, number2, number3);

    EXPECT_EQ(59049LL, result);
}

TEST(MathsTest, powerMod_whenBaseIsNegativeAndExponentIsOdd)
{
    long long int number1 = -3LL;
    long long int number2 = 9LL;
    long long int number3 = 0LL;

    long long int result = alma::power_mod(number1, number2, number3);

    EXPECT_EQ(-19683LL, result);
}

TEST(MathsTest, powerMod_whenExponentIsNegative_thenThrowsDomainError)
{
    long long int number1 = 3LL;
    long long int number2 = -10LL;
    long long int number3 = 0LL;

    EXPECT_THROW(alma::power_mod(number1, number2, number3), std::domain_error);
}

TEST(MathsTest, powerMod_whenModuloAndBaseArePositive)
{
    long long int number1 = 5LL;
    long long int number2 = 11LL;
    long long int number3 = 10000LL;

    long long int result = alma::power_mod(number1, number2, number3);

    EXPECT_EQ(8125LL, result);
}

TEST(MathsTest, powerMod_whenModuloIsPositiveAndBaseIsNegative)
{
    long long int number1 = -5LL;
    long long int number2 = 11LL;
    long long int number3 = 10000LL;

    long long int result = alma::power_mod(number1, number2, number3);

    EXPECT_EQ(1875LL, result);
}

#pragma endregion
#pragma region multMod

TEST(MathsTest, multMod_whenFactor1IsZero_thenReturnsZero)
{
    long long int number1 = 0LL;
    long long int number2 = 14LL;
    long long int number3 = 0LL;

    long long int result = alma::mult_mod(number1, number2, number3);

    EXPECT_EQ(0LL, result);
}

TEST(MathsTest, multMod_whenFactor2IsZero_thenReturnsZero)
{
    long long int number1 = 14LL;
    long long int number2 = 0LL;
    long long int number3 = 0LL;

    long long int result = alma::mult_mod(number1, number2, number3);

    EXPECT_EQ(0LL, result);
}

TEST(MathsTest, multMod_whenFactorsAreZero_thenReturnsZero)
{
    long long int number1 = 0LL;
    long long int number2 = 0LL;
    long long int number3 = 0LL;

    long long int result = alma::mult_mod(number1, number2, number3);

    EXPECT_EQ(0LL, result);
}

TEST(MathsTest, multMod_whenFactor1IsNegativeAndFactor2IsPositive)
{
    long long int number1 = -3LL;
    long long int number2 = 10LL;
    long long int number3 = 0LL;

    long long int result = alma::mult_mod(number1, number2, number3);

    EXPECT_EQ(-30LL, result);
}

TEST(MathsTest, multMod_whenFactor1IsPositiveAndFactor2IsNegative)
{
    long long int number1 = 3LL;
    long long int number2 = -10LL;
    long long int number3 = 0LL;

    long long int result = alma::mult_mod(number1, number2, number3);

    EXPECT_EQ(-30LL, result);
}

TEST(MathsTest, multMod_whenFactorsAreNegative)
{
    long long int number1 = -3LL;
    long long int number2 = -10LL;
    long long int number3 = 0LL;

    long long int result = alma::mult_mod(number1, number2, number3);

    EXPECT_EQ(30LL, result);
}

TEST(MathsTest, multMod_whenModuloAndFactorsArePositive)
{
    long long int number1 = 547LL;
    long long int number2 = 312LL;
    long long int number3 = 10000LL;

    long long int result = alma::mult_mod(number1, number2, number3);

    EXPECT_EQ(664LL, result);
}

TEST(MathsTest, multMod_whenModuloIsPositiveAndFactor1IsNegative)
{
    long long int number1 = -547LL;
    long long int number2 = 312LL;
    long long int number3 = 10000LL;

    long long int result = alma::mult_mod(number1, number2, number3);

    EXPECT_EQ(9336LL, result);
}

TEST(MathsTest, multMod_whenModuloIsPositiveAndFactor2IsNegative)
{
    long long int number1 = 547LL;
    long long int number2 = -312LL;
    long long int number3 = 10000LL;

    long long int result = alma::mult_mod(number1, number2, number3);

    EXPECT_EQ(9336LL, result);
}

TEST(MathsTest, multMod_whenModuloIsPositiveAndFactorsAreNegative)
{
    long long int number1 = -547LL;
    long long int number2 = -312LL;
    long long int number3 = 10000LL;

    long long int result = alma::mult_mod(number1, number2, number3);

    EXPECT_EQ(664LL, result);
}

#pragma endregion
