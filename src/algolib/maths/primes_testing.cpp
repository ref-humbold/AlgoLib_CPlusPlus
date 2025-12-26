/*!
 * \file primes_testing.cpp
 * \brief Algorithms for testing prime numbers.
 */
#include "algolib/maths/primes_testing.hpp"
#include <cmath>
#include <ctime>
#include <algorithm>
#include <random>

namespace alma = algolib::maths;

#pragma region test_prime_fermat

bool alma::test_prime_fermat(int number)
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

        if(gcd(witness, number) > 1 || power(witness, number - 1, number) != 1)
            return false;
    }

    return true;
}

bool alma::test_prime_fermat(long number)
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

        if(gcd(witness, number) > 1 || power(witness, number - 1, number) != 1)
            return false;
    }

    return true;
}

bool alma::test_prime_fermat(long long number)
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

        if(gcd(witness, number) > 1 || power(witness, number - 1, number) != 1)
            return false;
    }

    return true;
}

#pragma endregion
#pragma region test_prime_miller

bool alma::test_prime_miller(int number)
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

        if(power(witness, multiplicand, number) != 1)
        {
            std::vector<int> exponents;

            for(int d = multiplicand; d <= number / 2; d *= 2)
                exponents.push_back(d);

            if(std::all_of(exponents.begin(), exponents.end(),
                       [&](int d) { return power(witness, d, number) != number - 1; }))
                return false;
        }
    }

    return true;
}

bool alma::test_prime_miller(long number)
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

        if(power(witness, multiplicand, number) != 1)
        {
            std::vector<long> exponents;

            for(long d = multiplicand; d <= number / 2; d *= 2)
                exponents.push_back(d);

            if(std::all_of(exponents.begin(), exponents.end(),
                       [&](long d) { return power(witness, d, number) != number - 1; }))
                return false;
        }
    }

    return true;
}

bool alma::test_prime_miller(long long number)
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

        if(power(witness, multiplicand, number) != 1)
        {
            std::vector<long long> exponents;

            for(long long d = multiplicand; d <= number / 2; d *= 2)
                exponents.push_back(d);

            if(std::all_of(exponents.begin(), exponents.end(),
                       [&](long long d) { return power(witness, d, number) != number - 1; }))
                return false;
        }
    }

    return true;
}

#pragma endregion
