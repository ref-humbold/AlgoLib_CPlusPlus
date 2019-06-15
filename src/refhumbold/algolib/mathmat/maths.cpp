//! Basic mathematics algorithms.
#include "refhumbold/algolib/mathmat/maths.hpp"

namespace alma = algolib::mathmat;

long long int alma::gcd(long long int number1, long long int number2)
{
    std::pair<long long int, long long int> number_pair =
        std::make_pair(std::min(number1, number2), std::max(number1, number2));

    while(number_pair.first > 0)
        number_pair = std::make_pair(number_pair.second % number_pair.first, number_pair.first);

    return number_pair.second;
}

long long int alma::lcm(long long int number1, long long int number2)
{
    long long int min_number = std::min(number1, number2), max_number = std::max(number1, number2);

    return max_number / gcd(number1, number2) * min_number;
}

long long int alma::mult_mod(long long int factor1, long long int factor2,
                             unsigned long long int modulo)
{
    long long int result = 0;

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
        factor2 >>= 1;
    }

    return result;
}

long long int alma::power_mod(long long int base, long long int exponent,
                              unsigned long long int modulo)
{
    long long int result = 1;

    if(exponent < 0)
        throw std::domain_error("Negative exponent.");

    if(base == 0 && exponent == 0)
        throw std::domain_error("Not a number.");

    while(exponent > 0)
    {
        if(exponent % 2 == 1)
            result = mult_mod(result, base, modulo);

        base = mult_mod(base, base, modulo);
        exponent >>= 1;
    }

    return result;
}
