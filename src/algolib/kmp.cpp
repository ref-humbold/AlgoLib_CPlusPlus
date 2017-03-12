// ALGORYTM KNUTHA-MORRISA-PRATTA WYSZUKIWANIA WZORCA W TEKŚCIE
#include "kmp.hpp"

namespace details = algolib::detail;

std::vector<int> details::prefixes(const std::string & pattern)
{
    std::vector<int> pi(1, 0);
    int pos = 0;

    for(const char & ltr : pattern)
    {
        while(pos > 0 && pattern[pos] != ltr)
            pos = pi[pos-1];

        if(pattern[pos] == ltr)
            ++pos;

        pi.push_back(pos);
    }

    return pi;
}

std::vector<int> algolib::kmp(const std::string & text, const std::string & pattern)
{
    std::vector<int> places;
    std::vector<int> pi = details::prefixes(pattern);
    size_t pos = 0;

    for(size_t i = 0; i < text.size(); ++i)
    {
        while(pos > 0 && pattern[pos] != text[i])
            pos = pi[pos-1];

        if(pattern[pos] == text[i])
            ++pos;

        if(pos == pattern.size())
        {
            places.push_back(i-pattern.size()+1);
            pos = pi[pos-1];
        }
    }

    return places;
}
