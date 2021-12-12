/*!
 * \file knuth_morris_pratt.hpp
 * \brief Knuth-Morris-Pratt algorithm for pattern searching
 */
#ifndef KNUTH_MORRIS_PRATT_HPP_
#define KNUTH_MORRIS_PRATT_HPP_

#include <cstdlib>
#include <algorithm>
#include <string>
#include <vector>

namespace algolib::text
{
    /*!
     * \brief Searches for pattern occurrences in given text using Knuth-Morris-Pratt algorithm.
     * \param text a text
     * \param pattern a pattern
     * \return vector of indices with pattern occurrence
     */
    std::vector<size_t> kmp(const std::string & text, const std::string & pattern);
}

#endif
