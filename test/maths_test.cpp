// TESTY DLA ALGORYTMÓW MATEMATYCZNYCH
#include <gtest/gtest.h>
#include "algolib/math/maths.hpp"

namespace alma = algolib::math;

TEST(MathsTest, testGCDWhenNumbersAreComposite)
{
    long long int number1 = 161LL;
    long long int number2 = 46LL;

    long long int result = alma::gcd(number1, number2);

    EXPECT_EQ(23LL, result);
}

TEST(MathsTest, testGCDWhenNumbersArePrime)
{
    long long int number1 = 127LL;
    long long int number2 = 41LL;

    long long int result = alma::gcd(number1, number2);

    EXPECT_EQ(1LL, result);
}

TEST(MathsTest, testGCDWhenNumbersAreMutuallyPrime)
{
    long long int number1 = 119LL;
    long long int number2 = 57LL;

    long long int result = alma::gcd(number1, number2);

    EXPECT_EQ(1LL, result);
}

TEST(MathsTest, testGCDWhenOneOfNumbersIsMultipleOfAnother)
{
    long long int number1 = 272LL;
    long long int number2 = 34LL;

    long long int result = alma::gcd(number1, number2);

    EXPECT_EQ(number2, result);
}

TEST(MathsTest, testGCDWhenOneOfNumbersIsZero)
{
    long long int number1 = 96LL;
    long long int number2 = 0LL;

    long long int result = alma::gcd(number1, number2);

    EXPECT_EQ(number1, result);
}

TEST(MathsTest, testLCMWhenNumbersAreComposite)
{
    long long int number1 = 161LL;
    long long int number2 = 46LL;

    long long int result = alma::lcm(number1, number2);

    EXPECT_EQ(322LL, result);
}

TEST(MathsTest, testLCMWhenNumbersArePrime)
{
    long long int number1 = 127LL;
    long long int number2 = 41LL;

    long long int result = alma::lcm(number1, number2);

    EXPECT_EQ(5207LL, result);
}

TEST(MathsTest, testLCMWhenNumbersAreMutuallyPrime)
{
    long long int number1 = 119LL;
    long long int number2 = 57LL;

    long long int result = alma::lcm(number1, number2);

    EXPECT_EQ(6783LL, result);
}

TEST(MathsTest, testLCMWhenOneOfNumbersIsMultipleOfAnother)
{
    long long int number1 = 272LL;
    long long int number2 = 34LL;

    long long int result = alma::lcm(number1, number2);

    EXPECT_EQ(number1, result);
}

TEST(MathsTest, testLCMWhenOneOfNumbersIsZero)
{
    long long int number1 = 96LL;
    long long int number2 = 0LL;

    long long int result = alma::lcm(number1, number2);

    EXPECT_EQ(number2, result);
}

TEST(MathsTest, testPowerModWhenBaseIsZero)
{
    long long int number1 = 0LL;
    long long int number2 = 14LL;
    long long int number3 = 0LL;

    long long int result = alma::power_mod(number1, number2, number3);

    EXPECT_EQ(number1, result);
}

TEST(MathsTest, testPowerModWhenExponentIsZero)
{
    long long int number1 = 14LL;
    long long int number2 = 0LL;
    long long int number3 = 0LL;

    long long int result = alma::power_mod(number1, number2, number3);

    EXPECT_EQ(1LL, result);
}

TEST(MathsTest, testPowerModWhenBaseAndExponentAreZero)
{
    long long int number1 = 0LL;
    long long int number2 = 0LL;
    long long int number3 = 0LL;

    EXPECT_THROW(alma::power_mod(number1, number2, number3), std::domain_error);
}

TEST(MathsTest, testPowerModWhenBaseAndExponentArePositive)
{
    long long int number1 = 3LL;
    long long int number2 = 10LL;
    long long int number3 = 0LL;

    long long int result = alma::power_mod(number1, number2, number3);

    EXPECT_EQ(59049LL, result);
}

TEST(MathsTest, testPowerModWhenBaseIsNegativeAndExponentIsEven)
{
    long long int number1 = -3LL;
    long long int number2 = 10LL;
    long long int number3 = 0LL;

    long long int result = alma::power_mod(number1, number2, number3);

    EXPECT_EQ(59049LL, result);
}

