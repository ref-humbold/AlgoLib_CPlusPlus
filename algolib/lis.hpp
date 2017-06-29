// NAJMNIEJSZY LEKSYKOGRAFICZNIE NAJDŁUŻSZY PODCIĄG ROSNĄCY
#ifndef LIS_HPP
#define LIS_HPP

#include <cstdlib>
#include <vector>
#include <algorithm>

namespace detail
{
    /**
     * Wyszukiwanie miejsca dla elementu
     * @param sequence ciąg wejściowy
     * @param subseq_last końcowe elementy podciągów
     * @param index_begin indeks początku
     * @param index_end indeks końca
     * @param element indeks elementu
     * @return indeks miejsca elementu w tablicy długości
     */
    template<typename T>
    int search(const std::vector<T> & sequence, const std::vector<int> & subseq_last,
        int index_begin, int index_end, int element);
}

namespace algolib
{
    /**
     * Wyzanczanie najdłuższego podciągu rosnącego.
     * @param sequence ciąg wejściowy
     * @return najdłuższy podciąg rosnący
     */
    template<typename T>
    std::vector<T> find_lis(const std::vector<T> & sequence);
}

#endif
