/**!
 * \file subsequences.hpp
 * \brief Algorithms for subsequences
 */
#ifndef SUBSEQS_HPP_
#define SUBSEQS_HPP_

#include <cstdlib>
#include <algorithm>
#include <functional>
#include <vector>

namespace internal
{
    template <typename T, typename C = std::less<T>>
    int search_index(const std::vector<T> & sequence, const C & compare,
                     const std::vector<int> & subseq_last, int index_begin, int index_end,
                     int index_elem)
    {
        if(index_begin == index_end)
            return index_begin;

        int index_middle = (index_begin + index_end) / 2;

        if(compare(sequence[subseq_last[index_middle]], sequence[index_elem]))
            return search_index(sequence, compare, subseq_last, index_middle + 1, index_end,
                                index_elem);

        return search_index(sequence, compare, subseq_last, index_begin, index_middle, index_elem);
    }
}

namespace algolib::sequences
{
    /*!
     * \brief Constructs the longest increasing subsequence according to given order function.
     * \param sequence a sequence of elements
     * \return the longest increasing subsequence (least lexicographically)
     */
    template <typename T, typename C = std::less<T>>
    std::vector<T> longest_increasing(const std::vector<T> & sequence, const C & compare = C())
    {
        std::vector<T> longest_subseq = {};
        std::vector<int> subseq_last = {0};
        std::vector<int> previous_elems(sequence.size(), -1);

        for(size_t i = 1; i < sequence.size(); ++i)
            if(compare(sequence[subseq_last.back()], sequence[i]))
            {
                previous_elems[i] = subseq_last.back();
                subseq_last.push_back(i);
            }
            else
            {
                int index = internal::search_index<T>(sequence, compare, subseq_last, 0,
                                                      subseq_last.size() - 1, i);

                subseq_last[index] = i;
                previous_elems[i] = index > 0 ? subseq_last[index - 1] : -1;
            }

        for(int j = subseq_last.back(); j >= 0; j = previous_elems[j])
            longest_subseq.push_back(sequence[j]);

        std::reverse(longest_subseq.begin(), longest_subseq.end());
        return longest_subseq;
    }

    /*!
     * \brief Dynamically constructs coherent subarray with maximal sum.
     * \param sequence a sequence of numbers
     * \return the maximum subarray
     */
    std::vector<double> maximum_subarray(const std::vector<double> & sequence);

    /*!
     * \brief Calculates maximal sum from all coherent subarrays using interval tree.
     * \param sequence a sequence of numbers
     * \return the sum of maximum subarray
     */
    double maximal_subsum(const std::vector<double> & sequence);
}

#endif
