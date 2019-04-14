/**
 * @file maximum_subarray.hpp
 * @brief Algorithms for maximum subarray.
 */
#ifndef _MAXIMUM_SUBARRAY_HPP_
#define _MAXIMUM_SUBARRAY_HPP_

#include <cstdlib>
#include <algorithm>
#include <vector>

namespace algolib
{
    /**
     * Wyznaczanie spójnego podciągu o maksymalnej sumie w sposób dynamiczny.
     * @param sequence ciąg
     * @return elementy spójnego podciągu o maksymalnej sumie
     */
    std::vector<double> find_maximum_subarray(const std::vector<double> & sequence);

    /**
     * Wyznaczanie maksymalnej sumy spójnego podciągu za pomocą drzewa przedziałowego.
     * @param sequence ciąg
     * @return maksymalna suma
     */
    double find_maximal_sum(const std::vector<double> & sequence);
}

#endif
