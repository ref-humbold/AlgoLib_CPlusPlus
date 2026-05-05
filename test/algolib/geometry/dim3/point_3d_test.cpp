/*!
 * \file point_3d_test.cpp
 * \brief Tests: Structure of point in 3D.
 */
#include <gtest/gtest.h>
#include "algolib/geometry/dim3/point_3d.hpp"

namespace alge3 = algolib::geometry::dim3;

constexpr double offset = 1e-12;

TEST(Point3DTest, coordinates_ThenArray)
{
    // when
    std::array<double, 3> result =
            alge3::point_3d(150.123456789, -3700.987654321, 0.55555555).coordinates();

    // then
    EXPECT_EQ((std::array<double, 3>{150.123456789, -3700.987654321, 0.55555555}), result);
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
