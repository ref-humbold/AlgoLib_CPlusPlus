/**!
 * \file longest_common_subsequence.hpp
 * \brief Algorithm for longest common subsequence
 */
#ifndef LONGEST_COMMON_SUBSEQUENCE_HPP_
#define LONGEST_COMMON_SUBSEQUENCE_HPP_

#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>

namespace algolib::sequences
{
    template <typename T>
    size_t count_lcs_length(const std::vector<T> & sequence1, const std::vector<T> & sequence2)
    {
        const std::vector<T> & short_sequence =
                sequence1.size() <= sequence2.size() ? sequence1 : sequence2;
        const std::vector<T> & long_sequence =
                sequence1.size() > sequence2.size() ? sequence1 : sequence2;

        std::vector<size_t> previous_lcs(short_sequence.size() + 1, 0);

        for(auto && element : long_sequence)
        {
            std::vector<size_t> next_lcs = {0};

            for(size_t i = 0; i < short_sequence.size(); ++i)
                next_lcs.push_back(element == short_sequence[i]
                                           ? previous_lcs[i] + 1
                                           : std::max(previous_lcs[i + 1], next_lcs.back()));

            previous_lcs = next_lcs;
        }

        return previous_lcs.back();
    }

    size_t count_lcs_length(const std::string & text1, const std::string & text2);
}

#endif
