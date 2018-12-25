// SUFFIX ARRAY STRUCTURE
#include "algolib/text/suffix_array.hpp"

namespace alte = algolib::text;

std::string alte::suffix_array::operator[](size_t i)
{
    return text.substr(array[i], std::string::npos);
}

void alte::suffix_array::init_array()
{
}

void alte::suffix_array::init_lcp()
{
    size_t len = 0;

    for(size_t i = 0; i < text.length(); ++i)
    {
        if(inv[i] >= 1)
        {
            size_t j = array[inv[i] - 1];

            while(text[i + len] == text[j + len])
            {
                ++len;
            }

            lcp.push_back(len);
        }

        if(len > 0)
            --len;
    }
}
