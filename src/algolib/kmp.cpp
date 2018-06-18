// ALGORYTM KNUTHA-MORRISA-PRATTA WYSZUKIWANIA WZORCA W TEKŚCIE
#include "algolib/kmp.hpp"

std::vector<size_t> detail::prefixes(const std::string & pattern)
{
    std::vector<size_t> pi(1, 0);
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

std::vector<size_t> algolib::kmp(const std::string & text, const std::string & pattern)
{
    std::vector<size_t> places;
    std::vector<size_t> pi = detail::prefixes(pattern);
    size_t pos = 0;

    if(pattern == "")
        return std::vector<size_t>();

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
