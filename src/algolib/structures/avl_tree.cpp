// DRZEWO AVL
#include <cstdlib>
#include <cmath>
#include <algorithm>

#include "avl_tree.hpp"

template<typename E>
algolib::avl_tree<E>::avl_tree(std::initializer_list<E> init_list) :
    tree{nullptr},
    elems{init_list.size()}
{
    for(auto i : init_list)
        insert(i);
}

template<typename E>
algolib::avl_tree<E> & algolib::avl_tree<E>::operator=(const algolib::avl_tree<E> & avl)
{
    avl_node * new_tree = new avl_node(*avl.tree);

    delete this->tree;
    this->tree = new_tree;
    this->elems = avl.elems;

    return *this;
}

template<typename E>
algolib::avl_tree<E> & algolib::avl_tree<E>::operator=(algolib::avl_tree<E> && avl)
{
    std::swap(this->tree, avl.tree);
    std::swap(this->elems, avl.elems);

    return *this;
}

template<typename E>
typename algolib::avl_tree<E>::iterator algolib::avl_tree<E>::begin()
{
    return iterator( tree->minimum() );
}

template<typename E>
typename algolib::avl_tree<E>::iterator algolib::avl_tree<E>::end()
{
    return iterator(nullptr);
}

template<typename E>
typename algolib::avl_tree<E>::reverse_iterator algolib::avl_tree<E>::rbegin()
{
    return reverse_iterator( tree->maximum() );
}

template<typename E>
typename algolib::avl_tree<E>::reverse_iterator algolib::avl_tree<E>::rend()
{
    return reverse_iterator(nullptr);
}

template<typename E>
typename algolib::avl_tree<E>::iterator algolib::avl_tree<E>::find(const E & element) const
{
    if(tree == nullptr)
        return end();

    algolib::avl_tree<E>::avl_node * node_parent = find_node_parent(element);

    if(node_parent == nullptr)
        return iterator(tree);

    algolib::avl_tree<E>::avl_node * the_node = node_parent->get_subtree(element);

    if(the_node == nullptr)
        return end();

    return iterator(the_node);
}

template<typename E>
std::pair<typename algolib::avl_tree<E>::iterator, bool> algolib::avl_tree<E>::insert(const E & element)
{
    algolib::avl_tree<E>::avl_node * node_parent = find_node_parent(element);
    algolib::avl_tree<E>::avl_node * the_node = node_parent == nullptr ? tree : node_parent->get_subtree(element);

    if(the_node != nullptr)
        return std::make_pair(iterator(the_node), false);

    algolib::avl_tree<E>::avl_node * new_node = new algolib::avl_tree<E>::avl_node(element);

    if(node_parent != nullptr)
    {
        if(element > node_parent->element)
            node_parent->set_right(new_node);
        else
            node_parent->set_left(new_node);

        rebalance(node_parent);
    }
    else
        tree = new_node;

    ++elems;

    return std::make_pair(iterator(new_node), true);
}

template<typename E>
void algolib::avl_tree<E>::erase(const E & element)
{
    algolib::avl_tree<E>::avl_node * node_parent = find_node_parent(element);
    algolib::avl_tree<E>::avl_node * the_node = node_parent == nullptr ? tree : node_parent->get_subtree(element);

    if(the_node == nullptr)
        return;

    if(node_parent == nullptr)
        delete_root(the_node);
    else
        delete_node(the_node);
}

template<typename E>
void algolib::avl_tree<E>::clear()
{
    delete tree;
    tree = nullptr;
    elems = 0;
}

template<typename E>
typename algolib::avl_tree<E>::avl_node * algolib::avl_tree<E>::find_node_parent(const E & element) const
{
    typename algolib::avl_tree<E>::avl_node * tree_iter = tree;
    typename algolib::avl_tree<E>::avl_node * iter_parent = nullptr;

    while(tree_iter != nullptr)
        if(tree_iter->element == element)
            break;
        else
        {
            iter_parent = tree_iter;
            tree_iter = tree_iter->get_subtree(element);
        }

    return iter_parent;
}

template<typename E>
void algolib::avl_tree<E>::delete_root(algolib::avl_tree<E>::avl_node * root)
{
    if(root->get_left() != nullptr && root->get_right() != nullptr)
        delete_node(root);
    else if(root->get_left() != nullptr && root->get_right() == nullptr)
    {
        swap(root->get_left()->element, root->element);
        root->get_left()->parent = nullptr;
        root->set_left(nullptr);
        --elems;
        delete root->get_left();
    }
    else if(root->get_left() == nullptr && root->get_right() != nullptr)
    {
        swap(root->get_right()->element, root->element);
        root->get_right()->parent = nullptr;
        root->set_right(nullptr);
        --elems;
        delete root->get_right();
    }
    else
        clear();
}

