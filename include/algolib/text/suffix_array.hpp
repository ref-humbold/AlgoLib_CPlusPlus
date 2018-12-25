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
            }

            ~suffix_array() = default;
            suffix_array(const suffix_array &) = default;
            suffix_array & operator=(const suffix_array &) = default;
            suffix_array(suffix_array &&) = default;
            suffix_array & operator=(suffix_array &&) = default;

            std::string get_text()
            {
                return this->text;
            }

            std::string operator[](int i);

        private:
            std::string text;
            std::vector<int> array;
            std::vector<int> inv;
            std::vector<int> lcp;
        };
    }
}

#endif
