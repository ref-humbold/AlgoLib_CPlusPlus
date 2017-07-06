// ALGORYTMY TESTOWANIA PIERWSZOŚCI
#include "prime_checking.hpp"

namespace alma = algolib::maths;

std::pair<long long int, long long int> detail::distribute(long long int number)
{
    long long int power = 2LL, exponent = 1LL;

    while(number % power == 0)
    {
        ++exponent;
        power <<= 1;
    }

    --exponent;

    return std::make_pair(exponent, number / (1 << exponent));
}

bool alma::fermat_prime(long long int number)
{
    if(number == 2 || number == 3)
        return true;

    if(number < 2 || number % 2 == 0 || number % 3 == 0)
        return false;

    for(int i = 0; i < 12; ++i)
    {
        long long int rdv = 1 + rand() % (number - 1);

        if(gcd(rdv, number) > 1 || power_mod(rdv, number - 1, number) != 1)
            return false;
    }

    return true;
}

bool alma::miller_prime(long long int number)
{
    if(number == 2 || number == 3)
        return true;

    if(number < 2 || number % 2 == 0 || number % 3 == 0)
        return false;

    auto distribution = detail::distribute(number - 1);

    for(int i = 0; i < 12; ++i)
    {
        long long int rdv = 1 + rand() % (number - 1);

        if(power_mod(rdv, distribution.second, number) != 1)
        {
            bool is_composite = true;

            for(long long int j = 0LL; j < distribution.first; ++j)
            {
                long long int pwm = power_mod(rdv, (1LL << j) * distribution.second, number);

                is_composite = is_composite && pwm != number - 1;
            }

            if(is_composite)
                return false;
        }
    }

    return true;
}
