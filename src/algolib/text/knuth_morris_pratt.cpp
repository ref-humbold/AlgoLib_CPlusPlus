/*!
 * \file knuth_morris_pratt.cpp
 * \brief Knuth-Morris-Pratt algorithm for pattern searching.
 */
#include "algolib/text/knuth_morris_pratt.hpp"

namespace alte = algolib::text;

namespace internal
{
    // Computes Knuth's PI prefix function values for given pattern.
    std::vector<size_t> prefixes(const std::string & pattern)
    {
        std::vector<size_t> pi = {0};
        size_t position = 0;

        for(const char & letter : pattern.substr(1))
        {
            while(position > 0 && pattern[position] != letter)
                position = pi[position - 1];

            if(pattern[position] == letter)
                ++position;

            pi.push_back(position);
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
    size_t position = 0;

    for(size_t i = 0; i < text.size(); ++i)
    {
        while(position > 0 && pattern[position] != text[i])
            position = pi[position - 1];

        if(pattern[position] == text[i])
            ++position;

        if(position == pattern.size())
        {
            places.push_back(i - pattern.size() + 1);
            position = pi[position - 1];
        }
    }

    return places;
}
