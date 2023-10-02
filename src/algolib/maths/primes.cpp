/*!
 * \file primes.cpp
 * \brief Algorithms for prime numbers.
 */
#include "algolib/maths/primes.hpp"
#include <cmath>
#include <ctime>
#include <algorithm>
#include <random>

namespace alma = algolib::maths;

#pragma region find_primes

// Extracts prime numbers between 0 and given maximum value
std::vector<size_t> get_base_primes(size_t base_maximum)
{
    std::vector<size_t> primes;
    std::vector<bool> is_prime((base_maximum - 1) / 2, true);

    for(size_t i = 0; i < static_cast<size_t>(sqrt(base_maximum) / 2); ++i)
        if(is_prime[i])
        {
            size_t prime_value = 2 * i + 3;

            for(size_t j = prime_value * prime_value; j < base_maximum; j += 2 * prime_value)
                is_prime[(j - 3) / 2] = false;
        }

    for(size_t i = 0; i < is_prime.size(); ++i)
        if(is_prime[i])
            primes.push_back(2 * i + 3);

    return primes;
}

// Extracts prime numbers from given range using given basic prime numbers
std::vector<size_t> get_segment_primes(
        size_t segment_start, size_t segment_end, const std::vector<size_t> & base_primes)
{
    std::vector<size_t> primes;
    std::vector<bool> is_prime;
    size_t segment_begin = segment_start + 1 - segment_start % 2;

    for(size_t i = segment_begin; i < segment_end; i += 2)
        is_prime.push_back(i > 2);

    for(auto && p : base_primes)
    {
        size_t prime_multiple = (segment_begin + p - 1) / p * p;
        size_t multiple_start = prime_multiple % 2 == 0 ? prime_multiple + p : prime_multiple;

        for(size_t i = multiple_start; i < segment_end; i += 2 * p)
            is_prime[(i - segment_begin) / 2] = false;
    }

    for(size_t i = 0; i < is_prime.size(); ++i)
        if(is_prime[i])
            primes.push_back(segment_begin + 2 * i);

    return primes;
}

std::vector<size_t> alma::find_primes(size_t minimum, size_t maximum)
{
    if(maximum <= minimum || maximum <= 2)
        return std::vector<size_t>();

    std::vector<size_t> primes;
    size_t segment_size = static_cast<size_t>(sqrt(maximum));
    std::vector<size_t> base_primes = get_base_primes(segment_size);

    if(minimum < segment_size)
    {
        if(2 >= minimum)
            primes.push_back(2);

        for(auto && p : base_primes)
            if(p >= minimum)
                primes.push_back(p);
    }

    for(size_t i = std::max(minimum, segment_size); i < maximum; i += segment_size)
    {
        std::vector<size_t> segment_primes =
                get_segment_primes(i, std::min(i + segment_size, maximum), base_primes);

        primes.insert(primes.end(), segment_primes.begin(), segment_primes.end());
    }

    return primes;
}

#pragma endregion
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

        if(gcd(witness, number) > 1 || power(witness, number - 1, number) != 1)
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

        if(gcd(witness, number) > 1 || power(witness, number - 1, number) != 1)
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

        if(gcd(witness, number) > 1 || power(witness, number - 1, number) != 1)
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

        if(power(witness, multiplicand, number) != 1)
        {
            std::vector<int> exponents;

            for(int d = multiplicand; d <= number / 2; d *= 2)
                exponents.push_back(d);

            if(std::all_of(
                       exponents.begin(), exponents.end(),
                       [&](int d) { return power(witness, d, number) != number - 1; }))
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

        if(power(witness, multiplicand, number) != 1)
        {
            std::vector<long> exponents;

            for(long d = multiplicand; d <= number / 2; d *= 2)
                exponents.push_back(d);

            if(std::all_of(
                       exponents.begin(), exponents.end(),
                       [&](long d) { return power(witness, d, number) != number - 1; }))
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

        if(power(witness, multiplicand, number) != 1)
        {
            std::vector<long long> exponents;

            for(long long d = multiplicand; d <= number / 2; d *= 2)
                exponents.push_back(d);

            if(std::all_of(
                       exponents.begin(), exponents.end(),
                       [&](long long d) { return power(witness, d, number) != number - 1; }))
                return false;
        }
    }

    return true;
}

#pragma endregion
