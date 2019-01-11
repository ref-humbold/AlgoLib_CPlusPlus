// SUFFIX ARRAY STRUCTURE
#ifndef _SUFFIX_ARRAY_HPP_
#define _SUFFIX_ARRAY_HPP_

#include <cstdlib>
#include <algorithm>
#include <exception>
#include <queue>
#include <stdexcept>
#include <string>
#include <vector>

namespace algolib
{
    namespace text
    {
        class suffix_array
        {
        public:
            explicit suffix_array(const std::string & s) : length{s.length()}, text{s}
            {
                init_array();
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

            std::string get_text() const
            {
                return text;
            }

            size_t size() const
            {
                return length;
            }

            std::string at(size_t i) const;
            std::string operator[](size_t i) const;
            size_t index(size_t suf) const;
            size_t lcp(size_t suf1, size_t suf2) const;

        private:
            void init_array();
            void init_lcp();
            void lex_sort(std::vector<std::queue<size_t>> & buckets, size_t ix);

            /// Size of suffix array
            size_t length;

            /// Text
            std::string text;

            /// Suffix array
            std::vector<size_t> suf_arr;

            /// Inversed suffix array
            std::vector<size_t> inv_arr;

            /// Array of longest common prefices
            std::vector<size_t> lcp_arr;
        };
    }
}

#endif
