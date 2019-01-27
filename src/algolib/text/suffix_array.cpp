// SUFFIX ARRAY STRUCTURE
#include "algolib/text/suffix_array.hpp"

namespace alte = algolib::text;

std::string alte::suffix_array::at(size_t i) const
{
    if(i >= length)
        throw std::out_of_range("Suffix array index out of range");

    return operator[](i);
}

std::string alte::suffix_array::operator[](size_t i) const
{
    return text.substr(suf_arr[i], std::string::npos);
}

size_t alte::suffix_array::index_at(size_t i) const
{
    if(i >= length)
        throw std::out_of_range("Suffix array index out of range");

    return suf_arr[i];
}

size_t alte::suffix_array::index_of(size_t suf) const
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
    std::vector<std::queue<std::pair<size_t, size_t>>> buckets(128);
    std::vector<size_t> ranks(length);

    for(size_t i = 0; i < text.size(); ++i)
        buckets[+text[i]].push(std::make_pair(i, 1));

    size_t r = 1;

    for(auto & q : buckets)
    {
        size_t added = 0;

        while(!q.empty())
        {
            suf_arr.push_back(q.front().first);
            ranks[q.front().first] = r;
            q.pop();
            added = 1;
        }

        r += added;
    }

    buckets.resize(r);

    for(size_t i = 1; i < length; i *= 2)
        pref_sort(buckets, ranks, i);

    inv_arr.resize(length);

    for(size_t i = 0; i < length; ++i)
        inv_arr[suf_arr[i]] = i;
}

void alte::suffix_array::pref_sort(std::vector<std::queue<std::pair<size_t, size_t>>> & buckets,
                                   std::vector<size_t> & ranks, size_t pref_len)
{
    for(size_t i = 0; i < length; ++i)
        if(i + pref_len < length)
            buckets[ranks[i + pref_len]].push(std::make_pair(i, ranks[i + pref_len]));
        else
            buckets[0].push(std::make_pair(i, 0));

    std::pair<size_t, size_t> snd_order[length];
    size_t j = 0;

    for(auto & q : buckets)
        while(!q.empty())
        {
            snd_order[j] = q.front();
            q.pop();
            ++j;
        }

    for(size_t i = 0; i < length; ++i)
        buckets[ranks[snd_order[i].first]].push(snd_order[i]);

    size_t r = 0, k = 0;

    for(auto & q : buckets)
    {
        size_t added = 0, prev_rank = 0;

        while(!q.empty())
        {
            if(q.front().second != prev_rank)
            {
                prev_rank = q.front().second;
                ++r;
            }

            suf_arr[k] = q.front().first;
            ranks[q.front().first] = r;
            q.pop();
            ++k;
            added = 1;
        }

        r += added;
    }

    buckets.resize(r);
}

void alte::suffix_array::init_lcp()
{
    lcp_arr.resize(length);

    for(size_t i = 0, len = 0; i < length; ++i)
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
