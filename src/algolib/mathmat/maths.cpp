/**!
 * \file maths.cpp
 * \brief Algorithms for basic mathematical computations
 */
#include "algolib/mathmat/maths.hpp"

namespace alma = algolib::mathmat;

#pragma region gcd

int alma::gcd(int number1, int number2)
{
    std::pair<int, int> number_pair =
            std::make_pair(std::min(std::abs(number1), std::abs(number2)),
                           std::max(std::abs(number1), std::abs(number2)));

    while(number_pair.first > 0)
        number_pair = std::make_pair(number_pair.second % number_pair.first, number_pair.first);

    return number_pair.second;
}

long alma::gcd(long number1, long number2)
{
    std::pair<long, long> number_pair =
            std::make_pair(std::min(std::abs(number1), std::abs(number2)),
                           std::max(std::abs(number1), std::abs(number2)));

    while(number_pair.first > 0)
        number_pair = std::make_pair(number_pair.second % number_pair.first, number_pair.first);

    return number_pair.second;
}

long long alma::gcd(long long number1, long long number2)
{
    std::pair<long long, long long> number_pair =
            std::make_pair(std::min(std::abs(number1), std::abs(number2)),
                           std::max(std::abs(number1), std::abs(number2)));

    while(number_pair.first > 0)
        number_pair = std::make_pair(number_pair.second % number_pair.first, number_pair.first);

    return number_pair.second;
}

#pragma endregion
#pragma region lcm

int alma::lcm(int number1, int number2)
{
    int min_number = std::min(std::abs(number1), std::abs(number2)),
        max_number = std::max(std::abs(number1), std::abs(number2));

    return max_number / gcd(number1, number2) * min_number;
}

long alma::lcm(long number1, long number2)
{
    long min_number = std::min(std::abs(number1), std::abs(number2)),
         max_number = std::max(std::abs(number1), std::abs(number2));

    return max_number / gcd(number1, number2) * min_number;
}

long long alma::lcm(long long number1, long long number2)
{
    long long min_number = std::min(std::abs(number1), std::abs(number2)),
              max_number = std::max(std::abs(number1), std::abs(number2));

    return max_number / gcd(number1, number2) * min_number;
}

#pragma endregion
#pragma region mult_mod

int alma::mult_mod(int factor1, int factor2, int modulo)
{
    int result = 0;

    if(modulo < 0)
        throw std::domain_error("Negative modulo");

    if(factor1 < 0 && factor2 < 0)
        return mult_mod(-factor1, -factor2, modulo);

    if(factor1 < 0)
        return modulo - mult_mod(-factor1, factor2, modulo);

    if(factor2 < 0)
        return modulo - mult_mod(factor1, -factor2, modulo);

    while(factor2 > 0)
    {
        if(factor2 % 2 == 1)
            result = modulo == 0 ? result + factor1 : (result + factor1) % modulo;

        factor1 = modulo == 0 ? factor1 + factor1 : (factor1 + factor1) % modulo;
        factor2 /= 2;
    }

    return result;
}

long alma::mult_mod(long factor1, long factor2, long modulo)
{
    long result = 0;

    if(modulo < 0)
        throw std::domain_error("Negative modulo");

    if(factor1 < 0 && factor2 < 0)
        return mult_mod(-factor1, -factor2, modulo);

    if(factor1 < 0)
        return modulo - mult_mod(-factor1, factor2, modulo);

    if(factor2 < 0)
        return modulo - mult_mod(factor1, -factor2, modulo);

    while(factor2 > 0)
    {
        if(factor2 % 2 == 1)
            result = modulo == 0 ? result + factor1 : (result + factor1) % modulo;

        factor1 = modulo == 0 ? factor1 + factor1 : (factor1 + factor1) % modulo;
        factor2 /= 2;
    }

    return result;
}

long long alma::mult_mod(long long factor1, long long factor2, long long modulo)
{
    long long result = 0;

    if(modulo < 0)
        throw std::domain_error("Negative modulo");

    if(factor1 < 0 && factor2 < 0)
        return mult_mod(-factor1, -factor2, modulo);

    if(factor1 < 0)
        return modulo - mult_mod(-factor1, factor2, modulo);

    if(factor2 < 0)
        return modulo - mult_mod(factor1, -factor2, modulo);

    while(factor2 > 0)
    {
        if(factor2 % 2 == 1)
            result = modulo == 0 ? result + factor1 : (result + factor1) % modulo;

        factor1 = modulo == 0 ? factor1 + factor1 : (factor1 + factor1) % modulo;
        factor2 /= 2;
    }

    return result;
}

#pragma endregion
#pragma region power_mod

int alma::power_mod(int base, int exponent, int modulo)
{
    int result = 1;

    if(modulo < 0)
        throw std::domain_error("Negative modulo");

    if(exponent < 0)
        throw std::domain_error("Negative exponent");

    if(base == 0 && exponent == 0)
        throw std::domain_error("Not a number");

    while(exponent > 0)
    {
        if(exponent % 2 == 1)
            result = mult_mod(result, base, modulo);

        base = mult_mod(base, base, modulo);
        exponent /= 2;
    }

    return result;
}

long alma::power_mod(long base, long exponent, long modulo)
{
    long result = 1;

    if(modulo < 0)
        throw std::domain_error("Negative modulo");

    if(exponent < 0)
        throw std::domain_error("Negative exponent");

    if(base == 0 && exponent == 0)
        throw std::domain_error("Not a number");

    while(exponent > 0)
    {
        if(exponent % 2 == 1)
            result = mult_mod(result, base, modulo);

        base = mult_mod(base, base, modulo);
        exponent /= 2;
    }

    return result;
}

long long alma::power_mod(long long base, long long exponent, long long modulo)
{
    long long result = 1;

    if(modulo < 0)
        throw std::domain_error("Negative modulo");

    if(exponent < 0)
        throw std::domain_error("Negative exponent");

    if(base == 0 && exponent == 0)
        throw std::domain_error("Not a number");

    while(exponent > 0)
    {
        if(exponent % 2 == 1)
            result = mult_mod(result, base, modulo);

        base = mult_mod(base, base, modulo);
        exponent /= 2;
    }

    return result;
}

#pragma endregion