template<typename E>
void algolib::avl_tree<E>::delete_node(algolib::avl_tree<E>::avl_node * node)
{
    if(node->get_left() != nullptr && node->get_right() != nullptr)
    {
        algolib::avl_tree<E>::avl_node * succ = node->successor();

        swap(succ->element, node->element);
        delete_node(succ);
    }
    else
    {
        algolib::avl_tree<E>::avl_node * son = node->getLeft() != nullptr ? node->getLeft() : node->getRight();
        algolib::avl_tree<E>::avl_node * node_parent = node->parent;

        replace_subtree(node, son);
        rebalance(node_parent);
        --elems;
        delete node;
    }
}

template<typename E>
void algolib::avl_tree<E>::replace_subtree(algolib::avl_tree<E>::avl_node * node, algolib::avl_tree<E>::avl_node * root)
{
    if(node->parent != nullptr)
    {
        if(node->is_left_son())
            node->parent->set_left(root);
        else
            node->parent->set_right(root);

        node->parent = nullptr;
    }
}

template<typename E>
void algolib::avl_tree<E>::rotate(algolib::avl_tree<E>::avl_node * node)
{
    algolib::avl_tree<E>::avl_node * node_parent = node->parent;

    replace_subtree(node_parent, node);

    if(node->is_left_son())
    {
        node_parent->set_right(node->get_left());
        node->set_left(node_parent);
    }
    else if(node->is_right_son())
    {
        node_parent->set_left(node->get_right());
        node->set_right(node_parent);
    }
}

template<typename E>
void algolib::avl_tree<E>::rebalance(algolib::avl_tree<E>::avl_node * node)
{
    node->count_height();

    int new_balance = node->get_balance();

    while(node != nullptr && node->parent != nullptr)
    {
        if(new_balance >= 2)
        {
            if(node->getLeft()->get_balance() > 0)
                rotate(node->getLeft());
            else if(node->getLeft()->get_balance() < 0)
            {
                rotate(node->getLeft()->getRight());
                rotate(node->getLeft());
            }
        }
        else if(new_balance <= -2)
        {
            if(node->getRight()->get_balance() < 0)
                rotate(node->getRight());
            else if(node->getRight()->get_balance() > 0)
            {
                rotate(node->getRight()->getLeft());
                rotate(node->getRight());
            }
        }

        node = node->parent;
    }
}


template<typename E>
algolib::avl_tree<E>::avl_node::~avl_node()
{
    if(parent != nullptr)
    {
        if(is_left_son())
            parent->left = nullptr;
        else
            parent->right = nullptr;
    }

    delete left;
    delete right;
}

template<typename E>
typename algolib::avl_tree<E>::avl_node & algolib::avl_tree<E>::avl_node::operator=(const algolib::avl_tree<E>::avl_node & node)
{
    algolib::avl_tree<E>::avl_node * new_left = new avl_node(*node.left);
    algolib::avl_tree<E>::avl_node * new_right = new avl_node(*node.right);

    this->height = node.height;
    this->element = node.element;
    delete this->left;
    delete this->right;
    this->set_left(new_left);
    this->set_right(new_right);

    return *this;
}

template<typename E>
typename algolib::avl_tree<E>::avl_node & algolib::avl_tree<E>::avl_node::operator=(algolib::avl_tree<E>::avl_node && node)
{
    std::swap(this->height, node.height);
    std::swap(this->element, node.element);
    std::swap(this->left, node.left);
    std::swap(this->right, node.right);
    this->left->parent = this;
    this->right->parent = this;

    return *this;
}

template<typename E>
void algolib::avl_tree<E>::avl_node::count_height()
{
    int left_height = left == nullptr ? -1 : left->height;
    int right_height = right == nullptr ? -1 : right->height;

    height = std::max(left_height, right_height)+1;
}

template<typename E>
typename algolib::avl_tree<E>::avl_node * algolib::avl_tree<E>::avl_node::get_subtree(const E & element)
{
    if(element == this->element)
        return this;
    else if(element < this->element)
        return left;
    else
        return right;
}

