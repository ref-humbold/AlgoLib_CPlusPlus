//! TESTY DLA UŁAMKÓW
#include <gtest/gtest.h>
#include "algolib/mathmat/fraction.hpp"

namespace alma = algolib::mathmat;

TEST(FractionTest, inverse_whenPositive)
{
    alma::fraction frac(7, 19);

    alma::fraction result = ~frac;

    EXPECT_EQ(alma::fraction(19, 7), result);
}

TEST(FractionTest, inverse_whenNegative)
{
    alma::fraction frac(-7, 19);

    alma::fraction result = ~frac;

    EXPECT_EQ(alma::fraction(-19, 7), result);
}

TEST(FractionTest, inverse_whenZero_thenThrowsDomainError)
{
    alma::fraction frac(0);

    EXPECT_THROW(~frac, std::domain_error);
}

TEST(FractionTest, reverse_whenPositive)
{
    alma::fraction frac(7, 19);

    alma::fraction result = -frac;

    EXPECT_EQ(alma::fraction(-7, 19), result);
}

TEST(FractionTest, reverse_whenNegative)
{
    alma::fraction frac(-7, 19);

    alma::fraction result = -frac;

    EXPECT_EQ(alma::fraction(7, 19), result);
}

TEST(FractionTest, reverse_whenZero_thenReturnsZero)
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

TEST(FractionTest, hash_whenFraction_thenReturnsXor)
{
    alma::fraction frac(-129, 20);

    size_t result = std::hash<alma::fraction>()(frac);

    EXPECT_EQ(-129 ^ 20, result);
}
