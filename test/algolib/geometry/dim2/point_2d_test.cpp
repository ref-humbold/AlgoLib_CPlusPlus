/*!
 * \file point_2d_test.cpp
 * \brief Tests: Structure of point in 2D.
 */
#include <gtest/gtest.h>
#include "algolib/geometry/dim2/point_2d.hpp"

namespace alge2 = algolib::geometry::dim2;

constexpr double offset = 1e-12;

struct PointExpectedParams
{
    PointExpectedParams(const alge2::point_2d & point, double expected)
        : point{point}, expected{expected}
    {
    }

    const alge2::point_2d point;
    const double expected;
};

class Point2DTest_Angle : public testing::TestWithParam<PointExpectedParams>
{
};

INSTANTIATE_TEST_SUITE_P(
        ,
        Point2DTest_Angle,
        testing::Values(
                PointExpectedParams(alge2::point_2d::zero, 0.0),
                PointExpectedParams(alge2::point_2d(7.0, 0.0), 0.0),
                PointExpectedParams(alge2::point_2d(7.0, 7.0), 45.0),
                PointExpectedParams(alge2::point_2d(0.0, 7.0), 90.0),
                PointExpectedParams(alge2::point_2d(-7.0, 7.0), 135.0),
                PointExpectedParams(alge2::point_2d(-7.0, 0.0), 180.0),
                PointExpectedParams(alge2::point_2d(-7.0, -7.0), 225.0),
                PointExpectedParams(alge2::point_2d(0.0, -7.0), 270.0),
                PointExpectedParams(alge2::point_2d(7.0, -7.0), 315.0)));

class Point2DTest_Radius : public testing::TestWithParam<PointExpectedParams>
{
};

INSTANTIATE_TEST_SUITE_P(
        ,
        Point2DTest_Radius,
        testing::Values(
                PointExpectedParams(alge2::point_2d::zero, 0.0),
                PointExpectedParams(alge2::point_2d(14.0, 0.0), 14.0),
                PointExpectedParams(alge2::point_2d(-14.0, 0.0), 14.0),
                PointExpectedParams(alge2::point_2d(0.0, 14.0), 14.0),
                PointExpectedParams(alge2::point_2d(0.0, -14.0), 14.0),
                PointExpectedParams(alge2::point_2d(8.0, 6.0), 10.0),
                PointExpectedParams(alge2::point_2d(8.0, -6.0), 10.0),
                PointExpectedParams(alge2::point_2d(-8.0, 6.0), 10.0),
                PointExpectedParams(alge2::point_2d(-8.0, -6.0), 10.0)));

TEST(Point2DTest, coordinates_ThenArray)
{
    // when
    std::array<double, 2> result = alge2::point_2d(150.123456789, -3700.987654321).coordinates();

    // then
    EXPECT_EQ((std::array<double, 2>{150.123456789, -3700.987654321}), result);
}

TEST_P(Point2DTest_Angle, angle_ThenCounterClockwiseAngleFromXAxis)
{
    // given
    auto params = GetParam();

    // when
    alge2::angle_2d result = params.point.angle();

    // then
    EXPECT_EQ(alge2::angle_2d(params.expected, alge2::DEGREES), result);
}

TEST_P(Point2DTest_Radius, radius_ThenDistanceFromZeroPoint)
{
    // given
    auto params = GetParam();

    // when
    double result = params.point.radius();

    // then
    EXPECT_NEAR(params.expected, result, offset);
}

TEST(Point2DTest, ostream_operatorShiftLeft_ThenStringRepresentation)
{
    // given
    alge2::point_2d point(150.123456789, -3700.987654321);
    std::ostringstream stream;

    // when
    stream << point;

    // then
    EXPECT_EQ("(150.123456789, -3700.987654321)", stream.str());
}
