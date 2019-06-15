//! Suffix array structure.
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
    return txt.substr(suf_arr[i], std::string::npos);
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
    std::vector<size_t> t(txt.begin(), txt.end());

    suf_arr = create_array(t, 128);
}

void alte::suffix_array::init_inv()
{
    inv_arr.resize(length);

    for(size_t i = 0; i < length; ++i)
        inv_arr[suf_arr[i]] = i;
}

void alte::suffix_array::init_lcp()
{
    lcp_arr.resize(length);

    for(size_t i = 0, len = 0; i < length; ++i, len = len == 0 ? 0 : len - 1)
        if(inv_arr[i] >= 1)
        {
            size_t j = suf_arr[inv_arr[i] - 1];

            while(i + len < length && j + len < length && txt[i + len] == txt[j + len])
                ++len;

            lcp_arr[inv_arr[i]] = len;
        }
}

std::vector<size_t> alte::suffix_array::create_array(const std::vector<size_t> & t, size_t k)
{
    if(t.size() < 2)
        return std::vector<size_t>({0});

    size_t n2 = (t.size() + 2) / 3, n1 = (t.size() + 1) / 3, n0 = t.size() / 3, n02 = n0 + n2;
    std::vector<size_t> t12;

    for(size_t i = 0; i < t.size() + n2 - n1; ++i)
        if(i % 3 != 0)
            t12.push_back(i);

    sort_by_keys(t12, t, 2, k);
    sort_by_keys(t12, t, 1, k);
    sort_by_keys(t12, t, 0, k);

    size_t ix = 0, last0 = k, last1 = k, last2 = k;
    std::vector<size_t> tn12(n02, 0);

    for(size_t i : t12)
    {
        if(get_elem(t, i) != last0 || get_elem(t, i + 1) != last1 || get_elem(t, i + 2) != last2)
        {
            ++ix;
            last0 = get_elem(t, i);
            last1 = get_elem(t, i + 1);
            last2 = get_elem(t, i + 2);
        }

        if(i % 3 == 1)
            tn12[i / 3] = ix;
        else
            tn12[i / 3 + n2] = ix;
    }

    std::vector<size_t> sa0, sa12;

    if(ix < n02)
    {
        sa12 = create_array(tn12, ix + 1);

        for(size_t i = 0; i < sa12.size(); ++i)
            tn12[sa12[i]] = i + 1;
    }
    else
    {
        sa12.resize(n02, 0);

        for(size_t i = 0; i < tn12.size(); ++i)
            sa12[tn12[i] - 1] = i;
    }

    for(size_t i : sa12)
        if(i < n2)
            sa0.push_back(3 * i);

    sort_by_keys(sa0, t, 0, k);

    return merge(t, sa0, tn12, sa12);
}

std::vector<size_t> alte::suffix_array::merge(const std::vector<size_t> & t0,
                                              const std::vector<size_t> & sa0,
                                              const std::vector<size_t> & t12,
                                              const std::vector<size_t> & sa12)
{
    std::vector<size_t> sa;
    size_t n2 = (t0.size() + 2) / 3, n1 = (t0.size() + 1) / 3;
    size_t i0 = 0, i12 = n2 - n1;

    while(i0 < sa0.size() && i12 < sa12.size())
    {
        size_t pos12 = sa12[i12] < n2 ? sa12[i12] * 3 + 1 : (sa12[i12] - n2) * 3 + 2;
        size_t pos0 = sa0[i0];

        if(sa12[i12] < n2 ? std::make_tuple(get_elem(t0, pos12), get_elem(t12, sa12[i12] + n2))
                                    <= std::make_tuple(get_elem(t0, pos0), get_elem(t12, pos0 / 3))
                          : std::make_tuple(get_elem(t0, pos12), get_elem(t0, pos12 + 1),
                                            get_elem(t12, sa12[i12] - n2 + 1))
                                    <= std::make_tuple(get_elem(t0, pos0), get_elem(t0, pos0 + 1),
                                                       get_elem(t12, pos0 / 3 + n2)))
        {
            sa.push_back(pos12);
            ++i12;
        }
        else
        {
            sa.push_back(pos0);
            ++i0;
        }
    }

    while(i12 < sa12.size())
    {
        sa.push_back(sa12[i12] < n2 ? sa12[i12] * 3 + 1 : (sa12[i12] - n2) * 3 + 2);
        ++i12;
    }

    while(i0 < sa0.size())
    {
        sa.push_back(sa0[i0]);
        ++i0;
    }

    return sa;
}

void alte::suffix_array::sort_by_keys(std::vector<size_t> & v, const std::vector<size_t> & keys,
                                      size_t shift, size_t k)
{
    std::queue<size_t> buckets[k];
    size_t j = 0;

    for(int i : v)
        buckets[get_elem(keys, i + shift)].push(i);

    for(std::queue<size_t> & e : buckets)
        while(!e.empty())
        {
            v[j] = e.front();
            e.pop();
            ++j;
        }
}

size_t alte::suffix_array::get_elem(const std::vector<size_t> & v, size_t i)
{
    return i < v.size() ? v[i] : 0;
}
