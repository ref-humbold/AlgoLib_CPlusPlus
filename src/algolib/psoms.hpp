// ALGORYTMY WYZNACZANIA PODCIĄGU SPÓJNEGO O MAKSYMALNEJ SUMIE
#ifndef PSOMS_HPP
#define PSOMS_HPP

#include <cstdlib>
#include <vector>
#include <algorithm>

namespace algolib
{
    /**
    Wyznaczanie spójnego podciągu o maksymalnej sumie w sposób dynamiczny.
    @param sequence ciąg
    @return elementy spójnego podciągu o maksymalnej sumie
    */
    std::vector<double> find_maxsum_subseq1(const std::vector<double> & sequence);

    /**
    Wyznaczanie spójnego podciągu o maksymalnej sumie za pomocą drzewa parzedziałowego.
    @param sequence ciąg
    @return suma spójnego podciągu o maksymalnej sumie
    */
    double find_maxsum_subseq2(const std::vector<double> & sequence);
}

#endif
