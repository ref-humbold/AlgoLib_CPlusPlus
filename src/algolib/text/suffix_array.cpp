/*!
 * \file suffix_array.cpp
 * \brief Structure of suffix array.
 */
#include "algolib/text/suffix_array.hpp"

namespace alte = algolib::text;

std::string alte::suffix_array::at(size_t i) const
{
    if(i >= size_)
        throw std::out_of_range("Suffix array index out of range");

    return operator[](i);
}

std::string alte::suffix_array::operator[](size_t i) const
{
    return text_.substr(suf_arr[i], std::string::npos);
}

size_t alte::suffix_array::index_at(size_t i) const
{
    if(i >= size_)
        throw std::out_of_range("Suffix array index out of range");

    return suf_arr[i];
}

size_t alte::suffix_array::index_of(size_t suf) const
{
    if(suf >= size_)
        throw std::out_of_range("Text index out of range");

    return inv_arr[suf];
}

size_t alte::suffix_array::lcp(size_t suf1, size_t suf2) const
{
    if(suf1 >= size_ || suf2 >= size_)
        throw std::out_of_range("Text index out of range");

    if(suf1 == suf2)
        return size_ - suf1;

    size_t i1 = std::min(inv_arr[suf1], inv_arr[suf2]);
    size_t i2 = std::max(inv_arr[suf1], inv_arr[suf2]);
    size_t res = lcp_arr[i1 + 1];

    for(size_t i = i1 + 2; i <= i2; ++i)
        res = std::min(res, lcp_arr[i]);

    return res;
}

void alte::suffix_array::init_array()
{
    std::vector<size_t> t(text_.begin(), text_.end());

    suf_arr = create_array(t);
}

void alte::suffix_array::init_inv()
{
    inv_arr.resize(size_);

    for(size_t i = 0; i < size_; ++i)
        inv_arr[suf_arr[i]] = i;
}

void alte::suffix_array::init_lcp()
{
    lcp_arr.resize(size_);

    for(size_t i = 0, len = 0; i < size_; ++i, len = len == 0 ? 0 : len - 1)
        if(inv_arr[i] >= 1)
        {
            size_t j = suf_arr[inv_arr[i] - 1];

            while(i + len < size_ && j + len < size_ && text_[i + len] == text_[j + len])
                ++len;

            lcp_arr[inv_arr[i]] = len;
        }
}

std::vector<size_t> alte::suffix_array::create_array(const std::vector<size_t> & txt)
{
    if(txt.size() < 2)
        return {0};

    size_t length2 = (txt.size() + 2) / 3, length1 = (txt.size() + 1) / 3, length0 = txt.size() / 3;
    size_t length02 = length0 + length2;
    std::vector<size_t> indices12;

    for(size_t i = 0; i < txt.size() + length2 - length1; ++i)
        if(i % 3 != 0)
            indices12.push_back(i);

    sort_indices(indices12, txt, 2);
    sort_indices(indices12, txt, 1);
    sort_indices(indices12, txt, 0);

    size_t code = 0;
    std::tuple<size_t, size_t, size_t> last = {std::numeric_limits<size_t>::max(),
        std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max()};
    std::vector<size_t> text12(length02, 0);

    for(size_t i : indices12)
    {
        std::tuple<size_t, size_t, size_t> elems = {get_elem(txt, i), get_elem(txt, i + 1),
            get_elem(txt, i + 2)};

        if(last != elems)
        {
            ++code;
            last = elems;
        }

        if(i % 3 == 1)
            text12[i / 3] = code;
        else
            text12[i / 3 + length2] = code;
    }

    std::vector<size_t> sa0, sa12;

    if(code < length02)
    {
        sa12 = create_array(text12);

        for(size_t i = 0; i < sa12.size(); ++i)
            text12[sa12[i]] = i + 1;
    }
    else
    {
        sa12.resize(length02, 0);

        for(size_t i = 0; i < text12.size(); ++i)
            sa12[text12[i] - 1] = i;
    }

    for(size_t i : sa12)
        if(i < length2)
            sa0.push_back(3 * i);

    sort_indices(sa0, txt, 0);

    return merge(txt, sa0, text12, sa12);
}

std::vector<size_t> alte::suffix_array::merge(const std::vector<size_t> & t0,
        const std::vector<size_t> & sa0,
        const std::vector<size_t> & t12,
        const std::vector<size_t> & sa12)
{
    std::vector<size_t> sa_merged;
    size_t length2 = (t0.size() + 2) / 3, length1 = (t0.size() + 1) / 3;
    size_t index0 = 0, index12 = length2 - length1;

    while(index0 < sa0.size() && index12 < sa12.size())
    {
        size_t pos12 =
                sa12[index12] < length2 ? sa12[index12] * 3 + 1 : (sa12[index12] - length2) * 3 + 2;
        size_t pos0 = sa0[index0];

        bool cond =
                sa12[index12] < length2
                        ? std::make_tuple(get_elem(t0, pos12),
                                  get_elem(t12, sa12[index12] + length2))
                                  <= std::make_tuple(get_elem(t0, pos0), get_elem(t12, pos0 / 3))
                        : std::make_tuple(get_elem(t0, pos12), get_elem(t0, pos12 + 1),
                                  get_elem(t12, sa12[index12] - length2 + 1))
                                  <= std::make_tuple(get_elem(t0, pos0), get_elem(t0, pos0 + 1),
                                          get_elem(t12, pos0 / 3 + length2));

        if(cond)
        {
            sa_merged.push_back(pos12);
            ++index12;
        }
        else
        {
            sa_merged.push_back(pos0);
            ++index0;
        }
    }

    while(index12 < sa12.size())
    {
        sa_merged.push_back(sa12[index12] < length2 ? sa12[index12] * 3 + 1
                                                    : (sa12[index12] - length2) * 3 + 2);
        ++index12;
    }

    while(index0 < sa0.size())
    {
        sa_merged.push_back(sa0[index0]);
        ++index0;
    }

    return sa_merged;
}

void alte::suffix_array::sort_indices(
        std::vector<size_t> & indices, const std::vector<size_t> & values, size_t shift)
{
    std::map<size_t, std::queue<size_t>> buckets;
    size_t j = 0;

    for(int i : indices)
    {
        size_t v = get_elem(values, i + shift);

        buckets.emplace(v, std::queue<size_t>());
        buckets[v].push(i);
    }

    std::vector<std::queue<size_t>> queues;

    std::transform(buckets.begin(), buckets.end(), std::back_inserter(queues),
            [](std::pair<size_t, std::queue<size_t>> p) { return p.second; });

    for(std::queue<size_t> & e : queues)
        while(!e.empty())
        {
            indices[j] = e.front();
            e.pop();
            ++j;
        }
}

size_t alte::suffix_array::get_elem(const std::vector<size_t> & v, size_t i)
{
    return i < v.size() ? v[i] : 0;
}
