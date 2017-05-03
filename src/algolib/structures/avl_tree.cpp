// DRZEWO AVL
#include "avl_tree.hpp"

namespace alst = algolib::structures;

//
// avl_tree
//

template<typename E>
alst::avl_tree<E>::avl_tree(std::initializer_list<E> init_list) :
    tree{nullptr},
    elems{init_list.size()}
{
    for(auto i : init_list)
        insert(i);
}

template<typename E>
alst::avl_tree<E> & alst::avl_tree<E>::operator =(const alst::avl_tree<E> & avl)
{
    node_pointer temp = this->tree;

    this->tree = new node(*avl.tree);
    this->elems = avl.elems;
    delete temp;

    return *this;
}

template<typename E>
alst::avl_tree<E> & alst::avl_tree<E>::operator =(alst::avl_tree<E> && avl)
{
    std::swap(this->tree, avl.tree);
    std::swap(this->elems, avl.elems);

    return *this;
}

template<typename E>
typename alst::avl_tree<E>::iterator alst::avl_tree<E>::begin() const
{
    return iterator(tree->minimum());
}

template<typename E>
typename alst::avl_tree<E>::iterator alst::avl_tree<E>::end() const
{
    return iterator(nullptr);
}

template<typename E>
typename alst::avl_tree<E>::reverse_iterator alst::avl_tree<E>::rbegin() const
{
    return reverse_iterator(tree->maximum());
}

template<typename E>
typename alst::avl_tree<E>::reverse_iterator alst::avl_tree<E>::rend() const
{
    return reverse_iterator(nullptr);
}

template<typename E>
typename alst::avl_tree<E>::iterator alst::avl_tree<E>::find(const E & element) const
{
    if(tree == nullptr)
        return end();

    alst::avl_tree<E>::node_pointer node_parent = find_node_parent(element);

    if(node_parent == nullptr)
        return iterator(tree);

    alst::avl_tree<E>::node_pointer the_node = node_parent->get_subtree(element);

    if(the_node == nullptr)
        return end();

    return iterator(the_node);
}

