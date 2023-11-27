/**!
 * \file equation_system_test.cpp
 * \brief Tests: Structure of linear equations system.
 */
#include <gtest/gtest.h>
#include "algolib/maths/equation_system.hpp"

namespace alma = algolib::maths;

TEST(EquationSystemTest, operatorLeftShift_ThenStringRepresentation)
{
    // given
    alma::equation_system<3> test_object(
            {alma::equation<3>({2, 3, -2}, 15), alma::equation<3>({7, -1, 0}, 4),
             alma::equation<3>({-1, 6, 4}, 9)});
    std::ostringstream stream;
    // when
    stream << test_object;
    // then
    EXPECT_EQ(
            "{ 2 x_0 + 3 x_1 + -2 x_2 = 15 ; 7 x_0 + -1 x_1 = 4 ; -1 x_0 + 6 x_1 + 4 x_2 = 9 }",
            stream.str());
}

TEST(EquationSystemTest, solve_WhenSingleSolution_ThenSolution)
{
    // given
    alma::equation_system<3> test_object(
            {alma::equation<3>({2, 3, -2}, 15), alma::equation<3>({7, -1, 0}, 4),
             alma::equation<3>({-1, 6, 4}, 9)});
    // when
    std::array<double, 3> result = test_object.solve();
    // then
    ASSERT_EQ((std::array<double, 3>{1, 3, -2}), result);
    EXPECT_TRUE(test_object.has_solution(result));
    EXPECT_FALSE(test_object.has_solution({-2, -18, -36.5}));
}

TEST(EquationSystemTest, solve_WhenNoSolution_ThenNoSolutionError)
{
    // given
    alma::equation_system<3> test_object(
            {alma::equation<3>({2, 3, -2}, 15), alma::equation<3>({7, -1, 0}, 4),
             alma::equation<3>({-1, -1.5, 1}, -1)});
    // when
    auto exec = [&]() { test_object.solve(); };
    // then
    ASSERT_THROW(exec(), alma::no_solution_error);
    EXPECT_FALSE(test_object.has_solution({1, 3, -2}));
    EXPECT_FALSE(test_object.has_solution({-2, -18, -36.5}));
}

TEST(EquationSystemTest, solve_WhenInfiniteSolutions_ThenInfiniteSolutionsError)
{
    // given
    alma::equation_system<3> test_object(
            {alma::equation<3>({2, 3, -2}, 15), alma::equation<3>({7, -1, 0}, 4),
             alma::equation<3>({4, 6, -4}, 30)});
    // when
    auto exec = [&]() { test_object.solve(); };
    // then
    ASSERT_THROW(exec(), alma::infinite_solutions_error);
    EXPECT_TRUE(test_object.has_solution({1, 3, -2}));
    EXPECT_TRUE(test_object.has_solution({-2, -18, -36.5}));
}
