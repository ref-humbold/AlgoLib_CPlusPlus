/**!
 * \file longest_common_subsequence.cpp
 * \brief Algorithm for longest common subsequence
 */
#include "algolib/sequences/longest_common_subsequence.hpp"

namespace alse = algolib::sequences;

size_t alse::count_lcs_length(const std::string & text1, const std::string & text2)
{
    const std::string & short_text = text1.size() <= text2.size() ? text1 : text2;
    const std::string & long_text = text1.size() > text2.size() ? text1 : text2;

    std::vector<size_t> lcs(short_text.size() + 1, 0);

    for(auto && element : long_text)
    {
        size_t previous_above = lcs[0];

        for(size_t i = 0; i < short_text.size(); ++i)
        {
            size_t previous_diagonal = previous_above;

            previous_above = lcs[i + 1];
            lcs[i + 1] = element == short_text[i] ? previous_diagonal + 1
                                                  : std::max(previous_above, lcs[i]);
        }
    }

    return lcs.back();
}
