//! TESTY DLA UŁAMKÓW
#include <gtest/gtest.h>
#include "algolib/mathmat/fraction.hpp"

namespace alma = algolib::mathmat;

TEST(FractionTest, inverse_WhenPositive)
{
    alma::fraction frac(7, 19);

    alma::fraction result = ~frac;

    EXPECT_EQ(alma::fraction(19, 7), result);
}

TEST(FractionTest, inverse_WhenNegative)
{
    alma::fraction frac(-7, 19);

    alma::fraction result = ~frac;

    EXPECT_EQ(alma::fraction(-19, 7), result);
}

TEST(FractionTest, inverse_WhenZero_ThenThrowsDomainError)
{
    alma::fraction frac(0);

    EXPECT_THROW(~frac, std::domain_error);
}

TEST(FractionTest, reverse_WhenPositive)
{
    alma::fraction frac(7, 19);

    alma::fraction result = -frac;

    EXPECT_EQ(alma::fraction(-7, 19), result);
}

TEST(FractionTest, reverse_WhenNegative)
{
    alma::fraction frac(-7, 19);

    alma::fraction result = -frac;

    EXPECT_EQ(alma::fraction(7, 19), result);
}

TEST(FractionTest, reverse_WhenZero_ThenReturnsZero)
{
    alma::fraction frac(0);

    alma::fraction result = -frac;

    EXPECT_EQ(alma::fraction(0), result);
}

TEST(FractionTest, convertToDouble)
{
    alma::fraction frac(-129, 20);

    double result = static_cast<double>(frac);

    EXPECT_EQ(-6.45, result);
}

TEST(FractionTest, convertToInt)
{
    alma::fraction frac(-129, 20);

    int result = static_cast<int>(frac);

    EXPECT_EQ(-6, result);
}

TEST(FractionTest, hash_WhenFraction_ThenReturnsXor)
{
    alma::fraction frac(-129, 20);

    size_t result = std::hash<alma::fraction>()(frac);

    EXPECT_EQ(-129 ^ 20, result);
}
