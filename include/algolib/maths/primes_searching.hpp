/**!
 * \file primes_searching.hpp
 * \brief Algorithms for searching for prime numbers.
 */
#ifndef PRIMES_SEARCHING_HPP_
#define PRIMES_SEARCHING_HPP_

#include <cstdlib>
#include <vector>

namespace algolib::maths
{
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
}

#endif
