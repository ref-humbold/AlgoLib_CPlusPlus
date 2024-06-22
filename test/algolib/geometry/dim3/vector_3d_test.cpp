/*!
 * \file vector_3d_test.cpp
 * \brief Tests: Structure of vector in 3D.
 */
#include <gtest/gtest.h>
#include "algolib/geometry/dim3/vector_3d.hpp"

namespace alge3 = algolib::geometry::dim3;

const double offset = alge3::vector_3d::epsilon;

TEST(Vector3DTest, constructor_WhenArgumentsArePoints_ThenVectorFromBeginToEnd)
{
    // when
    alge3::vector_3d result =
            alge3::vector_3d(alge3::point_3d(2.4, 7.8, -10.3), alge3::point_3d(-1.5, 13.2, 15.8));

    // then
    EXPECT_EQ(alge3::vector_3d(-3.9, 5.4, 26.1), result);
}

TEST(Vector3DTest, coordinates_ThenArray)
{
    // when
    std::array<double, 3> result = alge3::vector_3d(5.0, -19.0, 14.2).coordinates();

    // then
    EXPECT_EQ((std::array<double, 3>{5.0, -19.0, 14.2}), result);
}

TEST(Vector3DTest, dot_ThenScalarProduct)
{
    // when
    double result = alge3::vector_3d::dot(
            alge3::vector_3d(1.5, -4.0, -3.5), alge3::vector_3d(9.0, -2.5, 8.5));

    // then
    EXPECT_NEAR(-6.25, result, offset);
}

TEST(Vector3DTest, dot_WhenOrthogonal_ThenZero)
{
    // when
    double result = alge3::vector_3d::dot(
            alge3::vector_3d(1.0, 0.0, 1.0), alge3::vector_3d(0.0, -2.0, 0.0));

    // then
    EXPECT_NEAR(0.0, result, offset);
}

TEST(Vector3DTest, cross_ThenCrossProduct)
{
    // when
    alge3::vector_3d result = alge3::vector_3d::cross(
            alge3::vector_3d(1.5, -4.0, -3.5), alge3::vector_3d(9.0, -2.5, 8.5));

    // then
    EXPECT_EQ(alge3::vector_3d(-42.75, -44.25, 32.25), result);
}

TEST(Vector3DTest, cross_WhenParallel_ThenZero)
{
    // when
    alge3::vector_3d result = alge3::vector_3d::cross(
            alge3::vector_3d(3.0, 3.0, 3.0), alge3::vector_3d(-8.0, -8.0, -8.0));

    // then
    EXPECT_EQ(alge3::vector_3d(0.0, 0.0, 0.0), result);
}

TEST(Vector3DTest, area_ThenLengthOfCrossProduct)
{
    // when
    double result = alge3::vector_3d::area(
            alge3::vector_3d(1.5, -4.0, -3.5), alge3::vector_3d(9.0, -2.5, 8.5));

    // then
    EXPECT_NEAR(69.46716850426538, result, offset);
}

TEST(Vector3DTest, area_WhenParallel_ThenZero)
{
    // when
    double result = alge3::vector_3d::area(
            alge3::vector_3d(3.0, 3.0, 3.0), alge3::vector_3d(-8.0, -8.0, -8.0));

    // then
    EXPECT_NEAR(0.0, result, offset);
}

TEST(Vector3DTest, volume_ThenScalarTripleProduct)
{
    // when
    double result = alge3::vector_3d::volume(
            alge3::vector_3d(1.5, -4.0, -3.5), alge3::vector_3d(9.0, -2.5, 8.5),
            alge3::vector_3d(1.0, -1.0, 1.0));

    // then
    EXPECT_NEAR(33.75, result, offset);
}

TEST(Vector3DTest, volume_WhenParallel_ThenZero)
{
    // when
    double result = alge3::vector_3d::volume(
            alge3::vector_3d(3.0, 3.0, 3.0), alge3::vector_3d(-8.0, -8.0, -8.0),
            alge3::vector_3d(2.0, -2.0, 2.0));

    // then
    EXPECT_NEAR(0.0, result, offset);
}

TEST(Vector3DTest, volume_WhenOrthogonal_ThenZero)
{
    // when
    double result = alge3::vector_3d::volume(
            alge3::vector_3d(3.0, 3.0, 3.0), alge3::vector_3d(1.0, 0.0, 1.0),
            alge3::vector_3d(0.0, -2.0, 0.0));

    // then
    EXPECT_NEAR(0.0, result, offset);
}

TEST(Vector3DTest, length_ThenLengthOfVector)
{
    // when
    double result = alge3::vector_3d(18.0, -6.0, 13.0).length();

    // then
    EXPECT_NEAR(23.0, result, offset);
}

TEST(Vector3DTest, plus_ThenCopy)
{
    // given
    alge3::vector_3d vec(5.4, 9.0, -12.3);

    // when
    alge3::vector_3d result = +vec;

    // then
    EXPECT_EQ(vec, result);
}

TEST(Vector3DTest, minus_ThenNegateEachCoordinate)
{
    // when
    alge3::vector_3d result = -alge3::vector_3d(5.4, 9.0, -12.3);

    // then
    EXPECT_EQ(alge3::vector_3d(-5.4, -9.0, 12.3), result);
}

TEST(Vector3DTest, add_ThenAddEachCoordinate)
{
    // when
    alge3::vector_3d result = alge3::vector_3d(5.4, 9.0, -12.3) + alge3::vector_3d(7.9, -8.1, 1.4);

    // then
    EXPECT_EQ(alge3::vector_3d(13.3, 0.9, -10.9), result);
}

TEST(Vector3DTest, subtract_ThenSubtractEachCoordinate)
{
    // when
    alge3::vector_3d result = alge3::vector_3d(5.4, 9.0, -12.3) - alge3::vector_3d(7.9, -8.1, 1.4);

    // then
    EXPECT_EQ(alge3::vector_3d(-2.5, 17.1, -13.7), result);
}

TEST(Vector3DTest, multiply_ThenMultiplyEachCoordinate)
{
    // when
    alge3::vector_3d result = alge3::vector_3d(5.4, 9.0, -12.3) * 3;

    // then
    EXPECT_EQ(alge3::vector_3d(16.2, 27.0, -36.9), result);
}

TEST(Vector3DTest, multiply_WhenMultiplicationByZero_ThenZeroVector)
{
    // when
    alge3::vector_3d result = alge3::vector_3d(5.4, 9.0, -12.3) * 0;

    // then
    EXPECT_EQ(alge3::vector_3d(0.0, 0.0, 0.0), result);
}

TEST(Vector3DTest, divide_ThenDivideEachCoordinate)
{
    // when
    alge3::vector_3d result = alge3::vector_3d(5.4, 9.0, -12.3) / 3;

    // then
    EXPECT_EQ(alge3::vector_3d(1.8, 3.0, -4.1), result);
}

TEST(Vector3DTest, divide_WhenDivisionByZero_ThenDomainError)
{
    // when
    auto exec = [&]() { return alge3::vector_3d(1.0, 1.0, 1.0) / 0; };

    // then
    EXPECT_THROW(exec(), std::domain_error);
}
