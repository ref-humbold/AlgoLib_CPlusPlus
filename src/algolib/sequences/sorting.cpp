/*!
 * \file sorting.cpp
 * \brief Algorithms for sorting vectors
 */
#include "algolib/sequences/sorting.hpp"
#include <algorithm>
#include <exception>
#include <stdexcept>

size_t internal::choose_pivot(std::uniform_int_distribution<size_t> & distribution,
                              std::default_random_engine & rand_eng)
{
    std::vector<size_t> candidates = {distribution(rand_eng), distribution(rand_eng),
                                      distribution(rand_eng)};

    std::sort(candidates.begin(), candidates.end());
    return candidates[1];
}

void internal::validate_indices(size_t size, size_t index_begin, size_t index_end)
{
    if(index_begin > size)
        throw std::out_of_range("Sequence beginning index out of range");

    if(index_end > size)
        throw std::out_of_range("Sequence ending index out of range");
}
