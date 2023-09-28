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
     * \param text the text
     * \param pattern the pattern
     * \return the indices with pattern occurrences
     */
    std::vector<size_t> kmp_search(const std::string & text, const std::string & pattern);
}

#endif
