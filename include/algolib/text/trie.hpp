/*!
 * \file trie.hpp
 * \brief Structure of trie tree
 */
#ifndef TRIE_HPP_
#define TRIE_HPP_

#include <cstdlib>
#include <exception>
#include <initializer_list>
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
        trie();

        trie(std::initializer_list<std::string> il) : trie()
        {
            for(auto && element : il)
                insert(element);
        }

        ~trie();
        trie(const trie & t);
        trie(trie && t) noexcept;
        trie & operator=(const trie & t);
        trie & operator=(trie && t) noexcept;

        size_t size() const
        {
            return size_;
        }

        bool empty() const;
        bool find(const std::string & text) const;
        void insert(const std::string & text);
        void erase(const std::string & text);

    private:
        bool remove_node(const std::string & text, node_ptr node, size_t i);

        node_ptr tree;
        size_t size_ = 0;
    };

#pragma endregion
#pragma region trie_node

    class trie::trie_node
    {
    public:
        trie_node() = default;
        ~trie_node();
        trie_node(const trie_node & node);
        trie_node(trie_node &&) = delete;
        trie_node & operator=(const trie_node & node);
        trie_node & operator=(trie_node &&) = delete;

        bool empty()
        {
            return children.empty();
        }

        node_ptr at(char character) const
        try
        {
            return children.at(character);
        }
        catch(const std::out_of_range &)
        {
            return nullptr;
        }

        bool insert(char character, node_ptr node)
        {
            auto p = children.emplace(character, node);

            return p.second;
        }

        void erase(char character);

        bool terminus = false;

    private:
        std::unordered_map<char, node_ptr> children;
    };

#pragma endregion
}

#endif