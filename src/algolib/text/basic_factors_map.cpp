/*!
 * \file basic_factors_map.cpp
 * \brief Structure of basic factors map using Karp-Miller-Rosenberg algorithm.
 */
#include "algolib/text/basic_factors_map.hpp"
#include <exception>
#include <stdexcept>

namespace alte = algolib::text;

alte::basic_factors_map::code_t alte::basic_factors_map::code(size_t start, size_t length) const
{
    if(start >= text_.size())
        throw std::out_of_range("Starting index out of bounds for text");

    size_t end = length == std::string::npos ? text_.size() : start + length;

    if(end > text_.size())
        throw std::out_of_range("Length exceeds text end");

    if(end <= start)
        throw std::invalid_argument("Range is empty");

    auto it = factors.find(std::make_pair(start, end));

    if(it != factors.end())
        return {it->second, 0};

    size_t n = get_max_length(end - start);
    return {factors.at(std::make_pair(start, start + n)), factors.at(std::make_pair(end - n, end))};
}

size_t alte::basic_factors_map::get_max_length(size_t n)
{
    size_t prev = 0, power = 1;

    while(power < n)
    {
        prev = power;
        power *= 2;
    }

    return prev;
}

void alte::basic_factors_map::create()
{
    size_t code_value =
            extend(1, 0, [&](size_t i, size_t) -> extension_code
                   { return extension_code(text_[i], 1 + text_[i], i); });

    for(size_t current_length = 2; current_length <= text_.size(); current_length *= 2)
        code_value =
                extend(current_length, code_value,
                       [&](size_t i, size_t length) -> extension_code
                       {
                           return extension_code(
                                   factors.at(std::make_pair(i, i + length / 2)),
                                   factors.at(std::make_pair(i + length / 2, i + length)), i);
                       });
}

size_t alte::basic_factors_map::extend(
        size_t length,
        size_t code_value,
        const extend_function_t & func)
{
    std::vector<extension_code> codes;

    codes.emplace_back(0, 0, -1);

    for(size_t i = 0; i <= text_.size() - length; ++i)
        codes.emplace_back(func(i, length));

    std::sort(codes.begin(), codes.end());

    for(size_t i = 1; i < codes.size(); ++i)
    {
        if(codes[i] != codes[i - 1])
            ++code_value;

        factors.emplace(std::make_pair(codes[i].index, codes[i].index + length), code_value);
    }

    return code_value;
}

bool alte::basic_factors_map::extension_code::operator==(const extension_code & code) const
{
    return prefix_code == code.prefix_code && suffix_code == code.suffix_code;
}

bool alte::basic_factors_map::extension_code::operator!=(const extension_code & code) const
{
    return !(*this == code);
}

bool alte::basic_factors_map::extension_code::operator<(const extension_code & code) const
{
    if(prefix_code < code.prefix_code)
        return true;

    if(prefix_code == code.prefix_code)
        return suffix_code < code.suffix_code;

    return false;
}
