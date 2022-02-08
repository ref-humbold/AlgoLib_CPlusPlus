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
#include "algolib/maths/maths.hpp"

namespace algolib::maths
{
#pragma region find_primes

    /*!
     * \brief Finds prime numbers inside a range of integers.
     * \param min_number minimal number in range, inclusive
     * \param max_number maximal number in range, exclusive
     * \return vector of prime numbers
     */
    std::vector<size_t> find_primes(size_t min_number, size_t max_number);

    /*!
     * \brief Finds prime numbers inside a range of integers starting from 0.
     * \param max_number maximal number in range, exclusive
     * \return vector of prime numbers
     */
    inline std::vector<size_t> find_primes(size_t max_number)
    {
        return find_primes(0, max_number);
    }

#pragma endregion
#pragma region test_fermat

    /*!
     * \brief Checks whether given number is prime running Fermat's prime test.
     * \param number number to be checked
     * \return \c true if the number is probably prime, otherwise \c false
     */
    bool test_fermat(int number);

    /*!
     * \brief Checks whether given number is prime running Fermat's prime test.
     * \param number number to be checked
     * \return \c true if the number is probably prime, otherwise \c false
     */
    bool test_fermat(long number);

    /*!
     * \brief Checks whether given number is prime running Fermat's prime test.
     * \param number number to be checked
     * \return \c true if the number is probably prime, otherwise \c false
     */
    bool test_fermat(long long number);

#pragma endregion
#pragma region test_miller

    /*!
     * \brief Checks whether given number is prime running Miller-Rabin's prime test.
     * \param number number to be checked
     * \return \c true if the number is probably prime, otherwise \c false
     */
    bool test_miller(int number);

    /*!
     * \brief Checks whether given number is prime running Miller-Rabin's prime test.
     * \param number number to be checked
     * \return \c true if the number is probably prime, otherwise \c false
     */
    bool test_miller(long number);

    /*!
     * \brief Checks whether given number is prime running Miller-Rabin's prime test.
     * \param number number to be checked
     * \return \c true if the number is probably prime, otherwise \c false
     */
    bool test_miller(long long number);

#pragma endregion
}

#endif
