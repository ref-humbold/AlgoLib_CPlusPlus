/*!
 * \file geometry_2d.hpp
 * \brief Algorithms for basic geometrical computations in 2D
 */
#ifndef GEOMETRY_2D_HPP_
#define GEOMETRY_2D_HPP_

#include <cmath>
#include <cstdlib>
#include "point_2d.hpp"
#include "vector_2d.hpp"

namespace algolib::geometry::dim2
{
    /*!
     * \brief Mutably sorts points by their X coordinate. Sorting is guaranteed to be stable.
     * \param points vector of points
     */
    void sort_by_x(std::vector<point_2d> & points);

    /*!
     * \brief Mutably sorts points by their Y coordinate. Sorting is guaranteed to be stable.
     * \param points vector of points
     */
    void sort_by_y(std::vector<point_2d> & points);

    /*!
     * \brief Mutably sorts points by their polar coordinates. First sorts by angle, then by radius.
     * Sorting is guaranteed to be stable.
     * \param points vector of points
     */
    void sort_by_angle(std::vector<point_2d> & points);

    /*!
     * \brief Counts the distance between given points.
    * \param point1 first point
    * \param point2 second point
    * \return distance between the points
    */
    double distance(const point_2d & point1, const point_2d & point2);

    /*!
     * \brief Translates given point by given vector.
     * \param point a point
     * \param vector a translation vector
     * \return the translated point
     */
    point_2d translate(const point_2d & point, const vector_2d & vector);

    /*!
     * \brief Reflects given point in another point.
     * \param point a point to be reflected
     * \param centre a reflection point
     * \return the reflected point
     */
    point_2d reflect(const point_2d & point, const point_2d & centre);
}

#endif
