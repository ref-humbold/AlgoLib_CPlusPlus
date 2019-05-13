// Karp-Miller-Rosenberg algorithm.
#include "algolib/text/kmr.hpp"

namespace alte = algolib::text;

namespace
{
    std::map<std::string, int> sign_letters(const std::string & text)
    {
        std::map<std::string, int> factors;
        std::vector<std::string> letters;
        int code_value = 0;

        for(size_t i = 0; i < text.size(); ++i)
            letters.push_back(text.substr(i, 1));

        sort(letters.begin(), letters.end());
        factors.emplace(letters[0], code_value);

        for(auto it = letters.begin() + 1; it != letters.end(); ++it)
            if(*it != *(it - 1))
            {
                ++code_value;
                factors.emplace(*it, code_value);
            }

        return factors;
    }

    void double_length(int new_length, const std::string & text,
                       std::map<std::string, int> & factors)
    {
        std::vector<std::tuple<int, int, int>> codes;
        int code_value = 0;

        for(size_t i = 0; i <= text.size() - new_length; ++i)
        {
            std::string s1 = text.substr(i, new_length / 2);
            std::string s2 = text.substr(i + new_length / 2, new_length / 2);

            codes.push_back(std::make_tuple(factors[s1], factors[s2], i));
        }

        sort(codes.begin(), codes.end());
        factors.emplace(text.substr(std::get<2>(codes[0]), new_length), code_value);

        for(auto it = codes.begin() + 1; it != codes.end(); ++it)
            if(std::get<0>(*it) != std::get<0>(*(it - 1))
               || std::get<1>(*it) != std::get<1>(*(it - 1)))
            {
                ++code_value;
                factors.emplace(text.substr(std::get<2>(*it), new_length), code_value);
            }
    }
}

std::map<std::string, int> alte::kmr(const std::string & text)
{
    std::map<std::string, int> factors = sign_letters(text);

    for(size_t length = 2; length <= text.size(); length <<= 1)
        double_length(length, text, factors);

    return factors;
}
