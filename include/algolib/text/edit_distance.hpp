/**!
 * \file edit distance.hpp
 * \brief Algorithms for edit distance.
 */
#ifndef EDIT_DISTANCE_HPP_
#define EDIT_DISTANCE_HPP_

#include <cmath>
#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <string>
#include <vector>

namespace algolib::text
{
    /*!
     * \brief Computes cost of Levenshtein edit distance between given texts.
     * \param source the initial text
     * \param destination the final text
     * \param insertion_cost the cost of insertion operation
     * \param deletion_cost the cost of deletion operation
     * \param substitution_cost the cost of substitution operation
     * \return the cost of edit distance
     */
    double count_levenshtein(
            const std::string & source,
            const std::string & destination,
            double insertion_cost = 1.0,
            double deletion_cost = 1.0,
            double substitution_cost = 1.0);

    /*!
     * \brief Computes cost of LCS edit distance between given texts.
     * \param source the initial text
     * \param destination the final text
     * \param insertion_cost the cost of insertion operation
     * \param deletion_cost the cost of deletion operation
     * \return the cost of edit distance
     */
    double count_lcs(
            const std::string & source,
            const std::string & destination,
            double insertion_cost = 1.0,
            double deletion_cost = 1.0);

    /*!
     * \brief Computes cost of Hamming edit distance between given texts of equal length.
     * \param source the initial text
     * \param destination the final text
     * \param substitution_cost the cost of substitution operation
     * \return the cost of edit distance
     */
    double count_hamming(
            const std::string & source,
            const std::string & destination,
            double substitution_cost = 1.0);
}

#endif
