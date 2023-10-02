/*!
 * \file vector_2d_test.cpp
 * \brief Tests: Structure of vector in 2D.
 */
#include <gtest/gtest.h>
#include "algolib/geometry/dim2/vector_2d.hpp"

namespace alge2 = algolib::geometry::dim2;

const double offset = alge2::vector_2d::epsilon;

TEST(Vector2DTest, constructor_WhenArgumentsArePoints_ThenVectorFromBeginToEnd)
{
    // when
    alge2::vector_2d result =
            alge2::vector_2d(alge2::point_2d(2.4, 7.8), alge2::point_2d(-1.5, 13.2));
    // then
    EXPECT_EQ(alge2::vector_2d(-3.9, 5.4), result);
}

TEST(Vector2DTest, coordinates_ThenArray)
{
    // when
    std::array<double, 2> result = alge2::vector_2d(5.0, -19.0).coordinates();
    // then
    EXPECT_EQ((std::array<double, 2>{5.0, -19.0}), result);
}

TEST(Vector2DTest, dot_ThenScalarProduct)
{
    // when
    double result = alge2::vector_2d::dot(alge2::vector_2d(1.5, -4.0), alge2::vector_2d(9.0, -2.5));
    // then
    EXPECT_NEAR(23.5, result, offset);
}

TEST(Vector2DTest, dot_WhenOrthogonal_ThenZero)
{
    // when
    double result = alge2::vector_2d::dot(alge2::vector_2d(1.0, 0.0), alge2::vector_2d(0.0, -2.0));
    // then
    EXPECT_NEAR(0.0, result, offset);
}

TEST(Vector2DTest, area_ThenLengthOfCrossProduct)
{
    // when
    double result =
            alge2::vector_2d::area(alge2::vector_2d(1.5, -4.0), alge2::vector_2d(9.0, -2.5));
    // then
    EXPECT_NEAR(32.25, result, offset);
}

TEST(Vector2DTest, area_WhenParallel_ThenZero)
{
    // when
    double result =
            alge2::vector_2d::area(alge2::vector_2d(3.0, 3.0), alge2::vector_2d(-8.0, -8.0));
    // then
    EXPECT_NEAR(0.0, result, offset);
}

TEST(Vector2DTest, length_ThenLengthOfVector)
{
    // when
    double result = alge2::vector_2d(8.0, -6.0).length();
    // then
    EXPECT_NEAR(10.0, result, offset);
}

TEST(Vector2DTest, plus_ThenCopy)
{
    // given
    alge2::vector_2d vec(5.4, -9.0);
    // when
    alge2::vector_2d result = +vec;
    // then
    EXPECT_EQ(vec, result);
}

TEST(Vector2DTest, minus_ThenNegateEachCoordinate)
{
    // when
    alge2::vector_2d result = -alge2::vector_2d(5.4, -9.0);
    // then
    EXPECT_EQ(alge2::vector_2d(-5.4, 9.0), result);
}

TEST(Vector2DTest, add_ThenAddEachCoordinate)
{
    // when
    alge2::vector_2d result = alge2::vector_2d(5.4, 9.0) + alge2::vector_2d(7.9, -8.1);
    // then
    EXPECT_EQ(alge2::vector_2d(13.3, 0.9), result);
}

TEST(Vector2DTest, subtract_ThenSubtractEachCoordinate)
{
    // when
    alge2::vector_2d result = alge2::vector_2d(5.4, 9.0) - alge2::vector_2d(7.9, -8.1);
    // then
    EXPECT_EQ(alge2::vector_2d(-2.5, 17.1), result);
}

TEST(Vector2DTest, multiply_ThenMultiplyEachCoordinate)
{
    // when
    alge2::vector_2d result = alge2::vector_2d(5.4, 9.0) * 3;
    // then
    EXPECT_EQ(alge2::vector_2d(16.2, 27.0), result);
}

TEST(Vector2DTest, multiply_WhenMultiplicationByZero_ThenZeroVector)
{
    // when
    alge2::vector_2d result = alge2::vector_2d(5.4, 9.0) * 0;
    // then
    EXPECT_EQ(alge2::vector_2d(0.0, 0.0), result);
}

TEST(Vector2DTest, divide_ThenDivideEachCoordinate)
{
    // when
    alge2::vector_2d result = alge2::vector_2d(5.4, 9.0) / 3;
    // then
    EXPECT_EQ(alge2::vector_2d(1.8, 3.0), result);
}

TEST(Vector2DTest, divide_WhenDivisionByZero_ThenDomainError)
{
    // when
    auto exec = [&]() { return alge2::vector_2d(1.0, 1.0) / 0; };
    // then
    EXPECT_THROW(exec(), std::domain_error);
}
