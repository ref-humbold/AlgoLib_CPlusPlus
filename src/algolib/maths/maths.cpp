// ALGORYTMY MATEMATYCZNE
#include "maths.hpp"

long long int algolib::maths::gcd(long long int number1, long long int number2)
{
    std::pair<long long int, long long int> number_pair =
        std::make_pair(std::min(number1, number2), std::max(number1, number2));

     while(number_pair.first > 0)
         number_pair = std::make_pair(number_pair.second%number_pair.first, number_pair.first);

    return number_pair.second;
}

long long int algolib::maths::lcm(long long int number1, long long int number2)
{
    long long int min_number = std::min(number1, number2), max_number = std::max(number1, number2);

    return max_number/gcd(number1, number2)*min_number;
}

long long int algolib::maths::power(long long int base, long long int exponent,
                                    long long int modulo)
{
    long long int result = 1;

    while(exponent > 0)
    {
        if((exponent&1) == 1)
            result = mult(result, base, modulo);

        base = mult(base, base, modulo);
        exponent >>= 1;
    }

    return result;
}

long long int algolib::maths::mult(long long int factor1, long long int factor2,
                                   long long int modulo)
{
    long long int result = 0;

    while(factor2 > 0)
    {
        if((factor2&1) == 1)
            result = modulo == 0.0 ? result+factor1 : (result+factor1)%modulo;

        factor1 = modulo == 0.0 ? factor1+factor1 : (factor1+factor1)%modulo;
        factor2 >>= 1;
    }

    return result;
}
