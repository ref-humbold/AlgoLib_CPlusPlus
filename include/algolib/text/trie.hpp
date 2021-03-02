/*!
 * \file trie.hpp
 * \brief Structure of trie tree
 */
#ifndef TRIE_HPP_
#define TRIE_HPP_

#include <cstdlib>
#include <exception>
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

    public:
        trie() = default;
        ~trie();
        trie(const trie & t);
        trie(trie && t) noexcept;
        trie & operator=(const trie & t);
        trie & operator=(trie && t) noexcept;

        void insert(const std::string & text);
        bool find(const std::string & text);

    private:
        node_ptr tree = nullptr;
    };

#pragma endregion
#pragma region trie_node

    class trie::trie_node
    {
    public:
        trie_node() = default;

        ~trie_node()
        {
            for(auto && p : children)
                delete p.second;
        }

        trie_node(const trie_node & node);
        trie_node(trie_node &&) = delete;
        trie_node & operator=(const trie_node & node);
        trie_node & operator=(trie_node &&) = delete;

        node_ptr & operator[](char character)
        {
            return children[character];
        }

        node_ptr at(char character) const
        {
            try
            {
                return children.at(character);
            }
            catch(const std::out_of_range &)
            {
                return nullptr;
            }
        }

        bool insert(char character, node_ptr node)
        {
            auto it = children.emplace(character, node);

            return it.second;
        }

        bool terminus = false;

    private:
        std::unordered_map<char, node_ptr> children;
    };

#pragma endregion
}

#endif
