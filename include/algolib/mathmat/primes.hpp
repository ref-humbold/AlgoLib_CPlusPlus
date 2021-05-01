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

namespace algolib::mathmat
{
    /*!
     * \brief Finds prime numbers inside a range of integers.
     * \param minNumber minimal number in range, inclusive
     * \param maxNumber maximal number in range, exclusive
     * \return vector of prime numbers
     */
    std::vector<size_t> find_primes(size_t min_number, size_t max_number);

    /*!
     * \brief Finds prime numbers inside a range of integers starting from 0.
     * \param maxNumber maximal number in range, exclusive
     * \return vector of prime numbers
     */
    inline std::vector<size_t> find_primes(size_t max_number)
    {
        return find_primes(0, max_number);
    }

    /*!
     * \brief Checks whether specified number is prime running Fermat's prime test.
     * \param number number to check
     * \return \c true if the number is probably prime, otherwise \c false
     */
    bool test_fermat(long long number);

    /*!
     * \brief Checks whether specified number is prime running Miller-Rabin's prime test.
     * \param number number to check
     * \return {@code true} if the number is probably prime, otherwise {@code false}
     */
    bool test_miller(long long number);
}

#endif