template<typename E>
typename algolib::avl_tree<E>::avl_node * algolib::avl_tree<E>::avl_node::successor()
{
    algolib::avl_tree<E>::avl_node * succ = this;

    if(right != nullptr)
        return right->minimum();

    while(succ != nullptr && succ->element <= this->element)
        succ = succ->parent;

    return succ;
}

template<typename E>
typename algolib::avl_tree<E>::avl_node * algolib::avl_tree<E>::avl_node::minimum()
{
    algolib::avl_tree<E>::avl_node * tree_iter = this;

    while(tree_iter != nullptr && tree_iter->left != nullptr)
        tree_iter = tree_iter->left;

    return tree_iter;
}

template<typename E>
typename algolib::avl_tree<E>::avl_node * algolib::avl_tree<E>::avl_node::maximum()
{
    algolib::avl_tree<E>::avl_node * tree_iter = this;

    while(tree_iter != nullptr && tree_iter->right != nullptr)
        tree_iter = tree_iter->right;

    return tree_iter;
}

template<typename E>
typename algolib::avl_tree<E>::avl_node * algolib::avl_tree<E>::avl_node::predecessor()
{
    algolib::avl_tree<E>::avl_node * pred = this->parent;

    if(left != nullptr)
        return left->maximum();

    while(pred != nullptr && pred->element >= this->element)
        pred = pred->parent;

    return pred;
}


template<typename E>
E & algolib::avl_tree<E>::iterator::operator *() const
{
    return current_node->element;
}

template<typename E>
typename algolib::avl_tree<E>::iterator & algolib::avl_tree<E>::iterator::operator ++()
{
    if(current_node != nullptr)
        current_node = current_node->successor();

    return *this;
}

template<typename E>
typename algolib::avl_tree<E>::iterator algolib::avl_tree<E>::iterator::operator ++(int i)
{
    algolib::avl_tree<E>::iterator result = *this;

    if(current_node != nullptr)
        current_node = current_node->successor();

    return result;
}

template<typename E>
typename algolib::avl_tree<E>::iterator & algolib::avl_tree<E>::iterator::operator --()
{
    if(current_node != nullptr)
        current_node = current_node->predecessor();

    return *this;
}

template<typename E>
typename algolib::avl_tree<E>::iterator algolib::avl_tree<E>::iterator::operator --(int i)
{
    algolib::avl_tree<E>::iterator result = *this;

    if(current_node != nullptr)
        current_node = current_node->predecessor();

    return result;
}

template<typename E>
bool algolib::avl_tree<E>::iterator::operator==(const algolib::avl_tree<E>::iterator & it) const
{
    return this->current_node == it.current_node;
}

template<typename E>
bool algolib::avl_tree<E>::iterator::operator !=(const algolib::avl_tree<E>::iterator & it) const
{
    return this->current_node != it.current_node;
}


template<typename E>
E & algolib::avl_tree<E>::reverse_iterator::operator *() const
{
    return current_node->element;
}

template<typename E>
typename algolib::avl_tree<E>::reverse_iterator & algolib::avl_tree<E>::reverse_iterator::operator ++()
{
    if(current_node != nullptr)
        current_node = current_node->predecessor();

    return *this;
}

template<typename E>
typename algolib::avl_tree<E>::reverse_iterator algolib::avl_tree<E>::reverse_iterator::operator ++(int i)
{
    algolib::avl_tree<E>::reverse_iterator result = *this;

    if(current_node != nullptr)
        current_node = current_node->predecessor();

    return result;
}

template<typename E>
typename algolib::avl_tree<E>::reverse_iterator & algolib::avl_tree<E>::reverse_iterator::operator --()
{
    if(current_node != nullptr)
        current_node = current_node->successor();

    return *this;
}

template<typename E>
typename algolib::avl_tree<E>::reverse_iterator algolib::avl_tree<E>::reverse_iterator::operator --(int i)
{
    algolib::avl_tree<E>::reverse_iterator result = *this;

    if(current_node != nullptr)
        current_node = current_node->successor();

    return result;
}

template<typename E>
bool algolib::avl_tree<E>::reverse_iterator::operator==(const algolib::avl_tree<E>::reverse_iterator & rev_it) const
{
    return this->current_node == rev_it.current_node;
}

template<typename E>
bool algolib::avl_tree<E>::reverse_iterator::operator !=(const algolib::avl_tree<E>::reverse_iterator & rev_it) const
{
    return this->current_node != rev_it.current_node;
}
