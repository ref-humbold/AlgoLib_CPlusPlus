// TESTY DLA ALGORYTMÓW MATEMATYCZNYCH
#include <gtest/gtest.h>
#include "../algolib/maths/maths.hpp"

namespace alma = algolib::maths;

TEST(MathsTest, testGCDWhenNumbersAreComposite)
{
    int number1 = 161;
    int number2 = 46;

    int result = alma::gcd(number1, number2);

    EXPECT_EQ(23, result);
}

TEST(MathsTest, testGCDWhenNumbersArePrime)
{
    int number1 = 127;
    int number2 = 41;

    int result = alma::gcd(number1, number2);

    EXPECT_EQ(1, result);
}

TEST(MathsTest, testGCDWhenNumbersAreMutuallyPrime)
{
    int number1 = 119;
    int number2 = 57;

    int result = alma::gcd(number1, number2);

    EXPECT_EQ(1, result);
}

TEST(MathsTest, testGCDWhenOneOfNumbersIsMultipleOfAnother)
{
    int number1 = 272;
    int number2 = 34;

    int result = alma::gcd(number1, number2);

    EXPECT_EQ(number2, result);
}

TEST(MathsTest, testGCDWhenOneOfNumbersIsZero)
{
    int number1 = 96;
    int number2 = 0;

    int result = alma::gcd(number1, number2);

    EXPECT_EQ(number1, result);
}

TEST(MathsTest, testLCMWhenNumbersAreComposite)
{
    int number1 = 161;
    int number2 = 46;

    int result = alma::lcm(number1, number2);

    EXPECT_EQ(322, result);
}

TEST(MathsTest, testLCMWhenNumbersArePrime)
{
    int number1 = 127;
    int number2 = 41;

    int result = alma::lcm(number1, number2);

    EXPECT_EQ(5207, result);
}

TEST(MathsTest, testLCMWhenNumbersAreMutuallyPrime)
{
    int number1 = 119;
    int number2 = 57;

    int result = alma::lcm(number1, number2);

    EXPECT_EQ(6783, result);
}

TEST(MathsTest, testLCMWhenOneOfNumbersIsMultipleOfAnother)
{
    int number1 = 272;
    int number2 = 34;

    int result = alma::lcm(number1, number2);

    EXPECT_EQ(number1, result);
}

TEST(MathsTest, testLCMWhenOneOfNumbersIsZero)
{
    int number1 = 96;
    int number2 = 0;

    int result = alma::lcm(number1, number2);

    EXPECT_EQ(number2, result);
}

TEST(MathsTest, testPowerModWhenBaseIsZero)
{
    int number1 = 0;
    int number2 = 14;
    int number3 = 0;

    int result = alma::power_mod(number1, number2, number3);

    EXPECT_EQ(number1, result);
}

TEST(MathsTest, testPowerModWhenExponentIsZero)
{
    int number1 = 14;
    int number2 = 0;
    int number3 = 0;

    int result = alma::power_mod(number1, number2, number3);

    EXPECT_EQ(1, result);
}

TEST(MathsTest, testPowerModWhenBaseAndExponentAreZero)
{
    int number1 = 0;
    int number2 = 0;
    int number3 = 0;

    EXPECT_THROW(alma::power_mod(number1, number2, number3), std::domain_error);
}

TEST(MathsTest, testPowerModWhenBaseAndExponentArePositive)
{
    int number1 = 3;
    int number2 = 10;
    int number3 = 0;

    int result = alma::power_mod(number1, number2, number3);

    EXPECT_EQ(59049, result);
}

TEST(MathsTest, testPowerModWhenBaseIsNegativeAndExponentIsEven)
{
    int number1 = -3;
    int number2 = 10;
    int number3 = 0;

    int result = alma::power_mod(number1, number2, number3);

    EXPECT_EQ(59049, result);
}

TEST(MathsTest, testPowerModWhenBaseIsNegativeAndExponentIsOdd)
{
    int number1 = -3;
    int number2 = 9;
    int number3 = 0;

    int result = alma::power_mod(number1, number2, number3);

    EXPECT_EQ(-19683, result);
}

