/**!
 * \file primes.hpp
 * \brief Algorithms for prime numbers
 */
#ifndef PRIMES_HPP_
#define PRIMES_HPP_

#include <cstdlib>
#include <vector>
#include "algolib/maths/maths.hpp"

namespace algolib::maths
{
#pragma region find_primes

    /*!
     * \brief Finds prime numbers inside given range of numbers.
     * \param minimum the minimal number, inclusive
     * \param maximum the maximal number, exclusive
     * \return the prime numbers
     */
    std::vector<size_t> find_primes(size_t minimum, size_t maximum);

    /*!
     * \brief Finds prime numbers less than given number.
     * \param maximum the maximal number, exclusive
     * \return the prime numbers
     */
    inline std::vector<size_t> find_primes(size_t maximum)
    {
        return find_primes(0, maximum);
    }

#pragma endregion
#pragma region test_fermat

    /*!
     * \brief Checks whether given number is prime using Fermat prime test.
     * \param number the number
     * \return \c true if the number is probably prime, otherwise \c false
     */
    bool test_fermat(int number);

    /*!
     * \brief Checks whether given number is prime using Fermat prime test.
     * \param number the number
     * \return \c true if the number is probably prime, otherwise \c false
     */
    bool test_fermat(long number);

    /*!
     * \brief Checks whether given number is prime using Fermat prime test.
     * \param number the number
     * \return \c true if the number is probably prime, otherwise \c false
     */
    bool test_fermat(long long number);

#pragma endregion
#pragma region test_miller

    /*!
     * \brief Checks whether given number is prime using Miller-Rabin prime test.
     * \param number the number
     * \return \c true if the number is probably prime, otherwise \c false
     */
    bool test_miller(int number);

    /*!
     * \brief Checks whether given number is prime using Miller-Rabin prime test.
     * \param number the number
     * \return \c true if the number is probably prime, otherwise \c false
     */
    bool test_miller(long number);

    /*!
     * \brief Checks whether given number is prime using Miller-Rabin prime test.
     * \param number the number
     * \return \c true if the number is probably prime, otherwise \c false
     */
    bool test_miller(long long number);

#pragma endregion
}

#endif
