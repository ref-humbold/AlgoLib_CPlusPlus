/**!
 * \file equation_system_test.cpp
 * \brief Tests: Structure of linear equation system with Gauss elimination algorithm
 */
#include <gtest/gtest.h>
#include "algolib/mathmat/equation_system.hpp"

namespace alma = algolib::mathmat;

class EquationSystemTest : public ::testing::Test
{
protected:
    alma::equation_system<3> test_object;

public:
    EquationSystemTest()
        : test_object{alma::equation_system<3>({alma::equation<3>({2, 3, -2}, 15),
                                                alma::equation<3>({7, -1, 0}, 4),
                                                alma::equation<3>({-1, 6, 4}, 9)})}
    {
    }

    virtual ~EquationSystemTest() = default;
};

TEST_F(EquationSystemTest, solve_whenSingleSolution_thenSolution)
{
    // when
    std::array<double, 3> result = test_object.solve();
    // then
    ASSERT_EQ((std::array<double, 3>{1, 3, -2}), result);
    EXPECT_TRUE(test_object.is_solution(result));
    EXPECT_FALSE(test_object.is_solution({-2, -18, -36.5}));
}

TEST_F(EquationSystemTest, solve_whenNoSolution_thenThrowNoSolutionException)
{
    // given
    test_object = alma::equation_system<3>({alma::equation<3>({2, 3, -2}, 15),
                                            alma::equation<3>({7, -1, 0}, 4),
                                            alma::equation<3>({-1, -1.5, 1}, -1)});

    // when - then
    ASSERT_THROW(test_object.solve(), alma::no_solution_exception);
    EXPECT_FALSE(test_object.is_solution({1, 3, -2}));
    EXPECT_FALSE(test_object.is_solution({-2, -18, -36.5}));
}

TEST_F(EquationSystemTest, solve_whenInfiniteSolutions_thenThrowInfiniteSolutionsException)
{
    // given
    test_object = alma::equation_system<3>({alma::equation<3>({2, 3, -2}, 15),
                                            alma::equation<3>({7, -1, 0}, 4),
                                            alma::equation<3>({4, 6, -4}, 30)});

    // when - then
    ASSERT_THROW(test_object.solve(), alma::infinite_solutions_exception);
    EXPECT_TRUE(test_object.is_solution({1, 3, -2}));
    EXPECT_TRUE(test_object.is_solution({-2, -18, -36.5}));
}
