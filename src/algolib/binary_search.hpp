// BINARY SEARCH: ZNAJDUJE ELEMENT W UPORZĄDKOWANYM CIĄGU
#ifndef BINARY_SEARCH_HPP
#define BINARY_SEARCH_HPP

#include <cstdlib>
#include <vector>
#include <algorithm>

namespace algolib
{
    /**
    WYSZUKIWANIE ELEMENTU W CIĄGU
    @param sequence posortowany ciąg
    @param element poszukiwany element
    @param index_begin indeks początku ciągu
    @param index_end indeks końca ciągu
    @return czy element znajduje się w ciągu
    */
    template<typename E>
    bool binary_search(const std::vector<E> & sequence, E element, int index_begin=0,
        int index_end=-1);
}

#endif

