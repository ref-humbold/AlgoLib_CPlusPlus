/**!
 * \file primes.hpp
 * \brief Algorithms for prime numbers
 */
#ifndef PRIMES_HPP_
#define PRIMES_HPP_

#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include "maths.hpp"

namespace algolib
{
    namespace mathmat
    {
        /**!
         * \brief Wyznaczanie liczb pierwszych na przedziale domkniętym
         * \param min_number dolna granica przedziału
         * \param max_number górna granica przedziału
         * \return lista liczb pierwszych
         */
        std::vector<size_t> find_primes(size_t min_number, size_t max_number);

        /**!
         * \brief Wyznaczanie liczb pierwszych od zera
         * \param max_number górna granica
         * \return lista liczb pierwszych
         */
        inline std::vector<size_t> find_primes(size_t max_number)
        {
            return find_primes(0, max_number);
        }

        /**!
         * \brief Test pierwszości Fermata
         * \param number testowana liczba
         * \return czy liczba prawdopodobnie jest pierwsza
         */
        bool test_fermat(long long int number);

        /**!
         * \brief Test pierwszości Millera-Rabina
         * \param number testowana liczba
         * \return czy liczba prawdopodobnie jest pierwsza
         */
        bool test_miller(long long int number);
    }
}

#endif
