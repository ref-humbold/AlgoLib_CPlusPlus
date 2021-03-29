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
     * \brief Searches for pattern occurrences in specified text using Knuth-Morris-Pratt algorithm.
     * \param text text to be searched in
     * \param pattern pattern to be searched for
     * \return vector of pattern occurrence positions
     */
    std::vector<size_t> kmp(const std::string & text, const std::string & pattern);
}

#endif
