// SITO ERASTOTENESA: WYZNACZANIE LICZB PIERWSZYCH
#include "sieve.hpp"

std::vector<int> algolib::maths::find_primes(int max_number)
{
    std::vector<int> primes;
    std::vector<bool> is_prime;

     for(int i = 0; i <= max_number; ++i)
         is_prime.push_back(i == 2 || (i > 2 && i%2 == 1));

    for(int i = 3; i <= sqrt(is_prime.size()); i += 2)
        if(is_prime[i])
            for(auto it = is_prime.begin()+i*i; it != is_prime.end(); it += i)
                *it = false;

    for(size_t i = 0; i < is_prime.size(); ++i)
        if(is_prime[i])
            primes.push_back(i);

    return primes;
}

std::vector<int> algolib::maths::find_primes(int min_number, int max_number)
{
    std::vector<int> primes;
    std::vector<bool> is_prime, base_primes;
    int diff = max_number-min_number;

    for(int i = 0; i <= sqrt(max_number); ++i)
        base_primes.push_back(i == 2 || (i > 2 && i%2 == 1));

    for(int i = 0; i <= diff; ++i)
        is_prime.push_back((min_number+i)%2 == 0);

    for(size_t i = 3; i < base_primes.size(); i += 2)
        if(base_primes[i])
        {
            int rest = i-min_number%i;

            for(auto it = base_primes.begin()+i*i; it != base_primes.end(); it += i)
                *it = false;

            for(auto it = is_prime.begin()+min_number+rest; it != is_prime.end(); it += i)
                *it = false;
        }

    for(size_t i = 0; i < is_prime.size(); ++i)
        if(is_prime[i])
            primes.push_back(min_number+i);

    return primes;
}
