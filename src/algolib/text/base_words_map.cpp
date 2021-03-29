/*!
 * \file base_words_map.cpp
 * \brief Structure of base words map using Karp-Miller-Rosenberg algorithm
 */
#include "algolib/text/base_words_map.hpp"
#include <exception>
#include <stdexcept>

namespace alte = algolib::text;

alte::base_words_map::code_t alte::base_words_map::code(size_t start, size_t length) const
{
    if(start > text_.size())
        throw std::out_of_range("Starting index out of range");

    size_t end = length > text_.size() - start ? text_.size() : start + length;

    if(end <= start)
        return {0, 0};

    auto it = factors.find(std::make_pair(start, end));

    if(it != factors.end())
        return {it->second, 0};

    size_t n = get_max_length(end - start);
    return {factors.at(std::make_pair(start, start + n)), factors.at(std::make_pair(end - n, end))};
}

void alte::base_words_map::create()
{
    size_t code_value = extend(
            1, 0, [&](size_t i, size_t length) -> std::tuple<size_t, size_t, size_t, size_t> {
                return {text_[i], 1 + text_[i], i, i + length};
            });

    for(size_t current_length = 2; current_length <= text_.size(); current_length *= 2)
        code_value = extend(
                current_length, code_value,
                [&](size_t i, size_t length) -> std::tuple<size_t, size_t, size_t, size_t> {
                    return {factors.at(std::make_pair(i, i + length / 2)),
                            factors.at(std::make_pair(i + length / 2, i + length)), i, i + length};
                });
}

size_t alte::base_words_map::extend(
        size_t length, size_t code_value,
        std::function<std::tuple<size_t, size_t, size_t, size_t>(size_t, size_t)> func)
{
    code_t previous_code = {0, 0};
    std::vector<std::tuple<size_t, size_t, size_t, size_t>> codes;

    for(size_t i = 0; i <= text_.size() - length; ++i)
        codes.push_back(func(i, length));

    sort(codes.begin(), codes.end());

    for(auto && code : codes)
    {
        code_t code_pair = std::make_pair(std::get<0>(code), std::get<1>(code));

        if(code_pair != previous_code)
        {
            ++code_value;
            previous_code = code_pair;
        }

        factors.emplace(std::make_pair(std::get<2>(code), std::get<3>(code)), code_value);
    }

    return code_value;
}

size_t alte::base_words_map::get_max_length(size_t n) const
{
    size_t prev = 0, power = 1;

    while(power < n)
    {
        prev = power;
        power *= 2;
    }

    return prev;
}
