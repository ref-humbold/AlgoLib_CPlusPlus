/**!
 * \file fraction_test.cpp
 * \brief Tests: Structure of fraction
 */
#include <sstream>
#include <gtest/gtest.h>
#include "algolib/mathmat/fraction.hpp"

namespace alma = algolib::mathmat;

#pragma region cast operators

TEST(FractionTest, operatorDouble_ThenDoubleValue)
{
    // given
    alma::fraction frac(-129, 20);
    // when
    double result = static_cast<double>(frac);
    // then
    EXPECT_EQ(-6.45, result);
}

TEST(FractionTest, operatorInt_ThenIntegerValueRoundedTowardsZero)
{
    // given
    alma::fraction frac(-129, 20);
    // when
    int result = static_cast<int>(frac);
    // then
    EXPECT_EQ(-6, result);
}

TEST(FractionTest, operatorBool_WhenZero_ThenFalse)
{
    // given
    alma::fraction frac;
    // when
    bool result = static_cast<bool>(frac);
    // then
    EXPECT_FALSE(result);
}

TEST(FractionTest, operatorBool_WhenPositive_ThenTrue)
{
    // given
    alma::fraction frac(129, 20);
    // when
    bool result = static_cast<bool>(frac);
    // then
    EXPECT_TRUE(result);
}

TEST(FractionTest, operatorBool_WhenNegative_ThenTrue)
{
    // given
    alma::fraction frac(129, -20);
    // when
    bool result = static_cast<bool>(frac);
    // then
    EXPECT_TRUE(result);
}

#pragma endregion
#pragma region comparison operators

TEST(FractionTest, operatorEqual_WhenSameNormalizedFraction_ThenTrue)
{
    // when
    bool result = alma::fraction(9, 15) == alma::fraction(3, 5);
    // then
    EXPECT_TRUE(result);
}

TEST(FractionTest, operatorEqual_WhenEqualToInt_ThenTrue)
{
    // when
    bool result1 = alma::fraction(125, 5) == 25;
    bool result2 = 25 == alma::fraction(125, 5);
    // then
    EXPECT_TRUE(result1);
    EXPECT_TRUE(result2);
}

TEST(FractionTest, operatorNotEqual_WhenDifferentFraction_ThenTrue)
{
    // when
    bool result = alma::fraction(9, 14) != alma::fraction(3, 5);
    // then
    EXPECT_TRUE(result);
}

TEST(FractionTest, operatorLess_WhenSameDenominatorAndGreaterNumerator_ThenTrue)
{
    // when
    bool result = alma::fraction(9, 14) < alma::fraction(17, 14);
    // then
    EXPECT_TRUE(result);
}

TEST(FractionTest, operatorLess_WhenLessThanInt_ThenTrue)
{
    // when
    bool result = alma::fraction(-31, 6) < -4;
    // then
    EXPECT_TRUE(result);
}

TEST(FractionTest, operatorGreater_WhenSameNumeratorAndGreaterDenominator_ThenTrue)
{
    // when
    bool result = alma::fraction(9, 14) > alma::fraction(9, 26);
    // then
    EXPECT_TRUE(result);
}

TEST(FractionTest, operatorGreater_WhenGreaterThanLongLong_ThenTrue)
{
    // when
    bool result = alma::fraction(11, 3) > 2LL;
    // then
    EXPECT_TRUE(result);
}

#pragma endregion
#pragma region unary operators

TEST(FractionTest, operatorUnaryPlus_ThenCopied)
{
    // given
    alma::fraction frac(7, 19);
    // when
    alma::fraction result = +frac;
    // then
    EXPECT_EQ(frac, result);
}

TEST(FractionTest, operatorUnaryMinus_WhenPositive_ThenNegative)
{
    // given
    alma::fraction frac(7, 19);
    // when
    alma::fraction result = -frac;
    // then
    EXPECT_EQ(alma::fraction(-7, 19), result);
}

TEST(FractionTest, operatorUnaryMinus_WhenNegative_ThenPositive)
{
    // given
    alma::fraction frac(-7, 19);
    // when
    alma::fraction result = -frac;
    // then
    EXPECT_EQ(alma::fraction(7, 19), result);
}

