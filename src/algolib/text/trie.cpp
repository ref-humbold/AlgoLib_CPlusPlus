/*!
 * \file trie.cpp
 * \brief Structure of trie tree
 */
#include "algolib/text/trie.hpp"

namespace alte = algolib::text;

#pragma region trie

alte::trie::trie() : tree{new alte::trie::trie_node}
{
}

alte::trie::~trie()
{
    delete tree;
}

alte::trie::trie(const alte::trie & t) : tree{new alte::trie::trie_node(*t.tree)}, size_{t.size_}
{
}

alte::trie::trie(alte::trie && t) noexcept : tree{nullptr}, size_{std::move(t.size_)}
{
    std::swap(tree, t.tree);
}

alte::trie & alte::trie::operator=(const alte::trie & t)
{
    node_ptr old_tree = tree;

    tree = new trie_node(*t.tree);
    size_ = t.size_;
    delete old_tree;
    return *this;
}

alte::trie & alte::trie::operator=(alte::trie && t) noexcept
{
    std::swap(tree, t.tree);
    std::swap(size_, t.size_);
    return *this;
}

bool alte::trie::empty() const
{
    return tree->empty();
}

bool alte::trie::find(const std::string & text) const
{
    node_ptr node = tree;

    for(auto && character : text)
    {
        node = node->at(character);

        if(node == nullptr)
            return false;
    }

    return node->terminus;
}

void alte::trie::insert(const std::string & text)
{
    node_ptr node = tree;

    for(auto && character : text)
    {
        node_ptr new_node = new trie_node;
        bool inserted = node->insert(character, new_node);

        if(!inserted)
            delete new_node;

        node = node->at(character);
    }

    if(!node->terminus)
    {
        size_++;
        node->terminus = true;
    }
}

void alte::trie::erase(const std::string & text)
{
    if(text.length() > 0)
        remove_node(text, tree, 0);
}

bool alte::trie::remove_node(const std::string & text, alte::trie::node_ptr node, size_t i)
{
    if(i == text.length() && node->terminus)
    {
        size_--;
        node->terminus = false;
    }
    else if(i < text.length())
    {
        node_ptr next_node = node->at(text.at(i));

        if(next_node != nullptr && remove_node(text, next_node, i + 1))
            node->erase(text.at(i));
    }

    return !node->terminus && node->empty();
}

#pragma endregion
#pragma region trie_node

alte::trie::trie_node::~trie_node()
{
    for(auto && p : children)
        delete p.second;
}

alte::trie::trie_node::trie_node(const alte::trie::trie_node & node) : terminus{node.terminus}
{
    for(auto && p : node.children)
        children.emplace(p.first, new trie_node(*p.second));
}

typename alte::trie::trie_node & alte::trie::trie_node::operator=(const trie::trie_node & node)
{
    std::unordered_map<char, node_ptr> old_children = children;

    children = node.children;
    terminus = node.terminus;

    for(auto && p : old_children)
        delete p.second;

    return *this;
}

void alte::trie::trie_node::erase(char character)
{
    node_ptr child = at(character);

    delete child;
    children.erase(character);
}

#pragma endregion
