/*!
 * \file primes_searching.cpp
 * \brief Algorithms for searching for prime numbers.
 */
#include "algolib/maths/primes_searching.hpp"
#include <cmath>
#include <ctime>
#include <algorithm>
#include <random>

namespace alma = algolib::maths;

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
