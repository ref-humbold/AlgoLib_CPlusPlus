/*!
 * \file base_words_map.hpp
 * \brief Structure of base words map using Karp-Miller-Rosenberg algorithm
 */
#ifndef BASE_WORDS_MAP_HPP_
#define BASE_WORDS_MAP_HPP_

#include <cstdlib>
#include <algorithm>
#include <functional>
#include <map>
#include <string>
#include <tuple>

namespace algolib::text
{
    class base_words_map
    {
    private:
        using extend_function_t =
                std::function<std::tuple<size_t, size_t, size_t, size_t>(size_t, size_t)>;

    public:
        using code_t = std::pair<size_t, size_t>;

        explicit base_words_map(const std::string & text) : text_{text}
        {
            create();
        }

        ~base_words_map() = default;
        base_words_map(const base_words_map &) = default;
        base_words_map(base_words_map &&) = default;
        base_words_map & operator=(const base_words_map &) = default;
        base_words_map & operator=(base_words_map &&) = default;

        const std::string & text() const
        {
            return text_;
        }

        /*!
         * \brief Retrieves code of a substring denoted by starting index and length.
         * \param start starting index
         * \param length length of a substring
         * \return the code of the substring
         */
        code_t code(size_t start, size_t length = std::string::npos) const;

    private:
        void create();
        size_t extend(size_t length, size_t code_value, extend_function_t func);
        size_t get_max_length(size_t n) const;

        std::string text_;
        std::map<std::pair<size_t, size_t>, size_t> factors;
    };

}

#endif
