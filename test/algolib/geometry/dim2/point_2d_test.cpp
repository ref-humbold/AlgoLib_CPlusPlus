/*!
 * \file point_2d_test.cpp
 * \brief Tests: Structure of point in 2D.
 */
#include <gtest/gtest.h>
#include "algolib/geometry/dim2/point_2d.hpp"

namespace alge2 = algolib::geometry::dim2;

constexpr double offset = 1e-12;

TEST(Point2DTest, coordinates_ThenArray)
{
    // when
    std::array<double, 2> result = alge2::point_2d(150.123456789, -3700.987654321).coordinates();

    // then
    EXPECT_EQ((std::array<double, 2>{150.123456789, -3700.987654321}), result);
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
