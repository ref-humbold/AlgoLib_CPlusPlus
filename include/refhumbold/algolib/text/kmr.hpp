/*!
 * \file kmr.hpp
 * \brief Karp-Miller-Rosenberg algorithm.
 */
#ifndef _KMR_HPP_
#define _KMR_HPP_

#include <cstdlib>
#include <algorithm>
#include <map>
#include <string>
#include <tuple>
#include <vector>

namespace algolib
{
    namespace text
    {
        /*!
         * \brief Budowa słownika podsłów bazowych.
         * \param text słowo
         * \return słownik podsłów bazowych
         */
        std::map<std::string, int> kmr(const std::string & text);
    }
}

#endif
