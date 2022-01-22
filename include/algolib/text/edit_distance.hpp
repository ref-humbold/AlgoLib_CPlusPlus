/**!
 * \file edit distance.hpp
 * \brief Algorithms for edit distance
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
     * \param source initial text
     * \param destination final text
     * \param insertion_cost cost of insertion operation
     * \param deletion_cost cost of deletion operation
     * \param substitution_cost cost of substitution operation
     * \return cost of edit distance
     */
    double count_levenshtein(const std::string & source, const std::string & destination,
                             double insertion_cost = 1.0, double deletion_cost = 1.0,
                             double substitution_cost = 1.0);

    /*!
     * \brief Computes cost of LCS edit distance between given texts.
     * \param source initial text
     * \param destination final text
     * \param insertion_cost cost of insertion operation
     * \param deletion_cost cost of deletion operation
     * \return cost of edit distance
     */
    double count_lcs(const std::string & source, const std::string & destination,
                     double insertion_cost = 1.0, double deletion_cost = 1.0);

    /*!
     * \brief Computes cost of Hamming edit distance between given texts of equal length.
     * \param source initial text
     * \param destination final text
     * \param substitution_cost cost of substitution operation
     * \return cost of edit distance
     */
    double count_hamming(const std::string & source, const std::string & destination,
                         double substitution_cost = 1.0);
}

#endif
