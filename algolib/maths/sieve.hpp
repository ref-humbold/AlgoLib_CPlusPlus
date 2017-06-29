// SITO ERASTOTENESA: WYZNACZANIE LICZB PIERWSZYCH
#ifndef SIEVE_HPP
#define SIEVE_HPP

#include <cstdlib>
#include <cmath>
#include <vector>

namespace algolib
{
    namespace maths
    {
        /**
         * Wyznaczanie liczb pierwszych od zera.
         * @param max_number górna granica
         * @return lista liczb pierwszych
         */
        std::vector<int> find_primes(size_t max_number);

        /**
         * Wyznaczanie liczb pierwszych na przedziale domkniętym.
         * @param min_number dolna granica przedziału
         * @param max_number górna granica przedziału
         * @return lista liczb pierwszych
         */
        std::vector<int> find_primes(size_t min_number, size_t max_number);
    }
}

#endif
