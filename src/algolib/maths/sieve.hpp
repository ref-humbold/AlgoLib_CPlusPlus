// SITO ERASTOTENESA: WYZNACZANIE LICZB PIERWSZYCH
#ifndef SIEVE_HPP
#define SIEVE_HPP

#include <cstdlib>
#include <cmath>
#include <vector>

namespace algolib
{
    /**
    WYZNACZANIE LICZB PIERWSZYCH OD 0
    @param max_number górna granica od zera
    @return lista liczb pierwszych
    */
    std::vector<int> find_primes(int max_number);

    /**
    WYZNACZANIE LICZB PIERWSZYCH NA PRZEDZIALE DOMKNIĘTYM
    @param min_number dolna granica przedziału
    @param max_number górna granica przedziału
    @return lista liczb pierwszych
    */
    std::vector<int> find_primes(int min_number, int max_number);
}

#endif
