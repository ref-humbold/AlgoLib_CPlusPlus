/*!
 * \file angle_2d_test.cpp
 * \brief Tests: Structure of angle in 2D.
 */
#include <gtest/gtest.h>
#include "algolib/geometry/dim2/angle_2d.hpp"

namespace alge2 = algolib::geometry::dim2;

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
