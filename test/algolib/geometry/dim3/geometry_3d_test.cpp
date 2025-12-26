/*!
 * \file geometry_3d_test.cpp
 * \brief Tests: Algorithms for basic geometrical operations in 3D.
 */
#include <gtest/gtest.h>
#include "algolib/geometry/dim3/geometry_3d.hpp"

namespace alge3 = algolib::geometry::dim3;

TEST(Geometry3DTest, sortByX_ThenSortedStablyAscending)
{
    // given
    std::vector<alge3::point_3d> sequence = {alge3::point_3d(0.0, 0.0, 0.0),
        alge3::point_3d(2.0, 3.0, -5.0), alge3::point_3d(-2.0, -3.0, 5.0),
        alge3::point_3d(2.0, -3.0, -5.0), alge3::point_3d(-2.0, -3.0, -5.0),
        alge3::point_3d(3.0, 2.0, 5.0), alge3::point_3d(-3.0, 2.0, 5.0)};

    // when
    alge3::sort_by_x(sequence);

    // then
    EXPECT_EQ(std::vector<alge3::point_3d>({alge3::point_3d(-3.0, 2.0, 5.0),
                  alge3::point_3d(-2.0, -3.0, 5.0), alge3::point_3d(-2.0, -3.0, -5.0),
                  alge3::point_3d(0.0, 0.0, 0.0), alge3::point_3d(2.0, 3.0, -5.0),
                  alge3::point_3d(2.0, -3.0, -5.0), alge3::point_3d(3.0, 2.0, 5.0)}),
            sequence);
}

TEST(Geometry3DTest, sortByY_ThenSortedStablyAscending)
{
    // given
    std::vector<alge3::point_3d> sequence = {alge3::point_3d(0.0, 0.0, 0.0),
        alge3::point_3d(2.0, 3.0, -5.0), alge3::point_3d(-2.0, -3.0, 5.0),
        alge3::point_3d(2.0, -3.0, -5.0), alge3::point_3d(-2.0, -3.0, -5.0),
        alge3::point_3d(3.0, 2.0, 5.0), alge3::point_3d(-3.0, 2.0, 5.0)};

    // when
    alge3::sort_by_y(sequence);

    // then
    EXPECT_EQ(std::vector<alge3::point_3d>({alge3::point_3d(-2.0, -3.0, 5.0),
                  alge3::point_3d(2.0, -3.0, -5.0), alge3::point_3d(-2.0, -3.0, -5.0),
                  alge3::point_3d(0.0, 0.0, 0.0), alge3::point_3d(3.0, 2.0, 5.0),
                  alge3::point_3d(-3.0, 2.0, 5.0), alge3::point_3d(2.0, 3.0, -5.0)}),
            sequence);
}

TEST(Geometry3DTest, sortByZ_ThenSortedStablyAscending)
{
    // given
    std::vector<alge3::point_3d> sequence = {alge3::point_3d(0.0, 0.0, 0.0),
        alge3::point_3d(2.0, 3.0, -5.0), alge3::point_3d(-2.0, -3.0, 5.0),
        alge3::point_3d(2.0, -3.0, -5.0), alge3::point_3d(-2.0, -3.0, -5.0),
        alge3::point_3d(3.0, 2.0, 5.0), alge3::point_3d(-3.0, 2.0, 5.0)};

    // when
    alge3::sort_by_z(sequence);

    // then
    EXPECT_EQ(std::vector<alge3::point_3d>({alge3::point_3d(2.0, 3.0, -5.0),
                  alge3::point_3d(2.0, -3.0, -5.0), alge3::point_3d(-2.0, -3.0, -5.0),
                  alge3::point_3d(0.0, 0.0, 0.0), alge3::point_3d(-2.0, -3.0, 5.0),
                  alge3::point_3d(3.0, 2.0, 5.0), alge3::point_3d(-3.0, 2.0, 5.0)}),
            sequence);
}

TEST(Geometry3DTest, distance_WhenDifferentPoints_ThenDistance)
{
    // when
    double result =
            alge3::distance(alge3::point_3d(4.0, 8.0, 5.0), alge3::point_3d(-2.0, -1.0, 3.0));

    // then
    EXPECT_EQ(11.0, result);
}

TEST(Geometry3DTest, distance_WhenSamePoint_ThenZero)
{
    // given
    alge3::point_3d point(13.5, 6.5, -4.2);

    // when
    double result = alge3::distance(point, point);

    // then
    EXPECT_EQ(0.0, result);
}

TEST(Geometry3DTest, translate_ThenPointTranslated)
{
    // when
    alge3::point_3d result =
            alge3::translate(alge3::point_3d(13.7, 6.5, -4.2), alge3::vector_3d(-10.4, 3.3, 1.1));

    // then
    EXPECT_EQ(alge3::point_3d(3.3, 9.8, -3.1), result);
}

TEST(Geometry3DTest, translate_WhenZeroVector_ThenSamePoint)
{
    // given
    alge3::point_3d point(13.5, 6.5, -4.2);

    // when
    alge3::point_3d result = alge3::translate(point, alge3::vector_3d(0.0, 0.0, 0.0));

    // then
    EXPECT_EQ(point, result);
}
