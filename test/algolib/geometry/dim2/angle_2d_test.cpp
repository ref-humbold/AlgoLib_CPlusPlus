/*!
 * \file angle_2d_test.cpp
 * \brief Tests: Structure of angle in 2D.
 */
#include <numbers>
#include <gtest/gtest.h>
#include "algolib/geometry/dim2/angle_2d.hpp"

namespace alge2 = algolib::geometry::dim2;

constexpr double offset = 1e-6;

struct AngleParams
{
    AngleParams(double radians, double degrees) : radians{radians}, degrees{degrees}
    {
    }

    const double radians;
    const double degrees;
};

class Angle2DTest_DegreesFromRadians : public testing::TestWithParam<AngleParams>
{
};

INSTANTIATE_TEST_SUITE_P(
        ,
        Angle2DTest_DegreesFromRadians,
        testing::Values(
                AngleParams(0.0, 0.0),
                AngleParams(std::numbers::pi / 6, 30.0),
                AngleParams(std::numbers::pi / 4, 45.0),
                AngleParams(std::numbers::pi / 3, 60.0),
                AngleParams(std::numbers::pi / 2, 90.0),
                AngleParams(std::numbers::pi, 180.0),
                AngleParams(2 * std::numbers::pi, 0.0),
                AngleParams(3 * std::numbers::pi, 180.0),
                AngleParams(-std::numbers::pi / 6, 330.0),
                AngleParams(-std::numbers::pi / 4, 315.0),
                AngleParams(-std::numbers::pi / 3, 300.0),
                AngleParams(-std::numbers::pi / 2, 270.0),
                AngleParams(-std::numbers::pi, 180.0),
                AngleParams(-2 * std::numbers::pi, 0.0),
                AngleParams(-3 * std::numbers::pi, 180.0)));

class Angle2DTest_RadiansFromDegrees : public testing::TestWithParam<AngleParams>
{
};

INSTANTIATE_TEST_SUITE_P(
        ,
        Angle2DTest_RadiansFromDegrees,
        testing::Values(
                AngleParams(0.0, 0.0),
                AngleParams(std::numbers::pi / 6, 30.0),
                AngleParams(std::numbers::pi / 4, 45.0),
                AngleParams(std::numbers::pi / 3, 60.0),
                AngleParams(std::numbers::pi / 2, 90.0),
                AngleParams(std::numbers::pi, 180.0),
                AngleParams(0.0, 360.0),
                AngleParams(std::numbers::pi, 540.0),
                AngleParams(11 * std::numbers::pi / 6, -30.0),
                AngleParams(7 * std::numbers::pi / 4, -45.0),
                AngleParams(5 * std::numbers::pi / 3, -60.0),
                AngleParams(3 * std::numbers::pi / 2, -90.0),
                AngleParams(std::numbers::pi, -180.0),
                AngleParams(0.0, -360.0),
                AngleParams(std::numbers::pi, -540.0)));

TEST_P(Angle2DTest_DegreesFromRadians, degrees_WhenFromRadians_ThenPositiveDegreesInRange)
{
    // given
    auto params = GetParam();
    alge2::angle_2d angle(params.radians, alge2::RADIANS);

    // when
    double result = angle.degrees();

    // then
    EXPECT_NEAR(params.degrees, result, offset);
}

TEST_P(Angle2DTest_RadiansFromDegrees, radians_WhenFromDegrees_ThenPositiveRadiansInRange)
{
    // given
    auto params = GetParam();
    alge2::angle_2d angle(params.degrees, alge2::DEGREES);

    // when
    double result = angle.radians();

    // then
    EXPECT_NEAR(params.radians, result, offset);
}

TEST(Angle2DTest, ostream_operatorShiftLeft_ThenStringRepresentation)

{
    // given
    alge2::angle_2d angle(150.123456789, alge2::DEGREES);
    std::ostringstream stream;

    // when
    stream << angle;

    // then
    EXPECT_EQ("Angle<150.123456789 deg>", stream.str());
}