TEST(MathsTest, testPowerModWhenBaseIsNegativeAndExponentIsOdd)
{
    long long int number1 = -3LL;
    long long int number2 = 9LL;
    long long int number3 = 0LL;

    long long int result = alma::power_mod(number1, number2, number3);

    EXPECT_EQ(-19683LL, result);
}

TEST(MathsTest, testPowerModWhenExponentIsNegative)
{
    long long int number1 = 3LL;
    long long int number2 = -10LL;
    long long int number3 = 0LL;

    EXPECT_THROW(alma::power_mod(number1, number2, number3), std::domain_error);
}

TEST(MathsTest, testPowerModWhenModuloAndBaseArePositive)
{
    long long int number1 = 5LL;
    long long int number2 = 11LL;
    long long int number3 = 10000LL;

    long long int result = alma::power_mod(number1, number2, number3);

    EXPECT_EQ(8125LL, result);
}

TEST(MathsTest, testPowerModWhenModuloIsPositiveAndBaseIsNegative)
{
    long long int number1 = -5LL;
    long long int number2 = 11LL;
    long long int number3 = 10000LL;

    long long int result = alma::power_mod(number1, number2, number3);

    EXPECT_EQ(1875LL, result);
}

TEST(MathsTest, testMultModWhenFactor1IsZero)
{
    long long int number1 = 0LL;
    long long int number2 = 14LL;
    long long int number3 = 0LL;

    long long int result = alma::mult_mod(number1, number2, number3);

    EXPECT_EQ(number1, result);
}

TEST(MathsTest, testPowerModWhenFactor2IsZero)
{
    long long int number1 = 14LL;
    long long int number2 = 0LL;
    long long int number3 = 0LL;

    long long int result = alma::mult_mod(number1, number2, number3);

    EXPECT_EQ(number2, result);
}

TEST(MathsTest, testMultModWhenFactorsAreZero)
{
    long long int number1 = 0LL;
    long long int number2 = 0LL;
    long long int number3 = 0LL;

    long long int result = alma::mult_mod(number1, number2, number3);

    EXPECT_EQ(number1, result);
}

TEST(MathsTest, testMultModWhenFactor1IsNegativeAndFactor2IsPositive)
{
    long long int number1 = -3LL;
    long long int number2 = 10LL;
    long long int number3 = 0LL;

    long long int result = alma::mult_mod(number1, number2, number3);

    EXPECT_EQ(-30LL, result);
}

TEST(MathsTest, testMultModWhenFactor1IsPositiveAndFactor2IsNegative)
{
    long long int number1 = 3LL;
    long long int number2 = -10LL;
    long long int number3 = 0LL;

    long long int result = alma::mult_mod(number1, number2, number3);

    EXPECT_EQ(-30LL, result);
}

TEST(MathsTest, testMultModWhenFactorsAreNegative)
{
    long long int number1 = -3LL;
    long long int number2 = -10LL;
    long long int number3 = 0LL;

    long long int result = alma::mult_mod(number1, number2, number3);

    EXPECT_EQ(30LL, result);
}

TEST(MathsTest, testMultModWhenModuloAndFactorsArePositive)
{
    long long int number1 = 547LL;
    long long int number2 = 312LL;
    long long int number3 = 10000LL;

    long long int result = alma::mult_mod(number1, number2, number3);

    EXPECT_EQ(664LL, result);
}

TEST(MathsTest, testMultModWhenModuloIsPositiveAndFactor1IsNegative)
{
    long long int number1 = -547LL;
    long long int number2 = 312LL;
    long long int number3 = 10000LL;

    long long int result = alma::mult_mod(number1, number2, number3);

    EXPECT_EQ(9336LL, result);
}

TEST(MathsTest, testMultModWhenModuloIsPositiveAndFactor2IsNegative)
{
    long long int number1 = 547LL;
    long long int number2 = -312LL;
    long long int number3 = 10000LL;

    long long int result = alma::mult_mod(number1, number2, number3);

    EXPECT_EQ(9336LL, result);
}

TEST(MathsTest, testMultModWhenModuloIsPositiveAndFactorsAreNegative)
{
    long long int number1 = -547LL;
    long long int number2 = -312LL;
    long long int number3 = 10000LL;

    long long int result = alma::mult_mod(number1, number2, number3);

    EXPECT_EQ(664LL, result);
}