TEST(MathsTest, testPowerModWhenExponentIsNegative)
{
    int number1 = 3;
    int number2 = -10;
    int number3 = 0;

    EXPECT_THROW(alma::power_mod(number1, number2, number3), std::domain_error);
}

TEST(MathsTest, testPowerModWhenModuloAndBaseArePositive)
{
    int number1 = 5;
    int number2 = 11;
    int number3 = 10000;

    int result = alma::power_mod(number1, number2, number3);

    EXPECT_EQ(8125, result);
}

TEST(MathsTest, testPowerModWhenModuloIsPositiveAndBaseIsNegative)
{
    int number1 = -5;
    int number2 = 11;
    int number3 = 10000;

    int result = alma::power_mod(number1, number2, number3);

    EXPECT_EQ(1875, result);
}

TEST(MathsTest, testPowerModWhenModuloIsNegative)
{
    int number1 = 5;
    int number2 = 11;
    int number3 = -10000;

    EXPECT_THROW(alma::power_mod(number1, number2, number3), std::domain_error);
}

TEST(MathsTest, testMultModWhenFactor1IsZero)
{
    int number1 = 0;
    int number2 = 14;
    int number3 = 0;

    int result = alma::mult_mod(number1, number2, number3);

    EXPECT_EQ(number1, result);
}

TEST(MathsTest, testPowerModWhenFactor2IsZero)
{
    int number1 = 14;
    int number2 = 0;
    int number3 = 0;

    int result = alma::mult_mod(number1, number2, number3);

    EXPECT_EQ(number2, result);
}

TEST(MathsTest, testMultModWhenFactorsAreZero)
{
    int number1 = 0;
    int number2 = 0;
    int number3 = 0;

    int result = alma::mult_mod(number1, number2, number3);

    EXPECT_EQ(number1, result);
}

TEST(MathsTest, testMultModWhenFactor1IsNegativeAndFactor2IsPositive)
{
    int number1 = -3;
    int number2 = 10;
    int number3 = 0;

    int result = alma::mult_mod(number1, number2, number3);

    EXPECT_EQ(-30, result);
}

TEST(MathsTest, testMultModWhenFactor1IsPositiveAndFactor2IsNegative)
{
    int number1 = 3;
    int number2 = -10;
    int number3 = 0;

    int result = alma::mult_mod(number1, number2, number3);

    EXPECT_EQ(-30, result);
}

TEST(MathsTest, testMultModWhenFactorsAreNegative)
{
    int number1 = -3;
    int number2 = -10;
    int number3 = 0;

    int result = alma::mult_mod(number1, number2, number3);

    EXPECT_EQ(30, result);
}

TEST(MathsTest, testMultModWhenModuloAndFactorsArePositive)
{
    int number1 = 547;
    int number2 = 312;
    int number3 = 10000;

    int result = alma::mult_mod(number1, number2, number3);

    EXPECT_EQ(664, result);
}

TEST(MathsTest, testMultModWhenModuloIsPositiveAndFactor1IsNegative)
{
    int number1 = -547;
    int number2 = 312;
    int number3 = 10000;

    int result = alma::mult_mod(number1, number2, number3);

    EXPECT_EQ(9336, result);
}

TEST(MathsTest, testMultModWhenModuloIsPositiveAndFactor2IsNegative)
{
    int number1 = 547;
    int number2 = -312;
    int number3 = 10000;

    int result = alma::mult_mod(number1, number2, number3);

    EXPECT_EQ(9336, result);
}

TEST(MathsTest, testMultModWhenModuloIsPositiveAndFactorsAreNegative)
{
    int number1 = -547;
    int number2 = -312;
    int number3 = 10000;

    int result = alma::mult_mod(number1, number2, number3);

    EXPECT_EQ(664, result);
}

TEST(MathsTest, testMultModWhenModuloIsNegative)
{
    int number1 = 547;
    int number2 = 312;
    int number3 = -10000;

    EXPECT_THROW(alma::mult_mod(number1, number2, number3), std::domain_error);
}
