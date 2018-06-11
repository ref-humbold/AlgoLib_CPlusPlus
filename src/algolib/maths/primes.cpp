// ALGORYTMY DLA LICZB PIERWSZYCH
#include "primes.hpp"

namespace alma = algolib::maths;

std::vector<size_t> alma::find_primes(size_t min_number, size_t max_number)
{
    if(max_number < min_number)
        throw std::invalid_argument(
            "Second argument must be grater or equal to the first argument.");

    std::vector<size_t> primes;
    std::vector<bool> is_prime;
    std::vector<bool> base_primes(static_cast<int>(sqrt(max_number) / 2), true);

    for(size_t i = min_number; i <= max_number; ++i)
        is_prime.push_back(i == 2 || (i > 2 && i % 2 != 0));

    for(size_t i = 0; i < base_primes.size(); ++i)
    {
        size_t p = 2 * i + 3;
        size_t begin = min_number < p * p ? p * p - min_number : (p - min_number % p) % p;

        for(size_t j = (p * p - 3) / 2; j < base_primes.size(); j += p)
            base_primes[j] = false;

        for(size_t j = begin; j < is_prime.size(); j += p)
            is_prime[j] = false;
    }

    for(size_t i = 0; i < is_prime.size(); ++i)
        if(is_prime[i])
            primes.push_back(min_number + i);

    return primes;
}

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

bool alma::test_fermat(long long int number)
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

bool alma::test_miller(long long int number)
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
