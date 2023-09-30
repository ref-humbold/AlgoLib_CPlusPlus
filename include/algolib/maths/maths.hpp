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
#pragma region greatest common divisor

    /*!
     * \brief Calculates greatest common divisor of given numbers.
     * \param number1 the first number
     * \param number2 the second number
     * \return the greatest common divisor
     */
    int gcd(int number1, int number2);

    /*!
     * \brief Calculates greatest common divisor of given numbers.
     * \param number1 the first number
     * \param number2 the second number
     * \return the greatest common divisor
     */
    long gcd(long number1, long number2);

    /*!
     * \brief Calculates greatest common divisor of given numbers.
     * \param number1 the first number
     * \param number2 the second number
     * \return the greatest common divisor
     */
    long long gcd(long long number1, long long number2);

#pragma endregion
#pragma region lowest common multiple

    /*!
     * \brief Calculates lowest common multiple of given numbers.
     * \param number1 the first number
     * \param number2 the second number
     * \return the lowest common multiple
     */
    int lcm(int number1, int number2);

    /*!
     * \brief Calculates lowest common multiple of given numbers.
     * \param number1 the first number
     * \param number2 the second number
     * \return the lowest common multiple
     */
    long lcm(long number1, long number2);

    /*!
     * \brief Calculates lowest common multiple of given numbers.
     * \param number1 the first number
     * \param number2 the second number
     * \return the lowest common multiple
     */
    long long lcm(long long number1, long long number2);

#pragma endregion
#pragma region multiply

    /*!
     * \brief Performs fast multiplication of given numbers.
     * \param factor1 the first factor
     * \param factor2 the second factor
     * \return the multiplication result
     */
    int multiply(int factor1, int factor2);

    /*!
     * \brief Performs fast multiplication of given numbers.
     * \param factor1 the first factor
     * \param factor2 the second factor
     * \return the multiplication result
     */
    long multiply(long factor1, long factor2);

    /*!
     * \brief Performs fast multiplication of given numbers.
     * \param factor1 the first factor
     * \param factor2 the second factor
     * \return the multiplication result
     */
    long long multiply(long long factor1, long long factor2);

    /*!
     * \brief Performs fast multiplication of given numbers with modulo taken.
     * \param factor1 the first factor
     * \param factor2 the second factor
     * \param modulo the modulo
     * \return the multiplication result with modulo taken
     */
    int multiply(int factor1, int factor2, int modulo);

    /*!
     * \brief Performs fast multiplication of given numbers with modulo taken.
     * \param factor1 the first factor
     * \param factor2 the second factor
     * \param modulo the modulo
     * \return the multiplication result with modulo taken
     */
    long multiply(long factor1, long factor2, long modulo);

    /*!
     * \brief Performs fast multiplication of given numbers with modulo taken.
     * \param factor1 the first factor
     * \param factor2 the second factor
     * \param modulo the modulo
     * \return the multiplication result with modulo taken
     */
    long long multiply(long long factor1, long long factor2, long long modulo);

#pragma endregion
#pragma region power

    /*!
     * \brief Performs fast exponentiation of given numbers.
     * \param base the base
     * \param exponent the exponent
     * \return the exponentiation result
     */
    int power(int base, int exponent);

    /*!
     * \brief Performs fast exponentiation of given numbers.
     * \param base the base
     * \param exponent the exponent
     * \return the exponentiation result
     */
    long power(long base, long exponent);

    /*!
     * \brief Performs fast exponentiation of given numbers.
     * \param base the base
     * \param exponent the exponent
     * \return the exponentiation result with modulo taken
     */
    long long power(long long base, long long exponent);

    /*!
     * \brief Performs fast exponentiation of given numbers with modulo taken.
     * \param base the base
     * \param exponent the exponent
     * \param modulo the modulo
     * \return the exponentiation result with modulo taken
     */
    int power(int base, int exponent, int modulo);

    /*!
     * \brief Performs fast exponentiation of given numbers with modulo taken.
     * \param base the base
     * \param exponent the exponent
     * \param modulo the modulo
     * \return the exponentiation result with modulo taken
     */
    long power(long base, long exponent, long modulo);

    /*!
     * \brief Performs fast exponentiation of given numbers with modulo taken.
     * \param base the base
     * \param exponent the exponent
     * \param modulo the modulo
     * \return the exponentiation result with modulo taken
     */
    long long power(long long base, long long exponent, long long modulo);

#pragma endregion
}

#endif
