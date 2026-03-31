/*!
 * \file basic_factors_map.hpp
 * \brief Structure of basic factors map using Karp-Miller-Rosenberg algorithm.
 */
#ifndef BASIC_FACTORS_MAP_HPP_
#define BASIC_FACTORS_MAP_HPP_

#include <cstdlib>
#include <algorithm>
#include <functional>
#include <map>
#include <string>

namespace algolib::text
{
    class basic_factors_map
    {
    private:
        struct extension_code;
        using extend_function_t = std::function<extension_code(size_t, size_t)>;

    public:
        using code_t = std::pair<size_t, size_t>;

        explicit basic_factors_map(const std::string & text) : text_{text}
        {
            create();
        }

        ~basic_factors_map() = default;
        basic_factors_map(const basic_factors_map &) = default;
        basic_factors_map(basic_factors_map &&) = default;
        basic_factors_map & operator=(const basic_factors_map &) = default;
        basic_factors_map & operator=(basic_factors_map &&) = default;

        const std::string & text() const
        {
            return text_;
        }

        /*!
         * \brief Retrieves code of substring denoted by given starting index and length.
         * \param start the starting index, inclusive
         * \param length the length of the substring
         * \return the code of the substring
         */
        code_t code(size_t start, size_t length = std::string::npos) const;

    private:
        static size_t get_max_length(size_t n);
        void create();
        size_t extend(size_t length, size_t code_value, const extend_function_t & func);

        std::string text_;
        std::map<std::pair<size_t, size_t>, size_t> factors;
    };

    struct basic_factors_map::extension_code
    {
        extension_code(size_t prefix_code, size_t suffix_code, size_t index)
            : prefix_code{prefix_code}, suffix_code{suffix_code}, index{index}
        {
        }

        bool operator==(const extension_code & code) const;

        bool operator!=(const extension_code & code) const;

        bool operator<(const extension_code & code) const;

        size_t prefix_code;
        size_t suffix_code;
        size_t index;
    };
}

#endif
