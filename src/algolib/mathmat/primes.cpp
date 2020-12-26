/*!
 * \file primes.cpp
 * \brief Algorithms for prime numbers
 */
#include "algolib/mathmat/primes.hpp"
#include <random>

namespace alma = algolib::mathmat;

std::vector<size_t> alma::find_primes(size_t min_number, size_t max_number)
{
    if(max_number <= min_number)
        return std::vector<size_t>();

    std::vector<size_t> primes;
    std::vector<bool> is_prime;
    std::vector<bool> base_primes(static_cast<int>(sqrt(max_number) / 2), true);

    for(size_t i = min_number; i < max_number; ++i)
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

bool alma::test_fermat(long long int number)
{
    if(number == 2 || number == 3)
        return true;

    if(number < 2 || number % 2 == 0 || number % 3 == 0)
        return false;

    std::default_random_engine rand_eng;
    std::uniform_int_distribution<long long int> distribution(2, number - 1);

    for(int i = 0; i < 17; ++i)
    {
        long long int witness = distribution(rand_eng);

        if(gcd(witness, number) > 1 || power_mod(witness, number - 1, number) != 1)
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

    long long int multiplier = number - 1;
    std::default_random_engine rand_eng;
    std::uniform_int_distribution<long long int> distribution(1, number - 1);

    while(multiplier % 2 == 0)
        multiplier /= 2;

    for(int i = 0; i < 17; ++i)
    {
        long long int witness = distribution(rand_eng);

        if(power_mod(witness, multiplier, number) != 1)
        {
            std::vector<long long int> exponents;

            for(long long int d = multiplier; d <= number / 2; d *= 2)
                exponents.push_back(d);

            if(std::all_of(exponents.begin(), exponents.end(), [&](long long int d) {
                   return power_mod(witness, d, number) != number - 1;
               }))
                return false;
        }
    }

    return true;
}
