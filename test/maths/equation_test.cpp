/**!
 * \file equation_test.cpp
 * \brief Tests: Structure of linear equation.
 */
#include <sstream>
#include <gtest/gtest.h>
#include "algolib/maths/equation.hpp"

namespace alma = algolib::maths;

template <size_t N>
std::array<double, N> coefficients(alma::equation<N> eq)
{
    std::array<double, N> result;

    for(size_t i = 0; i < N; ++i)
        result[i] = eq[i];

    return result;
}

class EquationTest : public ::testing::Test
{
protected:
    alma::equation<4> test_object;

public:
    EquationTest() : test_object{alma::equation<4>({2, 3, 0, -2.5}, 15)}
    {
    }

    virtual ~EquationTest() = default;
};

TEST_F(EquationTest, operatorUnaryPlus_ThenCopied)
{
    // when
    alma::equation<4> result = +test_object;
    // then
    EXPECT_EQ(coefficients(test_object), coefficients(result));
    EXPECT_EQ(test_object.free_term(), result.free_term());
}

TEST_F(EquationTest, operatorUnaryMinus_ThenNegated)
{
    // when
    alma::equation<4> result = -test_object;
    // then
    EXPECT_EQ((std::array<double, 4>{-2, -3, 0, 2.5}), coefficients(result));
    EXPECT_EQ(-15, result.free_term());
}

TEST_F(EquationTest, operatorPlus_ThenAddingEquations)
{
    // when
    alma::equation<4> result = test_object + alma::equation<4>({1, -1, 4, 10}, 5);
    // then
    EXPECT_EQ((std::array<double, 4>{3, 2, 4, 7.5}), coefficients(result));
    EXPECT_EQ(20, result.free_term());
}

TEST_F(EquationTest, operatorMinus_ThenSubtractingEquations)
{
    // when
    alma::equation<4> result = test_object - alma::equation<4>({1, -1, 4, 10}, 5);
    // then
    EXPECT_EQ((std::array<double, 4>{1, 4, -4, -12.5}), coefficients(result));
    EXPECT_EQ(10, result.free_term());
}

TEST_F(EquationTest, operatorAsterisk_WhenConstantIsNonZero_ThenMultiplyingEachCoefficient)
{
    // when
    alma::equation<4> result = test_object * 2;
    // then
    EXPECT_EQ((std::array<double, 4>{4, 6, 0, -5}), coefficients(result));
    EXPECT_EQ(30, result.free_term());
}

TEST_F(EquationTest, operatorAsterisk_WhenConstantIsZero_ThenDomainError)
{
    // when
    auto exec = [&]() { return 0 * test_object; };
    // then
    EXPECT_THROW(exec(), std::domain_error);
}

TEST_F(EquationTest, operatorSlash_WhenConstantIsNonZero_ThenDividingEachCoefficient)
{
    // when
    alma::equation<4> result = test_object / -2;
    // then
    EXPECT_EQ((std::array<double, 4>{-1, -1.5, 0, 1.25}), coefficients(result));
    EXPECT_EQ(-7.5, result.free_term());
}

TEST_F(EquationTest, operatorSlash_WhenConstantIsZero_ThenDomainError)
{
    // when
    auto exec = [&]() { return test_object / 0; };
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
    EXPECT_EQ("2 x_0 + 3 x_1 + -2.5 x_3 = 15", stream.str());
}

TEST_F(EquationTest, hasSolution_WhenSolution_ThenTrue)
{
    // when
    bool result = test_object.has_solution({10, 10, -29, 14});
    // then
    EXPECT_TRUE(result);
}

TEST_F(EquationTest, hasSolution_WhenNotSolution_ThenFalse)
{
    // when
    bool result = test_object.has_solution({10, 6, -17, 14});
    // then
    EXPECT_FALSE(result);
}
