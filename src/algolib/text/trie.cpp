/*!
 * \file trie.cpp
 * \brief Structure of trie tree
 */
#include "algolib/text/trie.hpp"

namespace alte = algolib::text;

#pragma region trie

alte::trie::trie() : tree{new alte::trie::trie_node()}
{
}

alte::trie::trie(std::initializer_list<std::string> il) : alte::trie::trie()
{
    for(auto && element : il)
        insert(element);
}

alte::trie::~trie()
{
    delete tree;
}

alte::trie::trie(const alte::trie & t) : tree{new alte::trie::trie_node(*t.tree)}
{
}

alte::trie::trie(alte::trie && t) noexcept
{
    std::swap(tree, t.tree);
}

alte::trie & alte::trie::operator=(const alte::trie & t)
{
    node_ptr old_tree = tree;

    tree = new trie_node(*t.tree);
    delete old_tree;
    return *this;
}

alte::trie & alte::trie::operator=(alte::trie && t) noexcept
{
    std::swap(tree, t.tree);
    return *this;
}

void alte::trie::insert(const std::string & text)
{
    node_ptr node = tree;

    for(auto && character : text)
    {
        node->insert(character, new trie_node);
        node = node->at(character);
    }

    node->terminus = true;
}

bool alte::trie::find(const std::string & text)
{
    node_ptr node = tree;

    for(auto && character : text)
    {
        node = node->at(character);

        if(node == nullptr)
            return false;
    }

    return node->terminus == true;
}

#pragma endregion
#pragma region trie_node

alte::trie::trie_node::trie_node(const alte::trie::trie_node & node) : terminus{node.terminus}
{
    for(auto && p : node.children)
        children.emplace(p.first, new trie_node(*p.second));
}

typename alte::trie::trie_node & alte::trie::trie_node::operator=(const trie::trie_node & node)
{
    std::unordered_map<char, node_ptr> old_children = children;

    terminus = node.terminus;
    children.clear();

    for(auto && p : node.children)
        children.emplace(p.first, new trie_node(*p.second));

    for(auto && p : old_children)
        delete p.second;

    return *this;
}

#pragma endregion
