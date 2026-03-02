/*!
 * \file suffix_array.hpp
 * \brief Structure of suffix array.
 */
#ifndef SUFFIX_ARRAY_HPP_
#define SUFFIX_ARRAY_HPP_

#include <cstdlib>
#include <algorithm>
#include <exception>
#include <limits>
#include <map>
#include <queue>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

namespace algolib::text
{
    class suffix_array
    {
    public:
        explicit suffix_array(const std::string & text) : size_{text.size()}, text_{text}
        {
            init_array();
            init_inv();
            init_lcp();
        }

        explicit suffix_array(const char * text) : suffix_array(std::string(text))
        {
        }

        ~suffix_array() = default;
        suffix_array(const suffix_array &) = default;
        suffix_array(suffix_array &&) = default;
        suffix_array & operator=(const suffix_array &) = default;
        suffix_array & operator=(suffix_array &&) = default;

        std::string text() const
        {
            return text_;
        }

        /*!
         * \brief Gets the length of this suffix array.
         * \return the length of suffix array
         */
        size_t size() const
        {
            return size_;
        }

        /*!
         * \brief Gets the text suffix at given index.
         * \param i the index in suffix array
         * \return the text suffix at the index
         */
        std::string at(size_t i) const;

        /*!
         * \brief Gets the text suffix at given index.
         * \param i the index in suffix array
         * \return the text suffix at the index
         */
        std::string operator[](size_t i) const;

        /*!
         * \brief Searches for suffix in text for given index in this suffix array.
         * \param index the index in suffix array
         * \return the index in text where suffix begins
         */
        size_t index_at(size_t index) const;

        /*!
         * \brief Searches for index in this suffix array for given text suffix.
         * \param index the index in text where suffix starts
         * \return the index in suffix array
         */
        size_t index_of(size_t index) const;

        /*!
         * \brief Computes length of longest common prefix of given suffixes.
         * \param index1 the index in text where the first suffix begins
         * \param index2 the index in text where the second suffix begins
         * \return the length of longest common prefix
         */
        size_t lcp(size_t index1, size_t index2) const;

    private:
        void init_array();
        void init_inv();
        void init_lcp();
        std::vector<size_t> create_array(const std::vector<size_t> & t);
        std::vector<size_t> merge(const std::vector<size_t> & t0,
                const std::vector<size_t> & sa0,
                const std::vector<size_t> & tn12,
                const std::vector<size_t> & sa12);
        void sort_indices(
                std::vector<size_t> & indices, const std::vector<size_t> & values, size_t shift);
        size_t get_elem(const std::vector<size_t> & v, size_t i);

        size_t size_;
        std::string text_;
        std::vector<size_t> suf_arr;
        std::vector<size_t> inv_arr;
        std::vector<size_t> lcp_arr;
    };
}

#endif
