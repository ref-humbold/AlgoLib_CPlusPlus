/*!
 * \file geometry_3d.hpp
 * \brief Algorithms for basic geometrical computations in 2D
 */
#ifndef GEOMETRY_3D_HPP_
#define GEOMETRY_3D_HPP_

#include <cmath>
#include <cstdlib>
#include <vector>
#include "algolib/geometry/dim3/point_3d.hpp"
#include "algolib/geometry/dim3/vector_3d.hpp"

namespace algolib::geometry::dim3
{
    /*!
     * \brief Mutably sorts given points by their X coordinate. Sorting is guaranteed to be stable.
     * \param points vector of points
     */
    void sort_by_x(std::vector<point_3d> & points);

    /*!
     * \brief Mutably sorts given points by their Y coordinate. Sorting is guaranteed to be stable.
     * \param points vector of points
     */
    void sort_by_y(std::vector<point_3d> & points);

    /*!
     * \brief Mutably sorts given points by their Z coordinate. Sorting is guaranteed to be stable.
     * \param points vector of points
     */
    void sort_by_z(std::vector<point_3d> & points);

    /*!
     * \brief Calculates distance between given points.
     * \param point1 the first point
     * \param point2 the second point
     * \return the distance between the points
     */
    double distance(const point_3d & point1, const point_3d & point2);

    /*!
     * \brief Translates given point by given vector.
     * \param point the point
     * \param vector the vector of translation
     * \return the translated point
     */
    point_3d translate(const point_3d & point, const vector_3d & vector);

    /*!
     * \brief Reflects given point in another point.
     * \param point the point
     * \param centre the point of reflection
     * \return the reflected point
     */
    point_3d reflect(const point_3d & point, const point_3d & centre);
}

#endif
