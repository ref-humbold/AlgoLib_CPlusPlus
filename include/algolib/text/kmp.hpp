/*!
 * \file kmp.hpp
 * \brief Knuth-Morris-Pratt algorithm
 */
#ifndef KMP_HPP_
#define KMP_HPP_

#include <cstdlib>
#include <algorithm>
#include <string>
#include <vector>

namespace algolib::text
{
    /*!
     * \brief Searches for pattern occurrences in given text using Knuth-Morris-Pratt algorithm.
     * \param text a text to be searched in
     * \param pattern a pattern to be searched for
     * \return vector of pattern occurrence indices
     */
    std::vector<size_t> kmp(const std::string & text, const std::string & pattern);
}

#endif
