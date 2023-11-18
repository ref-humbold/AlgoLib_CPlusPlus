/**!
 * \file primes_testing.hpp
 * \brief Algorithms for testing prime numbers.
 */
#ifndef PRIMES_TESTING_HPP_
#define PRIMES_TESTING_HPP_

#include <cstdlib>
#include <vector>
#include "algolib/maths/maths.hpp"

namespace algolib::maths
{
#pragma region test_prime_fermat

    /*!
     * \brief Checks whether given number is prime using Fermat prime test.
     * \param number the number
     * \return \c true if the number is probably prime, otherwise \c false
     */
    bool test_prime_fermat(int number);

    /*!
     * \brief Checks whether given number is prime using Fermat prime test.
     * \param number the number
     * \return \c true if the number is probably prime, otherwise \c false
     */
    bool test_prime_fermat(long number);

    /*!
     * \brief Checks whether given number is prime using Fermat prime test.
     * \param number the number
     * \return \c true if the number is probably prime, otherwise \c false
     */
    bool test_prime_fermat(long long number);

#pragma endregion
#pragma region test_prime_miller

    /*!
     * \brief Checks whether given number is prime using Miller-Rabin prime test.
     * \param number the number
     * \return \c true if the number is probably prime, otherwise \c false
     */
    bool test_prime_miller(int number);

    /*!
     * \brief Checks whether given number is prime using Miller-Rabin prime test.
     * \param number the number
     * \return \c true if the number is probably prime, otherwise \c false
     */
    bool test_prime_miller(long number);

    /*!
     * \brief Checks whether given number is prime using Miller-Rabin prime test.
     * \param number the number
     * \return \c true if the number is probably prime, otherwise \c false
     */
    bool test_prime_miller(long long number);

#pragma endregion
}

#endif
