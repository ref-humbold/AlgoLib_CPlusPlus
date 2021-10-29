/**!
 * \file subsequences.hpp
 * \brief Algorithms for subsequences
 */
#ifndef SUBSEQS_HPP_
#define SUBSEQS_HPP_

#include <cstdlib>
#include <algorithm>
#include <functional>
#include <optional>
#include <vector>

namespace internal
{
    // Searches for index of element in list of subsequences.
    // (index_begin inclusive, index_end exclusive)
    template <typename T, typename C = std::less<T>>
    size_t search_index(const std::vector<T> & sequence, const C & compare,
                        const std::vector<size_t> & subsequence, size_t index_elem,
                        size_t index_begin, size_t index_end)
    {
        if(index_end - index_begin <= 1)
            return index_begin;

        size_t index_middle = (index_begin + index_end - 1) / 2;

        return compare(sequence[subsequence[index_middle]], sequence[index_elem])
                       ? search_index(sequence, compare, subsequence, index_elem, index_middle + 1,
                                      index_end)
                       : search_index(sequence, compare, subsequence, index_elem, index_begin,
                                      index_middle);
    }
}

namespace algolib::sequences
{
    /*!
     * \brief Constructs the longest increasing subsequence according to given order function.
     * \param sequence a sequence of elements
     * \return the longest increasing subsequence (least lexicographically)
     */
    template <typename T, typename Compare = std::less<T>>
    std::vector<T> longest_increasing(const std::vector<T> & sequence,
                                      const Compare & compare = Compare())
    {
        std::vector<T> longest_subsequence = {};
        std::vector<size_t> subsequence = {0};
        std::vector<std::optional<size_t>> previous_elems = {std::nullopt};

        for(size_t i = 1; i < sequence.size(); ++i)
            if(compare(sequence[subsequence.back()], sequence[i]))
            {
                previous_elems.push_back(std::make_optional(subsequence.back()));
                subsequence.push_back(i);
            }
            else
            {
                size_t index = internal::search_index<T>(sequence, compare, subsequence, i, 0,
                                                         subsequence.size());

                subsequence[index] = i;
                previous_elems.push_back(index > 0 ? std::make_optional(subsequence[index - 1])
                                                   : std::nullopt);
            }

        for(std::optional<size_t> j = std::make_optional(subsequence.back()); j.has_value();
            j = previous_elems[*j])
            longest_subsequence.push_back(sequence[j.value()]);

        std::reverse(longest_subsequence.begin(), longest_subsequence.end());
        return longest_subsequence;
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
