/*!
 * \filee kmp.hpp
 * \brief Knuth-Morris-Pratt algorithm
 */
#ifndef KMP_HPP_
#define KMP_HPP_

#include <cstdlib>
#include <algorithm>
#include <string>
#include <vector>

namespace algolib
{
    namespace text
    {
        /*!
         * \brief Knuth-Morris-Pratt algorithm
         * \param text text
         * \param pattern pattern to search for
         * \return vector of pattern occurrence positions
         */
        std::vector<size_t> kmp(const std::string & text, const std::string & pattern);
    }
}

#endif
