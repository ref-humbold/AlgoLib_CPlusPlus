// BINARY SEARCH: ZNAJDUJE ELEMENT W UPORZ�DKOWANYM CIĄGU
#include "binary_search.hpp"

template<typename E>
bool algolib::binary_search(const std::vector<E> & sequence, E element, int index_begin,
    int index_end)
{
    index_begin = (index_begin+sequence.size())%sequence.size();
    index_end = (index_end+sequence.size())%sequence.size();

    if(index_begin > index_end)
        return false;

    int index_middle = (index_begin+index_end)/2;

    if(sequence[index_middle] == element)
        return true;
    else if(sequence[index_middle] < element)
        return binary_search(sequence, element, index_middle+1, index_end);
    else
        return binary_search(sequence, element, index_begin, index_middle-1);
}

