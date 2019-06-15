//! Vector sorting algorithms.
#include "algolib/sequences/vector_sorting.hpp"

int impl::choose_pivot(int size)
{
    srand(time(nullptr));

    int candidate1 = rand() % size, candidate2 = rand() % size, candidate3 = rand() % size;

    if(std::min(candidate2, candidate3) <= candidate1
       && candidate1 <= std::max(candidate2, candidate3))
        return candidate2;

    if(std::min(candidate1, candidate3) <= candidate2
       && candidate2 <= std::max(candidate1, candidate3))
        return candidate2;

    return candidate3;
}

void impl::validate_indices(int size, int index_begin, int index_end)
{
    if(index_begin < 0 || index_end > size)
        throw std::invalid_argument("Sequence beginning index out of range.");

    if(index_end < 0 || index_end > size)
        throw std::invalid_argument("Sequence ending index out of range.");
}
