/**
 * @file kmr.hpp
 * @brief Karp-Miller-Rosenberg algorithm.
 */
#ifndef _KMR_HPP_
#define _KMR_HPP_

#include <cstdlib>
#include <algorithm>
#include <map>
#include <string>
#include <tuple>
#include <vector>

namespace impl
{
    /**
     * Budowa podsłów złożonych z pojedynczych znaków.
     * @param text słowo
     * @return słownik podsłów bazowych
     */
    std::map<std::string, int> sign_letters(const std::string & text);

    /**
     * Budowa nowych podsłów o podwojonej długości.
     * @param new_length nowa długość podsłów
     */
    void double_length(int new_length, const std::string & text,
                       std::map<std::string, int> & factors);
}

namespace algolib
{
    namespace text
    {
        /**
         * Budowa słownika podsłów bazowych.
         * @param text słowo
         * @return słownik podsłów bazowych
         */
        std::map<std::string, int> kmr(const std::string & text);
    }
}

#endif
