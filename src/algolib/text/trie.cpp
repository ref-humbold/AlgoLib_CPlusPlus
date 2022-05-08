/*!
 * \file trie.cpp
 * \brief Structure of trie tree
 */
#include "algolib/text/trie.hpp"

namespace alte = algolib::text;

#pragma region trie

alte::trie::trie(const alte::trie & t) : tree{new alte::trie::trie_node(*t.tree)}, size_{t.size_}
{
}

alte::trie & alte::trie::operator=(const alte::trie & t)
{
    tree.reset(new alte::trie::trie_node(*t.tree));
    size_ = t.size_;
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

bool alte::trie::contains(const std::string & text) const
{
    node_ptr node = tree.get();

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
    node_ptr node = tree.get();

    for(auto && character : text)
    {
        node->insert(character, std::make_unique<trie_node>());
        node = node->at(character);
    }

    if(!node->terminus)
    {
        ++size_;
        node->terminus = true;
    }
}

void alte::trie::erase(const std::string & text)
{
    if(text.length() > 0)
        remove_node(text, tree.get(), 0);
}

void alte::trie::clear()
{
    tree.reset(new trie_node);
    size_ = 0;
}

bool alte::trie::remove_node(const std::string & text, alte::trie::node_ptr node, size_t i)
{
    if(i == text.length() && node->terminus)
    {
        --size_;
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

alte::trie::trie_node::trie_node(const alte::trie::trie_node & node) : terminus{node.terminus}
{
    for(size_t i = 0; i < node.children.size(); ++i)
        if(node.children[i])
            children[i].reset(new trie_node(*node.children[i]));
}

typename alte::trie::trie_node & alte::trie::trie_node::operator=(const trie::trie_node & node)
{
    for(size_t i = 0; i < node.children.size(); ++i)
        if(node.children[i])
            children[i].reset(new trie_node(*node.children[i]));
        else
            children[i].reset(nullptr);

    terminus = node.terminus;
    return *this;
}

#pragma endregion
