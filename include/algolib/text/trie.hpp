/*!
 * \file trie.hpp
 * \brief Structure of trie tree
 */
#ifndef TRIE_HPP_
#define TRIE_HPP_

#include <cstdlib>
#include <algorithm>
#include <array>
#include <exception>
#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace algolib::text
{
#pragma region trie

    class trie
    {
    private:
        class trie_node;

        using node_ptr = trie_node *;
        using node_uniq_ptr = std::unique_ptr<trie_node>;

    public:
        trie() = default;

        template <typename InputIterator>
        trie(InputIterator first, InputIterator last)
        {
            for(InputIterator it = first; it != last; ++it)
                insert(*it);
        }

        trie(std::initializer_list<std::string> init) : trie(init.begin(), init.end())
        {
        }

        ~trie() = default;
        trie(const trie & t);
        trie(trie && t) noexcept = default;
        trie & operator=(const trie & t);
        trie & operator=(trie && t) noexcept;

        //! \return number of texts in the trie
        size_t size() const
        {
            return size_;
        }

        //! \return \c true if the trie is empty, otherwise \c false
        bool empty() const;

        /*!
         * \brief Checks whether given text is present in the trie.
         * \param text text to be checked
         * \return \c true if the text was found in trie, otherwise \c false
         */
        bool contains(const std::string & text) const;

        /*!
         * \brief Adds a new text to the trie.
         * \param text text to be added
         */
        void insert(const std::string & text);

        /*!
         * \brief Removes given text from the trie if present.
         * \param text text to be removed
         */
        void erase(const std::string & text);

        //! \brief Removes all texts in the trie.
        void clear();

    private:
        // Removes node for a character in text at given index.
        bool remove_node(const std::string & text, node_ptr node, size_t i);

        node_uniq_ptr tree = std::make_unique<trie_node>();
        size_t size_ = 0;
    };

#pragma endregion
#pragma region trie_node

    class trie::trie_node
    {
    public:
        trie_node() = default;
        ~trie_node() = default;
        trie_node(const trie_node & node);
        trie_node(trie_node &&) = default;
        trie_node & operator=(const trie_node & node);
        trie_node & operator=(trie_node &&) = default;

        bool empty() const
        {
            return std::all_of(children.begin(), children.end(),
                               [](auto && child) { return !child; });
        }

        node_ptr at(char character) const
        try
        {
            return children.at(character).get();
        }
        catch(const std::out_of_range &)
        {
            return nullptr;
        }

        void insert(char character, node_uniq_ptr node)
        {
            if(!children[character])
                children[character] = std::move(node);
        }

        void erase(char character)
        {
            children[character].reset(nullptr);
        }

        bool terminus = false;

    private:
        std::array<node_uniq_ptr, 256> children;
    };

#pragma endregion
}

#endif
