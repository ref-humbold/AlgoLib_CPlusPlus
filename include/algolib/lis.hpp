/**
 * @file lis.hpp
 * @brief Longest increasing subsequence (least lexicographically).
 */
#ifndef LIS_HPP_
#define LIS_HPP_

#include <cstdlib>
#include <algorithm>
#include <vector>

namespace detail
{
    /**
     * Wyszukiwanie miejsca dla elementu
     * @param sequence ciąg wejściowy
     * @param subseq_last końcowe elementy podciągów
     * @param index_begin indeks początku
     * @param index_end indeks końca
     * @param index_elem indeks elementu
     * @return indeks miejsca elementu w tablicy długości
     */
    template <typename T>
    int search(const std::vector<T> & sequence, const std::vector<int> & subseq_last,
               int index_begin, int index_end, int index_elem)
    {
        if(index_begin == index_end)
            return index_begin;

        int index_middle = (index_begin + index_end) / 2;

        if(sequence[index_elem] > sequence[subseq_last[index_middle]])
            return search(sequence, subseq_last, index_middle + 1, index_end, index_elem);
        else
            return search(sequence, subseq_last, index_begin, index_middle, index_elem);
    }
}

namespace algolib
{
    /**
     * Wyznaczanie najdłuższego podciągu rosnącego.
     * @param sequence ciąg wejściowy
     * @return najdłuższy podciąg rosnący
     */
    template <typename T>
    std::vector<T> find_lis(const std::vector<T> & sequence)
    {
        std::vector<T> longest_subseq;
        std::vector<int> subseq_last(1, 0);
        std::vector<int> previous_elems(sequence.size(), -1);

        for(size_t i = 1; i < sequence.size(); ++i)
            if(sequence[i] > sequence[subseq_last.back()])
            {
                previous_elems[i] = subseq_last.back();
                subseq_last.push_back(i);
            }
            else
            {
                int index = detail::search(sequence, subseq_last, 0, subseq_last.size() - 1, i);

                subseq_last[index] = i;
                previous_elems[i] = index > 0 ? subseq_last[index - 1] : -1;
            }

        for(int j = subseq_last.back(); j >= 0; j = previous_elems[j])
            longest_subseq.push_back(sequence[j]);

        reverse(longest_subseq.begin(), longest_subseq.end());

        return longest_subseq;
    }
}

#endif
