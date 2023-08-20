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

namespace algolib::maths
{
#pragma region gcd

    /*!
     * \brief Counts greatest common divisor of two numbers.
     * \param number1 first number
     * \param number2 second number
     * \return greatest common divisor
     */
    int gcd(int number1, int number2);

    /*!
     * \brief Counts greatest common divisor of two numbers.
     * \param number1 first number
     * \param number2 second number
     * \return greatest common divisor
     */
    long gcd(long number1, long number2);

    /*!
     * \brief Counts greatest common divisor of two numbers.
     * \param number1 first number
     * \param number2 second number
     * \return greatest common divisor
     */
    long long gcd(long long number1, long long number2);

#pragma endregion
#pragma region lcm

    /*!
     * \brief Counts lowest common multiple of two numbers.
     * \param number1 first number
     * \param number2 second number
     * \return lowest common multiple
     */
    int lcm(int number1, int number2);

    /*!
     * \brief Counts lowest common multiple of two numbers.
     * \param number1 first number
     * \param number2 second number
     * \return lowest common multiple
     */
    long lcm(long number1, long number2);

    /*!
     * \brief Counts lowest common multiple of two numbers.
     * \param number1 first number
     * \param number2 second number
     * \return lowest common multiple
     */
    long long lcm(long long number1, long long number2);

#pragma endregion
#pragma region multiply

    /*!
     * \brief Performs fast multiplication of two numbers.
     * \param factor1 first factor
     * \param factor2 second factor
     * \return multiplication result
     */
    int multiply(int factor1, int factor2);

    /*!
     * \brief Performs fast multiplication of two numbers.
     * \param factor1 first factor
     * \param factor2 second factor
     * \return multiplication result
     */
    long multiply(long factor1, long factor2);

    /*!
     * \brief Performs fast multiplication of two numbers.
     * \param factor1 first factor
     * \param factor2 second factor
     * \return multiplication result
     */
    long long multiply(long long factor1, long long factor2);

    /*!
     * \brief Performs fast multiplication of two numbers with modulo taken.
     * \param factor1 first factor
     * \param factor2 second factor
     * \param modulo modulo value
     * \return multiplication result with modulo taken
     */
    int multiply(int factor1, int factor2, int modulo);

    /*!
     * \brief Performs fast multiplication of two numbers with modulo taken.
     * \param factor1 first factor
     * \param factor2 second factor
     * \param modulo modulo value
     * \return multiplication result with modulo taken
     */
    long multiply(long factor1, long factor2, long modulo);

    /*!
     * \brief Performs fast multiplication of two numbers with modulo taken.
     * \param factor1 first factor
     * \param factor2 second factor
     * \param modulo modulo value
     * \return multiplication result with modulo taken
     */
    long long multiply(long long factor1, long long factor2, long long modulo);

#pragma endregion
#pragma region power

    /*!
     * \brief Performs fast exponentiation of two numbers.
     * \param base base value
     * \param exponent exponent value
     * \return exponentiation result
     */
    int power(int base, int exponent);

    /*!
     * \brief Performs fast exponentiation of two numbers.
     * \param base base value
     * \param exponent exponent value
     * \return exponentiation result
     */
    long power(long base, long exponent);

    /*!
     * \brief Performs fast exponentiation of two numbers.
     * \param base base value
     * \param exponent exponent value
     * \return exponentiation result with modulo taken
     */
    long long power(long long base, long long exponent);

    /*!
     * \brief Performs fast exponentiation of two numbers with modulo taken.
     * \param base base value
     * \param exponent exponent value
     * \param modulo modulo value
     * \return exponentiation result with modulo taken
     */
    int power(int base, int exponent, int modulo);

    /*!
     * \brief Performs fast exponentiation of two numbers with modulo taken.
     * \param base base value
     * \param exponent exponent value
     * \param modulo modulo value
     * \return exponentiation result with modulo taken
     */
    long power(long base, long exponent, long modulo);

    /*!
     * \brief Performs fast exponentiation of two numbers with modulo taken.
     * \param base base value
     * \param exponent exponent value
     * \param modulo modulo value
     * \return exponentiation result with modulo taken
     */
    long long power(long long base, long long exponent, long long modulo);

#pragma endregion
}

#endif
