/*!
 * \file trie.cpp
 * \brief Structure of trie tree
 */
#include "algolib/text/trie.hpp"

namespace alte = algolib::text;

#pragma region trie

alte::trie::~trie()
{
    if(tree != nullptr)
        delete tree;
}

alte::trie::trie(const alte::trie & t) : tree{new alte::trie::trie_node(*t.tree)}
{
}

alte::trie::trie(alte::trie && t) noexcept
{
    std::swap(this->tree, t.tree);
}

alte::trie & alte::trie::operator=(const alte::trie & t)
{
    node_ptr old_tree = this->tree;

    this->tree = new trie_node(*t.tree);
    delete old_tree;
    return *this;
}

alte::trie & alte::trie::operator=(alte::trie && t) noexcept
{
    std::swap(this->tree, t.tree);
    return *this;
}

void alte::trie::add(const std::string & text)
{
}

#pragma endregion
#pragma region trie_node

alte::trie::trie_node::trie_node(const alte::trie::trie_node & node) : terminus{node.terminus}
{
    for(auto && p : node.children)
        this->children.emplace(p.first, new trie_node(*p.second));
}

typename alte::trie::trie_node & alte::trie::trie_node::operator=(const trie::trie_node & node)
{
    std::unordered_map<char, node_ptr> old_children = this->children;

    this->terminus = node.terminus;
    this->children.clear();

    for(auto && p : node.children)
        this->children.emplace(p.first, new trie_node(*p.second));

    for(auto && p : old_children)
        delete p.second;

    return *this;
}

typename alte::trie::node_ptr alte::trie::trie_node::operator[](char character)
{
    auto it = this->children.find(character);

    return it == this->children.end() ? nullptr : it->second;
}

#pragma endregion
