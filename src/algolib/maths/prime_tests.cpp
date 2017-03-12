// ALGORYTMY TESTOWANIA PIERWSZOŚCI
#include "prime_tests.hpp"

namespace details = algolib::detail;

std::pair<long long int, long long int> details::distribute(long long int number)
{
    long long int power = 2LL, exponent = 1LL;

    while(number%power == 0)
    {
        ++exponent;
        power <<= 1;
    }

    --exponent;

    return std::make_pair( exponent, number/(1<<exponent) );
}

bool algolib::fermat_prime(long long int number)
{
    for(int i = 0; i < 10; ++i)
    {
        long long int random_value = rand()%(number-3)+2;

        if(gcd(random_value, number) > 1)
            return false;

        if(powerI(random_value, number-1, number) != 1)
            return false;
    }

    return true;
}

bool algolib::miller_prime(long long int number)
{
    std::pair<long long int, long long int> distribution = details::distribute(number-1);

    for(int i = 0; i < 10; ++i)
    {
        long long int random_value = rand()%(number-3)+2;
        bool composity = true;

        if(powerI(random_value, distribution.second, number) != 1)
            for(int j = 0; j < distribution.first; ++j)
            {
                long long int pwm = powerI(random_value, (1<<j)*distribution.second, number);

                composity = composity && pwm != number-1;
            }

        if(composity)
            return false;
    }

    return true;
}
