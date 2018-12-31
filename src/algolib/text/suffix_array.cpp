// SUFFIX ARRAY STRUCTURE
#include "algolib/text/suffix_array.hpp"

namespace alte = algolib::text;

std::string alte::suffix_array::at(size_t i) const
{
    if(i >= length)
        throw std::out_of_range("Suffix array index out of range");

    return text.substr(suf_arr[i], std::string::npos);
}

std::string alte::suffix_array::operator[](size_t i) const
{
    return at(i);
}

size_t alte::suffix_array::index(size_t suf) const
{
    if(suf >= length)
        throw std::out_of_range("Text index out of range");

    return inv_arr[suf];
}

size_t alte::suffix_array::lcp(size_t suf1, size_t suf2) const
{
    if(suf1 >= length || suf2 >= length)
        throw std::out_of_range("Text index out of range");

    if(suf1 == suf2)
        return length - suf1;

    size_t i1 = std::min(inv_arr[suf1], inv_arr[suf2]);
    size_t i2 = std::max(inv_arr[suf1], inv_arr[suf2]);
    size_t res = lcp_arr[i1 + 1];

    for(size_t i = i1 + 2; i <= i2; ++i)
        res = std::min(res, lcp_arr[i]);

    return res;
}

void alte::suffix_array::init_array()
{
    std::vector<std::queue<size_t>> buckets(128);

    for(size_t i = 0; i < text.size(); ++i)
        suf_arr.push_back(i);

    lex_sort(buckets, 0, 0, length);
    inv_arr.resize(length);

    for(size_t i = 0; i < length; ++i)
        inv_arr[suf_arr[i]] = i;
}

void alte::suffix_array::lex_sort(std::vector<std::queue<size_t>> & buckets, size_t ix, size_t beg,
                                  size_t end)
{
    if(end - beg < 2 || ix >= length)
        return;

    std::vector<size_t> sizes;

    for(size_t i = beg; i < end; ++i)
    {
        if(suf_arr[i] + ix < length)
            buckets[+text[suf_arr[i] + ix]].push(suf_arr[i]);
        else
            buckets[0].push(suf_arr[i]);
    }

    size_t j = beg;

    for(std::queue<size_t> & q : buckets)
    {
        if(!q.empty())
            sizes.push_back(q.size());

        while(!q.empty())
        {
            suf_arr[j] = q.front();
            q.pop();
            ++j;
        }
    }

    size_t offset = 0;

    for(size_t s : sizes)
    {
        lex_sort(buckets, ix + 1, beg + offset, beg + offset + s);
        offset += s;
    }
}

void alte::suffix_array::init_lcp()
{
    size_t len = 0;

    lcp_arr.resize(length);

    for(size_t i = 0; i < length; ++i)
    {
        if(inv_arr[i] >= 1)
        {
            size_t j = suf_arr[inv_arr[i] - 1];

            while(text[i + len] == text[j + len])
                ++len;

            lcp_arr[inv_arr[i]] = len;
        }

        if(len > 0)
            --len;
    }
}