TEST(FractionTest, operatorUnaryMinus_WhenZero_ThenZero)
{
    // given
    alma::fraction frac(0);
    // when
    alma::fraction result = -frac;
    // then
    EXPECT_EQ(alma::fraction(0), result);
}

TEST(FractionTest, operatorTilde_WhenPositive_ThenInversed)
{
    // given
    alma::fraction frac(7, 19);
    // when
    alma::fraction result = ~frac;
    // then
    EXPECT_EQ(alma::fraction(19, 7), result);
}

TEST(FractionTest, operatorTilde_WhenNegative_ThenInversed)
{
    // given
    alma::fraction frac(-7, 19);
    // when
    alma::fraction result = ~frac;
    // then
    EXPECT_EQ(alma::fraction(-19, 7), result);
}

TEST(FractionTest, operatorTilde_WhenZero_ThenDomainError)
{
    // given
    alma::fraction frac(0);
    // when
    auto exec = [&]() { return ~frac; };
    // then
    EXPECT_THROW(exec(), std::domain_error);
}

#pragma endregion
#pragma region binary operators

TEST(FractionTest, operatorPlus_ThenDenominatorEqualsLcm)
{
    // when
    alma::fraction result = alma::fraction(1, 2) + alma::fraction(5, 7);
    // then
    EXPECT_EQ(alma::fraction(17, 14), result);
}

TEST(FractionTest, operatorPlus_WhenInt_ThenAdded)
{
    // when
    alma::fraction result1 = alma::fraction(7, 3) + 4;
    alma::fraction result2 = 4 + alma::fraction(7, 3);
    // then
    ASSERT_EQ(alma::fraction(19, 3), result1);
    EXPECT_EQ(result1, result2);
}

TEST(FractionTest, operatorMinus_ThenNormalized)
{
    // when
    alma::fraction result = alma::fraction(1, 2) - alma::fraction(3, 10);
    // then
    EXPECT_EQ(alma::fraction(1, 5), result);
}

TEST(FractionTest, operatorMinus_WhenInt_ThenSubtracted)
{
    // when
    alma::fraction result1 = alma::fraction(7, 3) - 4;
    alma::fraction result2 = 4 - alma::fraction(7, 3);
    // then
    EXPECT_EQ(alma::fraction(-5, 3), result1);
    EXPECT_EQ(alma::fraction(5, 3), result2);
}

TEST(FractionTest, operatorAsterisk_ThenNormalized)
{
    // when
    alma::fraction result = alma::fraction(3, 7) * alma::fraction(5, 12);
    // then
    EXPECT_EQ(alma::fraction(5, 28), result);
}

TEST(FractionTest, operatorAsterisk_WhenInt_ThenMultiplied)
{
    // when
    alma::fraction result1 = alma::fraction(7, 3) * 4;
    alma::fraction result2 = 4 * alma::fraction(7, 3);
    // then
    ASSERT_EQ(alma::fraction(28, 3), result1);
    EXPECT_EQ(result1, result2);
}

TEST(FractionTest, operatorSlash_ThenNormalized)
{
    // when
    alma::fraction result = alma::fraction(9, 14) / alma::fraction(2, 5);
    // then
    EXPECT_EQ(alma::fraction(45, 28), result);
}

TEST(FractionTest, operatorSlash_WhenZero_ThenDomainError)
{
    // when
    auto exec = []() { return alma::fraction(9, 14) / alma::fraction(0); };
    // then
    EXPECT_THROW(exec(), std::domain_error);
}

TEST(FractionTest, operatorSlash_WhenInt_ThenDivided)
{
    // when
    alma::fraction result1 = alma::fraction(7, 3) / 4;
    alma::fraction result2 = 4 / alma::fraction(7, 3);
    // then
    EXPECT_EQ(alma::fraction(7, 12), result1);
    EXPECT_EQ(alma::fraction(12, 7), result2);
}

#pragma endregion

TEST(FractionTest, ostream_operatorShiftLeft_ThenStringRepresentation)
{
    // given
    alma::fraction frac(129, -20);
    std::ostringstream stream;
    // when
    stream << frac;
    // then
    EXPECT_EQ("-129/20", stream.str());
}
