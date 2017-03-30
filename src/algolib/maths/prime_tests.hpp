// ALGORYTMY TESTOWANIA PIERWSZOŚCI
#ifndef PRIME_TESTS_HPP
#define PRIME_TESTS_HPP

#include <cstdlib>
#include <ctime>
#include <algorithm>

#include "maths.hpp"

namespace detail
{
    /**
    Rozkładanie liczby do testu Millera-Rabina.
    @param number rozkładana liczba
    @return rozkład liczby
    */
    std::pair<long long int, long long int> distribute(long long int number);
}

namespace algolib
{
    namespace maths
    {
        /**
        Test pierwszości Fermata.
        @param number testowana liczba
        @return czy liczba prawdopodobnie jest pierwsza
        */
        bool fermat_prime(long long int number);

        /**
        Test pierwszości Millera-Rabina.
        @param number testowana liczba
        @return czy liczba prawdopodobnie jest pierwsza
        */
        bool miller_prime(long long int number);
    }
}

#endif
