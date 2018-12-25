// SUFFIX ARRAY STRUCTURE
#ifndef _SUFFIX_ARRAY_HPP_
#define _SUFFIX_ARRAY_HPP_

#include <cstdlib>
#include <string>
#include <vector>

namespace algolib
{
    namespace text
    {
        class suffix_array
        {
        public:
            suffix_array(std::string s) : text{s}
            {
                init_array();
                init_lcp();
            }

            ~suffix_array() = default;
            suffix_array(const suffix_array &) = default;
            suffix_array(suffix_array &&) = default;
            suffix_array & operator=(const suffix_array &) = default;
            suffix_array & operator=(suffix_array &&) = default;

            std::string get_text()
            {
                return this->text;
            }

            std::string operator[](size_t i);

        private:
            void init_array();
            void init_lcp();

            /// Text
            std::string text;

            /// Suffix array
            std::vector<size_t> array;

            /// Inversed suffix array
            std::vector<size_t> inv;

            /// Array of longest common prefices
            std::vector<size_t> lcp;
        };
    }
}

#endif
