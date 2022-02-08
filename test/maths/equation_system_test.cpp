/**!
 * \file equation_system_test.cpp
 * \brief Tests: Structure of linear equation system with Gauss elimination algorithm
 */
#include <gtest/gtest.h>
#include "algolib/maths/equation_system.hpp"

namespace alma = algolib::maths;

TEST(EquationSystemTest, solve_WhenSingleSolution_ThenSolution)
{
    // given
    alma::equation_system<3> test_object({alma::equation<3>({2, 3, -2}, 15),
                                          alma::equation<3>({7, -1, 0}, 4),
                                          alma::equation<3>({-1, 6, 4}, 9)});

    // when
    std::array<double, 3> result = test_object.solve();
    // then
    ASSERT_EQ((std::array<double, 3>{1, 3, -2}), result);
    EXPECT_TRUE(test_object.is_solution(result));
    EXPECT_FALSE(test_object.is_solution({-2, -18, -36.5}));
}

TEST(EquationSystemTest, solve_WhenNoSolution_ThenNoSolutionError)
{
    // given
    alma::equation_system<3> test_object({alma::equation<3>({2, 3, -2}, 15),
                                          alma::equation<3>({7, -1, 0}, 4),
                                          alma::equation<3>({-1, -1.5, 1}, -1)});

    // when - then
    ASSERT_THROW(test_object.solve(), alma::no_solution_error);
    EXPECT_FALSE(test_object.is_solution({1, 3, -2}));
    EXPECT_FALSE(test_object.is_solution({-2, -18, -36.5}));
}

TEST(EquationSystemTest, solve_WhenInfiniteSolutions_ThenInfiniteSolutionsError)
{
    // given
    alma::equation_system<3> test_object({alma::equation<3>({2, 3, -2}, 15),
                                          alma::equation<3>({7, -1, 0}, 4),
                                          alma::equation<3>({4, 6, -4}, 30)});

    // when - then
    ASSERT_THROW(test_object.solve(), alma::infinite_solutions_error);
    EXPECT_TRUE(test_object.is_solution({1, 3, -2}));
    EXPECT_TRUE(test_object.is_solution({-2, -18, -36.5}));
}
