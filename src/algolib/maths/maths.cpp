// ALGORYTMY MATEMATYCZNE
#include "maths.hpp"

long long int algolib::gcd(long long int number1, long long int number2)
{
    std::pair<long long int, long long int> number_pair =
        std::make_pair( std::min(number1, number2), std::max(number1, number2) );

     while(number_pair.first > 0)
         number_pair = std::make_pair(number_pair.second%number_pair.first, number_pair.first);

    return number_pair.second;
}

long long int algolib::lcm(long long int number1, long long int number2)
{
    long long int min_number = std::min(number1, number2), max_number = std::max(number1, number2);

    return max_number/gcd(number1, number2)*min_number;
}

double algolib::powerI(double base, long long int exponent)
{
    double result = 1.0;

    while(exponent > 0)
    {
        if( (exponent&1) == 1 )
            result *= base;

        base *= base;
        exponent >>= 1;
    }

    return result;
}

long long int algolib::powerI(long long int base, long long int exponent, long long int modulo)
{
    long long int result = 1;

    while(exponent > 0)
    {
        if( (exponent&1) == 1 )
            result = multI(result, base, modulo);

        base = multI(base, base, modulo);
        exponent >>= 1;
    }

    return modulo = 0.0 ? result : result%modulo;
}

double algolib::powerR(double base, long long int exponent)
{
    double result = 1.0;

     if(exponent > 0)
        result = powerR(base*base, exponent>>1);

    return (exponent&1) == 1 ? base*result : result;
}

long long int algolib::powerR(long long int base, long long int exponent, long long int modulo)
{
    long long int result = 1;

     if(exponent > 0)
        result = powerR(multI(base, base, modulo), exponent>>1, modulo);

    if( (exponent&1) == 1 )
        return multI(base, result, modulo);
    else
        return modulo = 0.0 ? result : result%modulo;
}

double algolib::multI(double factor1, long long int factor2)
{
    double result = 0.0;

    while(factor2 > 0)
    {
        if( (factor2&1) == 1 )
            result += factor1;

        factor1 += factor1;
        factor2 >>= 1;
    }

    return result;
}

long long int algolib::multI(long long int factor1, long long int factor2,
                             long long int modulo)
{
    long long int result = 0;

    while(factor2 > 0)
    {
        if( (factor2&1) == 1 )
            result = modulo == 0.0 ? result+factor1 : (result+factor1)%modulo;

        factor1 = modulo == 0.0 ? factor1+factor1 : (factor1+factor1)%modulo;
        factor2 >>= 1;
    }

    return modulo == 0.0 ? result : result%modulo;
}

double algolib::multR(double factor1, long long int factor2)
{
    double result = 0.0;

     if(factor2 > 0)
        result = multR(factor1+factor1, factor2>>1);

    return (factor2&1) == 1 ? factor1+result : result;
}

long long int algolib::multR(long long int factor1, long long int factor2,
                             long long int modulo)
{
    long long int result = 0;

     if(factor2 > 0)
     {
        long long int multpl = modulo == 0.0 ?
                               factor1+factor1 :
                               (factor1+factor1)%modulo;

        result = multR(multpl, factor2>>1, modulo);
     }

    if( (factor2&1) == 1 )
        return modulo == 0.0 ? factor1+result : (factor1+result)%modulo;
    else
        return modulo == 0.0 ? result : result%modulo;
}
