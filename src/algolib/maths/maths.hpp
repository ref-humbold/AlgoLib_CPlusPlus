// ALGORYTMY MATEMATYCZNE
#ifndef MATHS_HPP
#define MATHS_HPP

#include <cstdlib>
#include <cmath>
#include <algorithm>

namespace algolib
{
    /**
    Największy wspólny dzielnik dwóch liczb.
    @param number1 pierwsza liczba
    @param number2 druga liczba
    @return największy wspólny dzielnik
    */
    long long int gcd(long long int number1, long long int number2);

    /**
    Najmniejsza wspólna wielokrotność dwóch liczb.
    @param number1 pierwsza liczba
    @param number2 druga liczba
    @return najmniejsza wspólna wielokrotność
    */
    long long int lcm(long long int number1, long long int number2);

    /**
    Iteracyjne szybkie potęgowanie binarne modulowane.
    @param base podstawa
    @param exponent wykładnik
    @param modulo modulo
    @return wynik potęgowania wzięty modulo
    */
    double powerI(double base, long long int exponent, double modulo=0.0);

    /**
    Iteracyjne szybkie potęgowanie binarne modulowane.
    @param base podstawa
    @param exponent wykładnik
    @param modulo modulo
    @return wynik potęgowania wzięty modulo
    */
    long long int powerI(long long int base, long long int exponent, long long int modulo=0LL);

    /**
    Rekurencyjne szybkie potęgowanie binarne modulowane.
    @param base podstawa
    @param exponent wykładnik
    @param modulo modulo
    @return wynik potęgowania wzięty modulo
    */
    double powerR(double base, long long int exponent, double modulo=0.0);

    /**
    Rekurencyjne szybkie potęgowanie binarne modulowane.
    @param base podstawa
    @param exponent wykładnik
    @param modulo modulo
    @return wynik potęgowania wzięty modulo
    */
    long long int powerR(long long int base, long long int exponent, long long int modulo=0LL);

    /**
    Iteracyjne mnożenie binarne modulowane.
    @param factor1 mnnożna
    @param factor2 mnożnik
    @param modulo modulo
    @return wynik mnożenia wzięty modulo
    */
    double multI(double factor1, long long int factor2, double modulo=0.0);

    /**
    Iteracyjne mnożenie binarne modulowane.
    @param factor1 mnnożna
    @param factor2 mnożnik
    @param modulo modulo
    @return wynik mnożenia wzięty modulo
    */
    long long int multI(long long int factor1, long long int factor2,
                        long long int modulo=0LL);

    /**
    Rekurencyjne mnożenie binarne modulowane.
    @param factor1 mnnożna
    @param factor2 mnożnik
    @param modulo modulo
    @return wynik mnożenia wzięty modulo
    */
    double multR(double factor1, long long int factor2, double modulo=0.0);

    /**
    Rekurencyjne mnożenie binarne modulowane.
    @param factor1 mnnożna
    @param factor2 mnożnik
    @param modulo modulo
    @return wynik mnożenia wzięty modulo
    */
    long long int multR(long long int factor1, long long int factor2,
                        long long int modulo=0LL);
}

#endif
