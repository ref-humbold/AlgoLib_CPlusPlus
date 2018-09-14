// TESTY DLA UŁAMKÓW
#include <gtest/gtest.h>
#include "algolib/math/fraction.hpp"

namespace alma = algolib::math;

TEST(FractionTest, testInverseWhenPositive)
{
    alma::fraction frac(7, 19);

    alma::fraction result = ~frac;

    EXPECT_EQ(alma::fraction(19, 7), result);
}

TEST(FractionTest, testInverseWhenNegative)
{
    alma::fraction frac(-7, 19);

    alma::fraction result = ~frac;

    EXPECT_EQ(alma::fraction(-19, 7), result);
}

TEST(FractionTest, testInverseWhenZero)
{
    alma::fraction frac(0);

    EXPECT_THROW(~frac, std::domain_error);
}

TEST(FractionTest, testReverseWhenPositive)
{
    alma::fraction frac(7, 19);

    alma::fraction result = -frac;

    EXPECT_EQ(alma::fraction(-7, 19), result);
}

TEST(FractionTest, testReverseWhenNegative)
{
    alma::fraction frac(-7, 19);

    alma::fraction result = -frac;

    EXPECT_EQ(alma::fraction(7, 19), result);
}

TEST(FractionTest, testReverseWhenZero)
{
    alma::fraction frac(0);

    alma::fraction result = -frac;

    EXPECT_EQ(alma::fraction(0), result);
}

TEST(FractionTest, testConvertToDouble)
{
    alma::fraction frac(-129, 20);

    double result = (double)frac;

    EXPECT_EQ(-6.45, result);
}

TEST(FractionTest, testConvertToInt)
{
    alma::fraction frac(-129, 20);

    int result = (int)frac;

    EXPECT_EQ(-6, result);
}

TEST(FractionTest, testHash)
{
    alma::fraction frac(-129, 20);

    size_t result = std::hash<alma::fraction>()(frac);

    EXPECT_EQ(-109, result);
}
