/*!
 * \file trie.hpp
 * \brief Structure of trie tree
 */
#ifndef TRIE_HPP_
#define TRIE_HPP_

#include <cstdlib>
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
        using node_uptr = std::unique_ptr<trie_node>;

    public:
        trie() = default;

        trie(std::initializer_list<std::string> il) : trie()
        {
            for(auto && element : il)
                insert(element);
        }

        ~trie() = default;
        trie(const trie & t);
        trie(trie && t) noexcept = default;

        trie & operator=(const trie & t);

        trie & operator=(trie && t) noexcept
        {
            std::swap(tree, t.tree);
            std::swap(size_, t.size_);
            return *this;
        }

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

        node_uptr tree = std::make_unique<trie_node>();
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

        bool empty()
        {
            return children.empty();
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

        void insert(char character, node_uptr node)
        {
            children.emplace(character, std::move(node));
        }

        void erase(char character)
        {
            children.erase(character);
        }

        bool terminus = false;

    private:
        std::unordered_map<char, node_uptr> children;
    };

#pragma endregion
}

#endif
