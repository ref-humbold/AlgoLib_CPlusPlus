/**
 * @file maths.hpp
 * MATHS ALGORITHMS
 */
#ifndef _MATHS_HPP_
#define _MATHS_HPP_

#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <exception>
#include <stdexcept>

namespace algolib
{
    namespace mathmat
    {
        /**
         * Największy wspólny dzielnik dwóch liczb.
         * @param number1 pierwsza liczba
         * @param number2 druga liczba
         * @return największy wspólny dzielnik
         */
        long long int gcd(long long int number1, long long int number2);

        /**
         * Najmniejsza wspólna wielokrotność dwóch liczb.
         * @param number1 pierwsza liczba
         * @param number2 druga liczba
         * @return najmniejsza wspólna wielokrotność
         */
        long long int lcm(long long int number1, long long int number2);

        /**
         * Szybkie mnożenie binarne modulowane.
         * @param factor1 mnnożna
         * @param factor2 mnożnik
         * @param modulo modulo
         * @return wynik mnożenia wzięty modulo
         */
        long long int mult_mod(long long int factor1, long long int factor2,
                               unsigned long long int modulo);

        /**
         * Szybkie potęgowanie binarne modulowane.
         * @param base podstawa
         * @param exponent wykładnik
         * @param modulo modulo
         * @return wynik potęgowania wzięty modulo
         */
        long long int power_mod(long long int base, long long int exponent,
                                unsigned long long int modulo);
    }
}

#endif
