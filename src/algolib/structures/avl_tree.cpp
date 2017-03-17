// DRZEWO AVL
#include <iostream>
#include "avl_tree.hpp"

template<typename E>
algolib::avl_tree<E>::avl_tree(std::initializer_list<E> init_list) :
    tree{node_sptr()},
    elems{init_list.size()}
{
    for(auto i : init_list)
        insert(i);
}

template<typename E>
algolib::avl_tree<E> & algolib::avl_tree<E>::operator=(const algolib::avl_tree<E> & avl)
{
    this->tree = std::make_shared<avl_node>(*avl.tree);
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
typename algolib::avl_tree<E>::iterator algolib::avl_tree<E>::begin() const
{
    return iterator(tree->minimum());
}

template<typename E>
typename algolib::avl_tree<E>::iterator algolib::avl_tree<E>::end() const
{
    return iterator(node_sptr());
}

template<typename E>
typename algolib::avl_tree<E>::reverse_iterator algolib::avl_tree<E>::rbegin() const
{
    return reverse_iterator( tree->maximum() );
}

template<typename E>
typename algolib::avl_tree<E>::reverse_iterator algolib::avl_tree<E>::rend() const
{
    return reverse_iterator(node_sptr());
}

template<typename E>
typename algolib::avl_tree<E>::iterator algolib::avl_tree<E>::find(const E & element) const
{
    if(tree == nullptr)
        return end();

    algolib::avl_tree<E>::node_sptr node_parent = find_node_parent(element);

    if(node_parent == nullptr)
        return iterator(tree);

    algolib::avl_tree<E>::node_sptr the_node = node_parent->get_subtree(element);

    if(the_node == nullptr)
        return end();

    return iterator( std::move(the_node) );
}

template<typename E>
std::pair<typename algolib::avl_tree<E>::iterator, bool> algolib::avl_tree<E>::insert(const E & element)
{
    algolib::avl_tree<E>::node_sptr node_parent = find_node_parent(element);
    algolib::avl_tree<E>::node_sptr the_node = node_parent == nullptr ? tree : node_parent->get_subtree(element);

    if(the_node != nullptr)
        return std::make_pair(iterator(the_node), false);

    algolib::avl_tree<E>::node_sptr new_node = std::make_shared<avl_node>(element);

    if(node_parent != nullptr)
    {
        if(element > node_parent->element)
            node_parent->set_right(new_node);
        else
            node_parent->set_left(new_node);

        rebalance( std::move(node_parent) );
    }
    else
        tree = new_node;

    ++elems;

    return std::make_pair(iterator( std::move(new_node) ), true);
}

template<typename E>
void algolib::avl_tree<E>::erase(const E & element)
{
    algolib::avl_tree<E>::node_sptr node_parent = find_node_parent(element);
    algolib::avl_tree<E>::node_sptr the_node = node_parent == nullptr ? tree : node_parent->get_subtree(element);

    if(the_node == nullptr)
        return;

    if(node_parent == nullptr)
        delete_root( std::move(the_node) );
    else
        delete_node( std::move(the_node) );
}

template<typename E>
void algolib::avl_tree<E>::clear()
{
    tree.reset();
    elems = 0;
}

template<typename E>
typename algolib::avl_tree<E>::node_sptr algolib::avl_tree<E>::find_node_parent(const E & element) const
{
    typename algolib::avl_tree<E>::node_sptr tree_iter = tree;
    typename algolib::avl_tree<E>::node_sptr iter_parent = std::shared_ptr<avl_node>(nullptr);

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
void algolib::avl_tree<E>::delete_root(algolib::avl_tree<E>::node_sptr root)
{
    if(root->get_left() != nullptr && root->get_right() != nullptr)
        delete_node(root);
    else if(root->get_left() != nullptr && root->get_right() == nullptr)
    {
        std::swap(root->get_left()->element, root->element);
        root->get_left()->set_parent(node_wptr());
        root->set_left(nullptr);
        --elems;
        root->get_left().reset();
    }
    else if(root->get_left() == nullptr && root->get_right() != nullptr)
    {
        std::swap(root->get_right()->element, root->element);
        root->get_right()->set_parent(node_wptr());
        root->set_right(nullptr);
        --elems;
        root->get_right().reset();
    }
    else
        clear();
}

template<typename E>
void algolib::avl_tree<E>::delete_node(algolib::avl_tree<E>::node_sptr node)
{
    if(node->get_left() != nullptr && node->get_right() != nullptr)
    {
        algolib::avl_tree<E>::node_sptr succ = node->successor();

        std::swap(succ->element, node->element);
        delete_node(succ);
    }
    else
    {
        algolib::avl_tree<E>::node_sptr son = node->get_left() != nullptr ? node->get_left() : node->get_right();
        algolib::avl_tree<E>::node_sptr node_parent = node->get_parent();

        replace_subtree(node, son);
        rebalance( std::move(node_parent) );
        --elems;
        node.reset();
    }
}

template<typename E>
void algolib::avl_tree<E>::replace_subtree(algolib::avl_tree<E>::node_sptr node, algolib::avl_tree<E>::node_sptr root)
{
    if(node->is_root())
    {
        tree = root;
        root.set_parent(node_wptr());
    }
    else if(node->is_left_son())
        node->get_parent()->set_left(root);
    else
        node->get_parent()->set_right(root);

    node->set_parent(node_wptr());
}

template<typename E>
void algolib::avl_tree<E>::rotate(algolib::avl_tree<E>::node_sptr node)
{
    if(node->is_root())
        return;

    algolib::avl_tree<E>::node_sptr upper_node = node->get_parent();

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
void algolib::avl_tree<E>::rebalance(algolib::avl_tree<E>::node_sptr node)
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


template<typename E>
algolib::avl_tree<E>::avl_node::~avl_node()
{
    if(!is_root())
    {
        if(is_left_son())
            parent.lock()->left.reset();
        else
            parent.lock()->right.reset();
    }
}

template<typename E>
algolib::avl_tree<E>::avl_node::avl_node(const algolib::avl_tree<E>::avl_node & node) :
    std::enable_shared_from_this<avl_node>(),
    element{node.element},
    height{node.height}
{
    if(node.left != nullptr)
    {
        left = std::make_shared<avl_node>(*node.left);
        left->parent = get_this();
    }

    if(node.right != nullptr)
    {
        right = std::make_shared<avl_node>(*node.right);
        right->parent = get_this();
    }
}

template<typename E>
algolib::avl_tree<E>::avl_node::avl_node(algolib::avl_tree<E>::avl_node && node) :
    std::enable_shared_from_this<avl_node>(),
    element{std::move(node.element)},
    height{std::move(node.height)}
{
    std::swap(this->left, node.left);
    std::swap(this->right, node.right);

    if(left != nullptr)
        left->parent = get_this();

    if(right != nullptr)
        right->parent = get_this();
}

template<typename E>
typename algolib::avl_tree<E>::avl_node & algolib::avl_tree<E>::avl_node::operator=(const algolib::avl_tree<E>::avl_node & node)
{
    algolib::avl_tree<E>::node_sptr new_left = std::shared_ptr<avl_node>(*node.left);
    algolib::avl_tree<E>::node_sptr new_right = std::shared_ptr<avl_node>(*node.right);

    this->height = node.height;
    this->element = node.element;
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
    this->left->parent = get_this();
    this->right->parent = get_this();

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
typename algolib::avl_tree<E>::node_sptr algolib::avl_tree<E>::avl_node::get_subtree(const E & element)
{
    if(element == this->element)
        return get_this();
    else if(element < this->element)
        return left;
    else
        return right;
}

template<typename E>
typename algolib::avl_tree<E>::node_sptr algolib::avl_tree<E>::avl_node::minimum()
{
    algolib::avl_tree<E>::node_sptr tree_iter = get_this();

    while(tree_iter != nullptr && tree_iter->left != nullptr)
        tree_iter = tree_iter->left;

    return tree_iter;
}

template<typename E>
typename algolib::avl_tree<E>::node_sptr algolib::avl_tree<E>::avl_node::maximum()
{
    algolib::avl_tree<E>::node_sptr tree_iter = get_this();

    while(tree_iter != nullptr && tree_iter->right != nullptr)
        tree_iter = tree_iter->right;

    return tree_iter;
}

template<typename E>
typename algolib::avl_tree<E>::node_sptr algolib::avl_tree<E>::avl_node::successor()
{
    algolib::avl_tree<E>::node_sptr succ = get_this();

    if(right != nullptr)
        return right->minimum();

    while(succ != nullptr && succ->element <= this->element)
        succ = succ->get_parent();

    return succ;
}

template<typename E>
typename algolib::avl_tree<E>::node_sptr algolib::avl_tree<E>::avl_node::predecessor()
{
    algolib::avl_tree<E>::node_sptr pred = this->get_parent();

    if(left != nullptr)
        return left->maximum();

    while(pred != nullptr && pred->element >= this->element)
        pred = pred->get_parent();

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
