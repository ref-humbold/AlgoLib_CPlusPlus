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
    /*!
     * \brief Computes length of the longest common subsequence of given sequences.
     * \param sequence1 first sequence
     * \param sequence2 second sequence
     * \return length of the longest common subsequence
     */
    template <typename T>
    size_t count_lcs_length(const std::vector<T> & sequence1, const std::vector<T> & sequence2)
    {
        const std::vector<T> & short_sequence =
                sequence1.size() <= sequence2.size() ? sequence1 : sequence2;
        const std::vector<T> & long_sequence =
                sequence1.size() > sequence2.size() ? sequence1 : sequence2;

        std::vector<size_t> lcs(short_sequence.size() + 1, 0);

        for(auto && element : long_sequence)
        {
            size_t previous_above = lcs[0];

            for(size_t i = 0; i < short_sequence.size(); ++i)
            {
                size_t previous_diagonal = previous_above;

                previous_above = lcs[i + 1];
                lcs[i + 1] = element == short_sequence[i] ? previous_diagonal + 1
                                                          : std::max(previous_above, lcs[i]);
            }
        }

        return lcs.back();
    }

    /*!
     * \brief Computes length of the longest common subsequence of given texts.
     * \param text1 first text
     * \param text2 second text
     * \return length of the longest common subsequence
     */
    size_t count_lcs_length(const std::string & text1, const std::string & text2);
}

#endif
