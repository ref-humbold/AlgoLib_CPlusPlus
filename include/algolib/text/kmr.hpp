/*!
 * \file kmr.hpp
 * \brief Karp-Miller-Rosenberg algorithm
 */
#ifndef _KMR_HPP_
#define _KMR_HPP_

#include <cstdlib>
#include <algorithm>
#include <map>
#include <string>
#include <tuple>
#include <vector>

namespace algolib::text
{
    /*!
         * \brief Builds a base words dictionary for specified text using Karp-Miller-Rosenberg algorithm.
         *
         * \param text a text
         * \return base words dictionary
         */
    std::map<std::string, int> kmr(const std::string & text);
}

#endif
