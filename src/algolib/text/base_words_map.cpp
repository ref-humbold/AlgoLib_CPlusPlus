/*!
 * \file base_words_map.cpp
 * \brief Structure of base words map using Karp-Miller-Rosenberg algorithm
 */
#include "algolib/text/base_words_map.hpp"

namespace alte = algolib::text;

size_t alte::base_words_map::code(size_t start, size_t end = std::string::npos)
{
}

void alte::base_words_map::create()
{
    size_t currentLength = 2;
    size_t codeValue = extend(
            1, 0, [&](size_t i, size_t length) -> std::tuple<size_t, size_t, size_t, size_t> {
                return {text_[i], 1 + text_[i], i, i + length};
            });

    while(currentLength <= text_.length())
    {
        codeValue = extend(
                currentLength, codeValue,
                [&](size_t i, size_t length) -> std::tuple<size_t, size_t, size_t, size_t> {
                    return {factors.at(std::make_pair(i, i + length / 2)),
                            factors.at(std::make_pair(i + length / 2, i + length)), i, i + length};
                });
        currentLength *= 2;
    }
}

size_t alte::base_words_map::extend(
        size_t length, size_t code_value,
        std::function<std::tuple<size_t, size_t, size_t, size_t>(size_t, size_t)> func)
{
    return code_value;
}

size_t alte::base_words_map::get_max_length(size_t n)
{
    size_t prev = 0, power = 1;

    while(power < n)
    {
        prev = power;
        power *= 2;
    }

    return prev;
}
