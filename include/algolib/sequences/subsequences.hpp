/**!
 * \file subsequences.hpp
 * \brief Algorithms for subsequences
 */
#ifndef SUBSEQS_HPP_
#define SUBSEQS_HPP_

#include <cstdlib>
#include <algorithm>
#include <vector>
#include <functional>

namespace internal
{
    template <typename T>
    int search_ord(const std::function<bool(T, T)> & order, const std::vector<T> & sequence,
                   const std::vector<int> & subseq_last, int index_begin, int index_end,
                   int index_elem)
    {
        if(index_begin == index_end)
            return index_begin;

        int index_middle = (index_begin + index_end) / 2;

        if(order(sequence[index_elem], sequence[subseq_last[index_middle]]))
            return search_ord(order, sequence, subseq_last, index_middle + 1, index_end,
                              index_elem);

        return search_ord(order, sequence, subseq_last, index_begin, index_middle, index_elem);
    }
}

namespace algolib
{
    /*!
     * \brief Constructs longest ordered subsequence
     * \param sequence sequence of elements
     * \param order order function of elements in subsequence
     * \return longest ordered subsequence (least lexicographically)
     */
    template <typename T>
    std::vector<T> longest_ordered(const std::vector<T> & sequence,
                                   const std::function<bool(T, T)> & order)
    {
        std::vector<T> longest_subseq;
        std::vector<int> subseq_last(1, 0);
        std::vector<int> previous_elems(sequence.size(), -1);

        for(size_t i = 1; i < sequence.size(); ++i)
            if(order(sequence[i], sequence[subseq_last.back()]))
            {
                previous_elems[i] = subseq_last.back();
                subseq_last.push_back(i);
            }
            else
            {
                int index = internal::search_ord(order, sequence, subseq_last, 0,
                                                 subseq_last.size() - 1, i);

                subseq_last[index] = i;
                previous_elems[i] = index > 0 ? subseq_last[index - 1] : -1;
            }

        for(int j = subseq_last.back(); j >= 0; j = previous_elems[j])
            longest_subseq.push_back(sequence[j]);

        reverse(longest_subseq.begin(), longest_subseq.end());

        return longest_subseq;
    }

    /*!
     * \brief Wyznaczanie spójnego podciągu o maksymalnej sumie w sposób dynamiczny
     * \param sequence ciąg
     * \return elementy spójnego podciągu o maksymalnej sumie
     */
    std::vector<double> maximum_subarray(const std::vector<double> & sequence);

    /*!
     * \brief Wyznaczanie maksymalnej sumy spójnego podciągu za pomocą drzewa przedziałowego
     * \param sequence ciąg
     * \return maksymalna suma
     */
    double maximal_subsum(const std::vector<double> & sequence);
}

#endif
