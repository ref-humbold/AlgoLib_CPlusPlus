// SUFFIX ARRAY STRUCTURE
#include "algolib/text/suffix_array.hpp"

namespace alte = algolib::text;

std::string alte::suffix_array::operator[](int i)
{
    return text.substr(array[i], std::string::npos);
}
