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
#pragma region gcd

    /*!
     * \brief Counts a greatest common divisor of two numbers.
     * \param number1 a first number
     * \param number2 a second number
     * \return greatest common divisor
     */
    int gcd(int number1, int number2);

    /*!
     * \brief Counts a greatest common divisor of two numbers.
     * \param number1 a first number
     * \param number2 a second number
     * \return greatest common divisor
     */
    long gcd(long number1, long number2);

    /*!
     * \brief Counts a greatest common divisor of two numbers.
     * \param number1 a first number
     * \param number2 a second number
     * \return greatest common divisor
     */
    long long gcd(long long number1, long long number2);

#pragma endregion
#pragma region lcm

    /*!
     * \brief Counts a lowest common multiple of two numbers.
     * \param number1 a first number
     * \param number2 a second number
     * \return lowest common multiple
     */
    int lcm(int number1, int number2);

    /*!
     * \brief Counts a lowest common multiple of two numbers.
     * \param number1 a first number
     * \param number2 a second number
     * \return lowest common multiple
     */
    long lcm(long number1, long number2);

    /*!
     * \brief Counts a lowest common multiple of two numbers.
     * \param number1 a first number
     * \param number2 a second number
     * \return lowest common multiple
     */
    long long lcm(long long number1, long long number2);

#pragma endregion
#pragma region mult_mod

    /*!
     * \brief Performs a fast multiplication of two numbers with modulo taken.
     * \param factor1 a first factor
     * \param factor2 a second factor
     * \param modulo a modulo value
     * \return multiplication result with modulo taken
     */
    int mult_mod(int factor1, int factor2, unsigned int modulo);

    /*!
     * \brief Performs a fast multiplication of two numbers with modulo taken.
     * \param factor1 a first factor
     * \param factor2 a second factor
     * \param modulo a modulo value
     * \return multiplication result with modulo taken
     */
    long mult_mod(long factor1, long factor2, unsigned long modulo);

    /*!
     * \brief Performs a fast multiplication of two numbers with modulo taken.
     * \param factor1 a first factor
     * \param factor2 a second factor
     * \param modulo a modulo value
     * \return multiplication result with modulo taken
     */
    long long mult_mod(long long factor1, long long factor2, unsigned long long modulo);

#pragma endregion
#pragma region power_mod

    /*!
     * \brief Performs a fast exponentiation of two numbers with modulo taken.
     * \param base a base value
     * \param exponent an exponent value
     * \param modulo a modulo value
     * \return exponentiation result with modulo taken
     */
    int power_mod(int base, int exponent, unsigned int modulo);

    /*!
     * \brief Performs a fast exponentiation of two numbers with modulo taken.
     * \param base a base value
     * \param exponent an exponent value
     * \param modulo a modulo value
     * \return exponentiation result with modulo taken
     */
    long power_mod(long base, long exponent, unsigned long modulo);

    /*!
     * \brief Performs a fast exponentiation of two numbers with modulo taken.
     * \param base a base value
     * \param exponent an exponent value
     * \param modulo a modulo value
     * \return exponentiation result with modulo taken
     */
    long long power_mod(long long base, long long exponent, unsigned long long modulo);

#pragma endregion
}

#endif
