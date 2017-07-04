// SITO ERASTOTENESA: WYZNACZANIE LICZB PIERWSZYCH
#include "sieve.hpp"
#include <iostream>

namespace alma = algolib::maths;

std::vector<size_t> alma::find_primes(size_t min_number, size_t max_number)
{
    if(max_number < min_number)
        throw std::invalid_argument(
            "Second argument must be grater or equal to the first argument.");

    std::vector<size_t> primes;
    std::vector<bool> is_prime;
    std::vector<bool> base_primes(sqrt(max_number) / 2, true);

    for(size_t i = min_number; i <= max_number; ++i)
        is_prime.push_back(i == 2 || (i > 2 && i % 2 != 0));

    for(size_t i = 0; i < base_primes.size(); ++i)
    {
        size_t p = 2 * i + 3;
        size_t begin = min_number < p * p ? p * p - min_number : (p - min_number % p) % p;

        for(size_t j = p * p; j < base_primes.size(); j += 2 * p)
            base_primes[(j - 3) / 2] = false;

        for(size_t j = begin; j < is_prime.size(); j += p)
            is_prime[j] = false;
    }

    for(size_t i = 0; i < is_prime.size(); ++i)
        if(is_prime[i])
            primes.push_back(min_number + i);

    return primes;
}
