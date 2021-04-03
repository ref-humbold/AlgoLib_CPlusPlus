/**!
 * \file equation_test.cpp
 * \brief Tests: Structure of linear equation
 */
#include <sstream>
#include <gtest/gtest.h>
#include "algolib/mathmat/equation.hpp"

namespace alma = algolib::mathmat;

class EquationTest : public ::testing::Test
{
protected:
    alma::equation<4> test_object;

public:
    EquationTest() : test_object{alma::equation<4>({2, 3, 0, -2}, 15)}
    {
    }

    virtual ~EquationTest() = default;
};

TEST_F(EquationTest, operatorPlus_ThenAddingEquations)
{
    // when
    alma::equation<4> result = test_object + alma::equation<4>({1, -1, 4, 10}, 5);
    // then
    EXPECT_EQ((std::array<double, 4>{3, 2, 4, 8}), result.coefficients);
    EXPECT_EQ(20, result.free);
}

TEST_F(EquationTest, operatorMinus_ThenSubtractingEquations)
{
    // when
    alma::equation<4> result = test_object - alma::equation<4>({1, -1, 4, 10}, 5);
    // then
    EXPECT_EQ((std::array<double, 4>{1, 4, -4, -12}), result.coefficients);
    EXPECT_EQ(10, result.free);
}

TEST_F(EquationTest, operatorAsterisk_WhenConstantIsNonZero_ThenMultiplyingEquations)
{
    // when
    alma::equation<4> result = test_object * 2;
    // then
    EXPECT_EQ((std::array<double, 4>{4, 6, 0, -4}), result.coefficients);
    EXPECT_EQ(30, result.free);
}

TEST_F(EquationTest, operatorAsterisk_WhenConstantIsZero_ThenDomainError)
{
    // when
    auto exec = [&]() { return test_object * 0; };
    // then
    EXPECT_THROW(exec(), std::domain_error);
}

TEST_F(EquationTest, operatorSlash_WhenConstantIsNonZero_ThenDividingEquations)
{
    // when
    alma::equation<4> result = test_object / -2;
    // then
    EXPECT_EQ((std::array<double, 4>{-1, -1.5, 0, 1}), result.coefficients);
    EXPECT_EQ(-7.5, result.free);
}

TEST_F(EquationTest, operatorSlash_WhenConstantIsZero_ThenDomainError)
{
    // when
    auto exec = [&]() { return test_object / 0; };
    // then
    EXPECT_THROW(exec(), std::domain_error);
}

TEST_F(EquationTest, combine_WhenConstantIsNonZero_ThenCombined)
{
    // when
    test_object.combine(alma::equation<4>({1, -1, 4, 10}, 5), -2);
    // then
    EXPECT_EQ((std::array<double, 4>{0, 5, -8, -22}), test_object.coefficients);
    EXPECT_EQ(5, test_object.free);
}

TEST_F(EquationTest, combine_WhenConstantIsZero_ThenDomainError)
{
    // when
    auto exec = [&]() { return test_object.combine(alma::equation<4>({1, -1, 10, 7}, 5), 0); };
    // then
    EXPECT_THROW(exec(), std::domain_error);
}

TEST_F(EquationTest, operatorLeftShift_ThenStringRepresentation)
{
    // given
    std::ostringstream stream;
    // when
    stream << test_object;
    // then
    EXPECT_EQ("2 x_0 + 3 x_1 + -2 x_3 = 15", stream.str());
}
