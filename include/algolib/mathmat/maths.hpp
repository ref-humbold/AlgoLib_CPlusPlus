/*!
 * \file maths.hpp
 * \brief Algorithms for basic mathematical computations
 */
#ifndef MATHS_HPP_
#define MATHS_HPP_

#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <exception>
#include <stdexcept>

namespace algolib::mathmat
{
    /*!
     * \brief Counts a greatest common divisor of two numbers.
     * \param number1 a first number
     * \param number2 a second number
     * \return greatest common divisor
     */
    long long gcd(long long number1, long long number2);

    /*!
     * \brief Counts a lowest common multiple of two numbers.
     * \param number1 a first number
     * \param number2 a second number
     * \return lowest common multiple
     */
    long long lcm(long long number1, long long number2);

    /*!
     * \brief Performs a fast multiplication of two numbers with modulo taken.
     * \param factor1 a first factor
     * \param factor2 a second factor
     * \param modulo a modulo value
     * \return multiplication result with modulo taken
     */
    long long mult_mod(long long factor1, long long factor2, unsigned long long modulo);

    /*!
     * \brief Performs a fast exponentiation of two numbers with modulo taken.
     * \param base a base value
     * \param exponent an exponent value
     * \param modulo a modulo value
     * \return exponentiation result with modulo taken
     */
    long long power_mod(long long base, long long exponent, unsigned long long modulo);
}

#endif
