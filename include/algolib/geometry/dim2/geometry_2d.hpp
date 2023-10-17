/*!
 * \file geometry_2d.hpp
 * \brief Algorithms for basic geometrical operations in 2D.
 */
#ifndef GEOMETRY_2D_HPP_
#define GEOMETRY_2D_HPP_

#include <cmath>
#include <cstdlib>
#include <vector>
#include "algolib/geometry/dim2/point_2d.hpp"
#include "algolib/geometry/dim2/vector_2d.hpp"

namespace algolib::geometry::dim2
{
    /*!
     * \brief Mutably sorts given points by their X coordinate. Sorting is guaranteed to be stable.
     * \param points the points
     */
    void sort_by_x(std::vector<point_2d> & points);

    /*!
     * \brief Mutably sorts given points by their Y coordinate. Sorting is guaranteed to be stable.
     * \param points the points
     */
    void sort_by_y(std::vector<point_2d> & points);

    /*!
     * \brief Mutably sorts given points by their polar coordinates.
     * First sorts by angle, then by radius. Sorting is guaranteed to be stable.
     * \param points the points
     */
    void sort_by_angle(std::vector<point_2d> & points);

    /*!
     * \brief Calculates distance between given points.
    * \param point1 the first point
    * \param point2 the second point
    * \return the distance between the points
    */
    double distance(const point_2d & point1, const point_2d & point2);

    /*!
     * \brief Translates given point by given vector.
     * \param point the point
     * \param vector the vector of translation
     * \return the translated point
     */
    point_2d translate(const point_2d & point, const vector_2d & vector);

    /*!
     * \brief Reflects given point in another point.
     * \param point the point
     * \param centre the point of reflection
     * \return the reflected point
     */
    point_2d reflect(const point_2d & point, const point_2d & centre);
}

#endif
