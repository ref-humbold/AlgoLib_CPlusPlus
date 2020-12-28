/**!
 * \file equation_test.cpp
 * \brief Tests: Structure of linear equation
 */
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

TEST_F(EquationTest, imul_WhenConstantIsNonZero_ThenMultiplied)
{
    // when
    test_object *= 2;
    // then
    EXPECT_EQ((std::array<double, 4>{4, 6, 0, -4}), test_object.coefficients);
    EXPECT_EQ(30, test_object.free);
}

TEST_F(EquationTest, imul_WhenConstantIsZero_ThenDomainError)
{
    // when - then
    EXPECT_THROW(test_object *= 0, std::domain_error);
}

TEST_F(EquationTest, combine_WhenConstantIsNonZero_ThenCombined)
{
    // when
    test_object.combine(alma::equation<4>({1, -1, 4, 10}, 5), -2);
    // then
    EXPECT_EQ((std::array<double, 4>{0, 5, -8, -22}), test_object.coefficients);
    EXPECT_EQ(5, test_object.free);
}

TEST_F(EquationTest, combine_WhenNoConstant_ThenAddEquation)
{
    // when
    test_object.combine(alma::equation<4>({1, -1, 4, 10}, 5));
    // then
    EXPECT_EQ((std::array<double, 4>{3, 2, 4, 8}), test_object.coefficients);
    EXPECT_EQ(20, test_object.free);
}

TEST_F(EquationTest, combine_WhenConstantIsZero_ThenDomainError)
{
    // when - then
    EXPECT_THROW(test_object.combine(alma::equation<4>({1, -1, 10, 7}, 5), 0), std::domain_error);
}
