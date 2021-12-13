/*!
 * \file knuth_morris_pratt.cpp
 * \brief Knuth-Morris-Pratt algorithm for pattern searching
 */
#include "algolib/text/knuth_morris_pratt.hpp"

namespace alte = algolib::text;

namespace internal
{
    // Computes Knuth's PI prefix function values for given pattern.
    std::vector<size_t> prefixes(const std::string & pattern)
    {
        std::vector<size_t> pi = {0};
        size_t pos = 0;

        for(const char & ltr : pattern)
        {
            while(pos > 0 && pattern[pos] != ltr)
                pos = pi[pos - 1];

            if(pattern[pos] == ltr)
                ++pos;

            pi.push_back(pos);
        }

        return pi;
    }
}

std::vector<size_t> alte::kmp_search(const std::string & text, const std::string & pattern)
{
    std::vector<size_t> places = {};

    if(pattern == "")
        return places;

    std::vector<size_t> pi = internal::prefixes(pattern);
    size_t pos = 0;

    for(size_t i = 0; i < text.size(); ++i)
    {
        while(pos > 0 && pattern[pos] != text[i])
            pos = pi[pos - 1];

        if(pattern[pos] == text[i])
            ++pos;

        if(pos == pattern.size())
        {
            places.push_back(i - pattern.size() + 1);
            pos = pi[pos - 1];
        }
    }

    return places;
}
