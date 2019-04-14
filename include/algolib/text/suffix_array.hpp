/**
 * @file suffix_array.hpp
 * @brief Suffix array structure
 */
#ifndef _SUFFIX_ARRAY_HPP_
#define _SUFFIX_ARRAY_HPP_

#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <queue>
#include <string>
#include <tuple>
#include <vector>

namespace algolib
{
    namespace text
    {
        class suffix_array
        {
        public:
            explicit suffix_array(const std::string & s) : length{s.length()}, txt{s}
            {
                init_array();
                init_inv();
                init_lcp();
            }

            explicit suffix_array(const char * s) : suffix_array(std::string(s))
            {
            }

            ~suffix_array() = default;
            suffix_array(const suffix_array &) = default;
            suffix_array(suffix_array &&) = default;
            suffix_array & operator=(const suffix_array &) = default;
            suffix_array & operator=(suffix_array &&) = default;

            std::string text() const
            {
                return txt;
            }

            size_t size() const
            {
                return length;
            }

            std::string at(size_t i) const;
            std::string operator[](size_t i) const;
            size_t index_at(size_t i) const;
            size_t index_of(size_t suf) const;
            size_t lcp(size_t suf1, size_t suf2) const;

        private:
            void init_array();
            void init_inv();
            void init_lcp();
            std::vector<size_t> create_array(const std::vector<size_t> & t, size_t k);
            std::vector<size_t> merge(const std::vector<size_t> & t0,
                                      const std::vector<size_t> & sa0,
                                      const std::vector<size_t> & tn12,
                                      const std::vector<size_t> & sa12);
            void sort_by_keys(std::vector<size_t> & v, const std::vector<size_t> & keys,
                              size_t shift, size_t k);
            size_t get_elem(const std::vector<size_t> & v, size_t i);

            size_t length;
            std::string txt;
            std::vector<size_t> suf_arr;
            std::vector<size_t> inv_arr;
            std::vector<size_t> lcp_arr;
        };
    }
}

#endif