template<typename E>
std::pair<typename alst::avl_tree<E>::iterator, bool> alst::avl_tree<E>::insert(const E & element)
{
    alst::avl_tree<E>::node_pointer node_parent = find_node_parent(element);
    alst::avl_tree<E>::node_pointer the_node = node_parent == nullptr ? tree : node_parent->get_subtree(element);

    if(the_node != nullptr)
        return std::make_pair(iterator(the_node), false);

    alst::avl_tree<E>::node_pointer new_node = new node(element);

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
void alst::avl_tree<E>::erase(const E & element)
{
    alst::avl_tree<E>::node_pointer node_parent = find_node_parent(element);
    alst::avl_tree<E>::node_pointer the_node = node_parent == nullptr ? tree : node_parent->get_subtree(element);

    if(the_node == nullptr)
        return;

    if(node_parent == nullptr)
        delete_root(the_node);
    else
        delete_node(the_node);
}

template<typename E>
void alst::avl_tree<E>::clear()
{
    delete tree;
    elems = 0;
}

template<typename E>
typename alst::avl_tree<E>::node_pointer alst::avl_tree<E>::find_node_parent(const E & element) const
{
    typename alst::avl_tree<E>::node_pointer tree_iter = tree;
    typename alst::avl_tree<E>::node_pointer iter_parent = nullptr;

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
void alst::avl_tree<E>::delete_root(alst::avl_tree<E>::node_pointer root)
{
    if(root->get_left() != nullptr && root->get_right() != nullptr)
        delete_node(root);
    else if(root->get_left() != nullptr && root->get_right() == nullptr)
    {
        std::swap(root->get_left()->element, root->element);
        root->get_left()->set_parent(nullptr);
        root->set_left(nullptr);
        --elems;
        root->get_left().reset();
    }
    else if(root->get_left() == nullptr && root->get_right() != nullptr)
    {
        std::swap(root->get_right()->element, root->element);
        root->get_right()->set_parent(nullptr);
        root->set_right(nullptr);
        --elems;
        root->get_right().reset();
    }
    else
        clear();
}

template<typename E>
void alst::avl_tree<E>::delete_node(alst::avl_tree<E>::node_pointer node)
{
    if(node->get_left() != nullptr && node->get_right() != nullptr)
    {
        alst::avl_tree<E>::node_pointer succ = node->successor();

        std::swap(succ->element, node->element);
        delete_node(succ);
    }
    else
    {
        alst::avl_tree<E>::node_pointer son = node->get_left() != nullptr ? node->get_left() : node->get_right();
        alst::avl_tree<E>::node_pointer node_parent = node->get_parent();

        replace_subtree(node, son);
        rebalance(node_parent);
        --elems;
        delete node;
    }
}

template<typename E>
void alst::avl_tree<E>::replace_subtree(alst::avl_tree<E>::node_pointer node, alst::avl_tree<E>::node_pointer root)
{
    if(node->is_root())
    {
        tree = root;
        root->set_parent(nullptr);
    }
    else if(node->is_left_son())
        node->get_parent()->set_left(root);
    else
        node->get_parent()->set_right(root);

    node->set_parent(nullptr);
}

template<typename E>
void alst::avl_tree<E>::rotate(alst::avl_tree<E>::node_pointer node)
{
    if(node->is_root())
        return;

    alst::avl_tree<E>::node_pointer upper_node = node->get_parent();

    if(node->is_left_son())
    {
        upper_node->set_right(node->get_left());
        replace_subtree(upper_node, node);
        node->set_left(upper_node);
    }
    else if(node->is_right_son())
    {
        upper_node->set_left(node->get_right());
        replace_subtree(upper_node, node);
        node->set_right(upper_node);
    }
}

template<typename E>
void alst::avl_tree<E>::rebalance(alst::avl_tree<E>::node_pointer node)
{
    while(node != nullptr)
    {
        node->count_height();

        int new_balance = node->get_balance();

        if(new_balance >= 2)
        {
            if(node->get_left()->get_balance() > 0)
                rotate(node->get_left());
            else if(node->get_left()->get_balance() < 0)
            {
                rotate(node->get_left()->get_right());
                rotate(node->get_left());
            }
        }
        else if(new_balance <= -2)
        {
            if(node->get_right()->get_balance() < 0)
                rotate(node->get_right());
            else if(node->get_right()->get_balance() > 0)
            {
                rotate(node->get_right()->get_left());
                rotate(node->get_right());
            }
        }

        node = node->get_parent();
    }
}

//
// avl_node
//

template<typename E>
alst::avl_tree<E>::avl_node::~avl_node()
{
    if(!is_root())
    {
        if(is_left_son())
            parent->left.reset();
        else
            parent->right.reset();
    }
}

template<typename E>
alst::avl_tree<E>::avl_node::avl_node(const alst::avl_tree<E>::avl_node & node) :
    element{node.element},
    height{node.height}
{
    if(node.left != nullptr)
    {
        left = new avl_node(*node.left);
        left->parent = this;
    }

    if(node.right != nullptr)
    {
        right = new avl_node(*node.right);
        right->parent = this;
    }
}

template<typename E>
typename alst::avl_tree<E>::avl_node & alst::avl_tree<E>::avl_node::operator =(const alst::avl_tree<E>::avl_node & node)
{
    alst::avl_tree<E>::node_pointer new_left = new avl_node(*node.left);
    alst::avl_tree<E>::node_pointer new_right = new avl_node(*node.right);

    this->height = node.height;
    this->element = node.element;
    this->set_left(new_left);
    this->set_right(new_right);

    return *this;
}

template<typename E>
void alst::avl_tree<E>::avl_node::count_height()
{
    int left_height = left == nullptr ? -1 : left->height;
    int right_height = right == nullptr ? -1 : right->height;

    height = std::max(left_height, right_height)+1;
}

template<typename E>
typename alst::avl_tree<E>::node_pointer alst::avl_tree<E>::avl_node::get_subtree(const E & element)
{
    if(element == this->element)
        return this;
    else if(element < this->element)
        return left;
    else
        return right;
}

template<typename E>
typename alst::avl_tree<E>::node_pointer alst::avl_tree<E>::avl_node::minimum()
{
    alst::avl_tree<E>::node_pointer tree_iter = this;

    while(tree_iter != nullptr && tree_iter->left != nullptr)
        tree_iter = tree_iter->left;

    return tree_iter;
}

template<typename E>
typename alst::avl_tree<E>::node_pointer alst::avl_tree<E>::avl_node::maximum()
{
    alst::avl_tree<E>::node_pointer tree_iter = this;

    while(tree_iter != nullptr && tree_iter->right != nullptr)
        tree_iter = tree_iter->right;

    return tree_iter;
}

template<typename E>
typename alst::avl_tree<E>::node_pointer alst::avl_tree<E>::avl_node::successor()
{
    alst::avl_tree<E>::node_pointer succ = this;

    if(right != nullptr)
        return right->minimum();

    while(succ != nullptr && succ->element <= this->element)
        succ = succ->get_parent();

    return succ;
}

template<typename E>
typename alst::avl_tree<E>::node_pointer alst::avl_tree<E>::avl_node::predecessor()
{
    alst::avl_tree<E>::node_pointer pred = this->get_parent();

    if(left != nullptr)
        return left->maximum();

    while(pred != nullptr && pred->element >= this->element)
        pred = pred->get_parent();

    return pred;
}

//
// avl_iterator
//

template<typename E>
E & alst::avl_tree<E>::avl_iterator::operator *() const
{
    return current_node->element;
}

template<typename E>
typename alst::avl_tree<E>::avl_iterator & alst::avl_tree<E>::avl_iterator::operator ++()
{
    if(current_node != nullptr)
        current_node = current_node->successor();

    return *this;
}

template<typename E>
typename alst::avl_tree<E>::avl_iterator alst::avl_tree<E>::avl_iterator::operator ++(int i)
{
    alst::avl_tree<E>::avl_iterator result = *this;

    if(current_node != nullptr)
        current_node = current_node->successor();

    return result;
}

template<typename E>
typename alst::avl_tree<E>::avl_iterator & alst::avl_tree<E>::avl_iterator::operator --()
{
    if(current_node != nullptr)
        current_node = current_node->predecessor();

    return *this;
}

template<typename E>
typename alst::avl_tree<E>::avl_iterator alst::avl_tree<E>::avl_iterator::operator --(int i)
{
    alst::avl_tree<E>::avl_iterator result = *this;

    if(current_node != nullptr)
        current_node = current_node->predecessor();

    return result;
}

template<typename E>
bool alst::avl_tree<E>::avl_iterator::operator ==(const alst::avl_tree<E>::avl_iterator & it) const
{
    return this->current_node == it.current_node;
}

template<typename E>
bool alst::avl_tree<E>::avl_iterator::operator !=(const alst::avl_tree<E>::avl_iterator & it) const
{
    return this->current_node != it.current_node;
}

//
// avl_rev_iterator
//

template<typename E>
E & alst::avl_tree<E>::avl_rev_iterator::operator *() const
{
    return current_node->element;
}

template<typename E>
typename alst::avl_tree<E>::avl_rev_iterator & alst::avl_tree<E>::avl_rev_iterator::operator ++()
{
    if(current_node != nullptr)
        current_node = current_node->predecessor();

    return *this;
}

template<typename E>
typename alst::avl_tree<E>::avl_rev_iterator alst::avl_tree<E>::avl_rev_iterator::operator ++(int i)
{
    alst::avl_tree<E>::avl_rev_iterator result = *this;

    if(current_node != nullptr)
        current_node = current_node->predecessor();

    return result;
}

template<typename E>
typename alst::avl_tree<E>::avl_rev_iterator & alst::avl_tree<E>::avl_rev_iterator::operator --()
{
    if(current_node != nullptr)
        current_node = current_node->successor();

    return *this;
}

template<typename E>
typename alst::avl_tree<E>::avl_rev_iterator alst::avl_tree<E>::avl_rev_iterator::operator --(int i)
{
    alst::avl_tree<E>::avl_rev_iterator result = *this;

    if(current_node != nullptr)
        current_node = current_node->successor();

    return result;
}

template<typename E>
bool alst::avl_tree<E>::avl_rev_iterator::operator ==(const alst::avl_tree<E>::avl_rev_iterator & rev_it) const
{
    return this->current_node == rev_it.current_node;
}

template<typename E>
bool alst::avl_tree<E>::avl_rev_iterator::operator !=(const alst::avl_tree<E>::avl_rev_iterator & rev_it) const
{
    return this->current_node != rev_it.current_node;
}
