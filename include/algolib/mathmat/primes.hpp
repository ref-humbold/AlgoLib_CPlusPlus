/**
 * @file primes.hpp
 * ALGORITHMS FOR PRIME NUMBERS
 */
#ifndef PRIMES_HPP_
#define PRIMES_HPP_

#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include "maths.hpp"

namespace detail
{
    /**
     * Rozkładanie liczby do testu Millera-Rabina
     * @param number rozkładana liczba
     * @return rozkład liczby
     */
    std::pair<long long int, long long int> distribute(long long int number);
}

namespace algolib
{
    namespace mathmat
    {
        /**
         * Wyznaczanie liczb pierwszych na przedziale domkniętym.
         * @param min_number dolna granica przedziału
         * @param max_number górna granica przedziału
         * @return lista liczb pierwszych
         */
        std::vector<size_t> find_primes(size_t min_number, size_t max_number);

        /**
         * Wyznaczanie liczb pierwszych od zera.
         * @param max_number górna granica
         * @return lista liczb pierwszych
         */
        inline std::vector<size_t> find_primes(size_t max_number)
        {
            return find_primes(0, max_number);
        }

        /**
         * Test pierwszości Fermata.
         * @param number testowana liczba
         * @return czy liczba prawdopodobnie jest pierwsza
         */
        bool test_fermat(long long int number);

        /**
         * Test pierwszości Millera-Rabina.
         * @param number testowana liczba
         * @return czy liczba prawdopodobnie jest pierwsza
         */
        bool test_miller(long long int number);
    }
}

#endif
