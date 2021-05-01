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

#pragma region test_fermat

bool alma::test_fermat(int number)
{
    if(number == 2 || number == 3)
        return true;

    if(number < 2 || number % 2 == 0 || number % 3 == 0)
        return false;

    std::default_random_engine rand_eng;
    std::uniform_int_distribution<int> distribution(2, number - 1);

    for(int i = 0; i < 17; ++i)
    {
        int witness = distribution(rand_eng);

        if(gcd(witness, number) > 1 || power_mod(witness, number - 1, number) != 1)
            return false;
    }

    return true;
}

bool alma::test_fermat(long number)
{
    if(number == 2 || number == 3)
        return true;

    if(number < 2 || number % 2 == 0 || number % 3 == 0)
        return false;

    std::default_random_engine rand_eng;
    std::uniform_int_distribution<long> distribution(2, number - 1);

    for(int i = 0; i < 17; ++i)
    {
        long witness = distribution(rand_eng);

        if(gcd(witness, number) > 1 || power_mod(witness, number - 1, number) != 1)
            return false;
    }

    return true;
}

bool alma::test_fermat(long long number)
{
    if(number == 2 || number == 3)
        return true;

    if(number < 2 || number % 2 == 0 || number % 3 == 0)
        return false;

    std::default_random_engine rand_eng;
    std::uniform_int_distribution<long long> distribution(2, number - 1);

    for(int i = 0; i < 17; ++i)
    {
        long long witness = distribution(rand_eng);

        if(gcd(witness, number) > 1 || power_mod(witness, number - 1, number) != 1)
            return false;
    }

    return true;
}

#pragma endregion
#pragma region test_miller

bool alma::test_miller(int number)
{
    if(number == 2 || number == 3)
        return true;

    if(number < 2 || number % 2 == 0 || number % 3 == 0)
        return false;

    int multiplicand = number - 1;
    std::default_random_engine rand_eng;
    std::uniform_int_distribution<int> distribution(1, number - 1);

    while(multiplicand % 2 == 0)
        multiplicand /= 2;

    for(int i = 0; i < 17; ++i)
    {
        int witness = distribution(rand_eng);

        if(power_mod(witness, multiplicand, number) != 1)
        {
            std::vector<int> exponents;

            for(int d = multiplicand; d <= number / 2; d *= 2)
                exponents.push_back(d);

            if(std::all_of(exponents.begin(), exponents.end(),
                           [&](int d) { return power_mod(witness, d, number) != number - 1; }))
                return false;
        }
    }

    return true;
}

bool alma::test_miller(long number)
{
    if(number == 2 || number == 3)
        return true;

    if(number < 2 || number % 2 == 0 || number % 3 == 0)
        return false;

    long multiplicand = number - 1;
    std::default_random_engine rand_eng;
    std::uniform_int_distribution<long> distribution(1, number - 1);

    while(multiplicand % 2 == 0)
        multiplicand /= 2;

    for(int i = 0; i < 17; ++i)
    {
        long witness = distribution(rand_eng);

        if(power_mod(witness, multiplicand, number) != 1)
        {
            std::vector<long> exponents;

            for(long d = multiplicand; d <= number / 2; d *= 2)
                exponents.push_back(d);

            if(std::all_of(exponents.begin(), exponents.end(),
                           [&](long d) { return power_mod(witness, d, number) != number - 1; }))
                return false;
        }
    }

    return true;
}

bool alma::test_miller(long long number)
{
    if(number == 2 || number == 3)
        return true;

    if(number < 2 || number % 2 == 0 || number % 3 == 0)
        return false;

    long long multiplicand = number - 1;
    std::default_random_engine rand_eng;
    std::uniform_int_distribution<long long> distribution(1, number - 1);

    while(multiplicand % 2 == 0)
        multiplicand /= 2;

    for(int i = 0; i < 17; ++i)
    {
        long long witness = distribution(rand_eng);

        if(power_mod(witness, multiplicand, number) != 1)
        {
            std::vector<long long> exponents;

            for(long long d = multiplicand; d <= number / 2; d *= 2)
                exponents.push_back(d);

            if(std::all_of(exponents.begin(), exponents.end(), [&](long long d) {
                   return power_mod(witness, d, number) != number - 1;
               }))
                return false;
        }
    }

    return true;
}

#pragma endregion
