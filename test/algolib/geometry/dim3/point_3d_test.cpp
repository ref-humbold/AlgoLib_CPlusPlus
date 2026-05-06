/*!
 * \file point_3d_test.cpp
 * \brief Tests: Structure of point in 3D.
 */
#include <gtest/gtest.h>
#include "algolib/geometry/dim3/point_3d.hpp"

namespace alge3 = algolib::geometry::dim3;

constexpr double offset = 1e-12;

struct PointExpectedParams
{
    PointExpectedParams(const alge3::point_3d & point, double expected)
        : point{point}, expected{expected}
    {
    }

    const alge3::point_3d point;
    const double expected;
};

class Point3DTest_Radius : public testing::TestWithParam<PointExpectedParams>
{
};

INSTANTIATE_TEST_SUITE_P(
        ,
        Point3DTest_Radius,
        testing::Values(
                PointExpectedParams(alge3::point_3d::zero, 0.0),
                PointExpectedParams(alge3::point_3d(14.0, 0.0, 0.0), 14.0),
                PointExpectedParams(alge3::point_3d(-14.0, 0.0, 0.0), 14.0),
                PointExpectedParams(alge3::point_3d(0.0, 14.0, 0.0), 14.0),
                PointExpectedParams(alge3::point_3d(0.0, -14.0, 0.0), 14.0),
                PointExpectedParams(alge3::point_3d(0.0, 0.0, 14.0), 14.0),
                PointExpectedParams(alge3::point_3d(0.0, 0.0, -14.0), 14.0),
                PointExpectedParams(alge3::point_3d(8.0, 6.0, 0.0), 10.0),
                PointExpectedParams(alge3::point_3d(8.0, -6.0, 0.0), 10.0),
                PointExpectedParams(alge3::point_3d(-8.0, 6.0, 0.0), 10.0),
                PointExpectedParams(alge3::point_3d(-8.0, -6.0, 0.0), 10.0),
                PointExpectedParams(alge3::point_3d(8.0, 0.0, 6.0), 10.0),
                PointExpectedParams(alge3::point_3d(8.0, 0.0, -6.0), 10.0),
                PointExpectedParams(alge3::point_3d(-8.0, 0.0, 6.0), 10.0),
                PointExpectedParams(alge3::point_3d(-8.0, 0.0, -6.0), 10.0),
                PointExpectedParams(alge3::point_3d(0.0, 8.0, 6.0), 10.0),
                PointExpectedParams(alge3::point_3d(0.0, 8.0, -6.0), 10.0),
                PointExpectedParams(alge3::point_3d(0.0, -8.0, 6.0), 10.0),
                PointExpectedParams(alge3::point_3d(0.0, -8.0, -6.0), 10.0),
                PointExpectedParams(alge3::point_3d(18.0, 6.0, 13.0), 23.0),
                PointExpectedParams(alge3::point_3d(18.0, 6.0, -13.0), 23.0),
                PointExpectedParams(alge3::point_3d(18.0, -6.0, 13.0), 23.0),
                PointExpectedParams(alge3::point_3d(18.0, -6.0, -13.0), 23.0),
                PointExpectedParams(alge3::point_3d(-18.0, 6.0, 13.0), 23.0),
                PointExpectedParams(alge3::point_3d(-18.0, 6.0, -13.0), 23.0),
                PointExpectedParams(alge3::point_3d(-18.0, -6.0, 13.0), 23.0),
                PointExpectedParams(alge3::point_3d(-18.0, -6.0, -13.0), 23.0)));

TEST(Point3DTest, coordinates_ThenArray)
{
    // when
    std::array<double, 3> result =
            alge3::point_3d(150.123456789, -3700.987654321, 0.55555555).coordinates();

    // then
    EXPECT_EQ((std::array<double, 3>{150.123456789, -3700.987654321, 0.55555555}), result);
}

TEST_P(Point3DTest_Radius, radius_ThenDistanceFromZeroPoint)
{
    // given
    auto params = GetParam();

    // when
    double result = params.point.radius();

    // then
    EXPECT_NEAR(params.expected, result, offset);
}

TEST(Point3DTest, ostream_operatorShiftLeft_ThenStringRepresentation)
{
    // given
    alge3::point_3d point(150.123456789, -3700.987654321, 0.55555555);
    std::ostringstream stream;

    // when
    stream << point;

    // then
    EXPECT_EQ("(150.123456789, -3700.987654321, 0.55555555)", stream.str());
}
