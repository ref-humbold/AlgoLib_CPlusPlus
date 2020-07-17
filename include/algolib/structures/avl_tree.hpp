/*!
 * \file avl_tree.hpp
 * \brief Structure of AVL tree
 */
#ifndef AVL_TREE_HPP_
#define AVL_TREE_HPP_

#include <cstdlib>
#include <cmath>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <initializer_list>
#include <iterator>
#include <functional>

namespace algolib::structures
{
#pragma region avl_tree

    template <typename E, typename Compare = std::less<E>>
    class avl_tree
    {
    private:
        struct avl_node;
        class avl_inner_node;
        class avl_header_node;

        class avl_iterator;
        class avl_const_iterator;

        using node_ptr = avl_node *;
        using inner_ptr = avl_inner_node *;
        using header_ptr = avl_header_node *;

    public:
        using value_type = E;
        using reference = value_type &;
        using const_reference = const value_type &;
        using pointer = value_type *;
        using const_pointer = const value_type *;
        using iterator = avl_iterator;
        using const_iterator = avl_const_iterator;
        using reverse_iterator = std::reverse_iterator<avl_iterator>;
        using const_reverse_iterator = std::reverse_iterator<avl_const_iterator>;
        using difference_type = typename std::iterator_traits<iterator>::difference_type;
        using size_type = size_t;

        explicit avl_tree(const Compare & comparator = Compare()) : comparator{comparator}
        {
        }

        explicit avl_tree(std::initializer_list<value_type> il,
                          const Compare & comparator = Compare())
            : comparator{comparator}
        {
            for(auto && element : il)
                insert(element);
        }

        ~avl_tree()
        {
            delete this->tree;
        }

        avl_tree(const avl_tree & avl)
            : tree{new avl_header_node(*avl.tree)}, count{avl.count}, comparator{avl.comparator}
        {
        }

        avl_tree(avl_tree && avl) noexcept
            : count{std::move(avl.count)}, comparator{std::move(avl.comparator)}
        {
            std::swap(this->tree, avl.tree);
        }

        avl_tree & operator=(const avl_tree & avl);
        avl_tree & operator=(avl_tree && avl) noexcept;

        const_iterator cbegin() const
        {
            return const_iterator(this->get_root()->minimum());
        }

        const_iterator cend() const
        {
            return const_iterator(this->tree);
        }

        const_reverse_iterator crbegin() const
        {
            return const_reverse_iterator(this->cend());
        }

        const_reverse_iterator crend() const
        {
            return const_reverse_iterator(this->cbegin());
        }

        iterator begin()
        {
            return iterator(this->get_root()->minimum());
        }

        const_iterator begin() const
        {
            return this->cbegin();
        }

        iterator end()
        {
            return iterator(this->tree);
        }

        const_iterator end() const
        {
            return this->cend();
        }

        reverse_iterator rbegin()
        {
            return reverse_iterator(this->end());
        }

        const_reverse_iterator rbegin() const
        {
            return this->crbegin();
        }

        reverse_iterator rend()
        {
            return reverse_iterator(this->begin());
        }

        const_reverse_iterator rend() const
        {
            return this->crend();
        }

        size_type size() const
        {
            return this->count;
        }

        bool empty() const
        {
            return this->get_root() == nullptr;
        }

        /*!
             * \brief Checks whether specified value is present in this tree.
             * \param element value to check
             * \return iterator on the element if found, otherwise iterator at the end
             */
        iterator find(const_reference element);

        /*!
             * \brief Checks whether specified value is present in this tree.
             * \param element value to check
             * \return iterator on the element if found, otherwise iterator at the end
             */
        const_iterator find(const_reference element) const;

        /*!
             * \brief Adds a new value to the tree.
             * \param element value to be added
             * \return iterator at the new element and \code true whether insert was successful,
             * otherwise \code false
             */
        std::pair<iterator, bool> insert(const_reference element);

        /*!
             * \brief Removes specified element from the tree if present.
             * \param element value to be removed
             * \return number of element removed
             */
        size_type erase(const_reference element);

        //! \brief Removes all elements in this tree.
        void clear();

    private:
        inner_ptr get_root() const
        {
            return this->tree->get_parent();
        }

        void set_root(inner_ptr node)
        {
            this->tree->set_parent(node);
        }

        bool is_left_child(inner_ptr node)
        {
            return node->get_parent()->get_height() > 0 && node->get_parent()->get_left() == node;
        }

        bool is_right_child(inner_ptr node)
        {
            return node->get_parent()->get_height() > 0 && node->get_parent()->get_right() == node;
        }

        // Determines the subtree where given value might be present:
        // - node if element is in it
        // - left child if element is less than node's element
        // - right child if element is greater than node's element
        inner_ptr search(inner_ptr node, const_reference element) const;

        // Searches for node that satisfies specified predicate with specified value.
        inner_ptr find_node(const_reference element,
                            std::function<bool(inner_ptr, const_reference)> predicate) const;

        // Removes inner node from the tree.
        void delete_node(inner_ptr node);

        // Replaces the subtree rooted in one node with subtree of another node.
        void replace_node(inner_ptr node1, inner_ptr node2);

        // Rotates the node along the edge to its parent.
        void rotate(inner_ptr node);

        // Restores balancing on a path from specified node to the root.
        void balance(node_ptr node);

        // Counts current node balance.
        int count_balance(node_ptr node);

        header_ptr tree = new avl_header_node();  // The tree denoted by its header
        size_type count = 0;  // Number of elements
        Compare comparator;  // Comparator
    };

    template <typename E, typename Compare>
    avl_tree<E, Compare> & avl_tree<E, Compare>::operator=(const avl_tree<E, Compare> & avl)
    {
        header_ptr tree_orig = this->tree;

        this->count = avl.count;
        this->comparator = avl.comparator;
        this->tree = new avl_header_node(*avl.tree);
        delete tree_orig;

        return *this;
    }

    template <typename E, typename Compare>
    avl_tree<E, Compare> & avl_tree<E, Compare>::operator=(avl_tree<E, Compare> && avl) noexcept
    {
        std::swap(this->tree, avl.tree);
        std::swap(this->count, avl.count);
        std::swap(this->comparator, avl.comparator);

        return *this;
    }

    template <typename E, typename Compare>
    typename avl_tree<E, Compare>::iterator avl_tree<E, Compare>::find(const_reference element)
    {
        if(this->empty())
            return this->end();

        std::function<bool(inner_ptr, const_reference)> equal = [this](inner_ptr n,
                                                                       const_reference e) {
            return !comparator(n->element, e) && !comparator(e, n->element);
        };
        node_ptr the_node = this->find_node(element, equal);

        return the_node == nullptr ? this->end() : iterator(the_node);
    }

    template <typename E, typename Compare>
    typename avl_tree<E, Compare>::const_iterator
            avl_tree<E, Compare>::find(const_reference element) const
    {
        if(this->empty())
            return this->cend();

        std::function<bool(inner_ptr, const_reference)> equal = [this](inner_ptr n,
                                                                       const_reference e) {
            return !comparator(n->element, e) && !comparator(e, n->element);
        };
        node_ptr the_node = this->find_node(element, equal);

        return the_node == nullptr ? this->cend() : const_iterator(the_node);
    }

    template <typename E, typename Compare>
    std::pair<typename avl_tree<E, Compare>::iterator, bool>
            avl_tree<E, Compare>::insert(const_reference element)
    {
        std::function<bool(inner_ptr, const_reference)> child_equal = [this](inner_ptr n,
                                                                             const_reference e) {
            inner_ptr child = this->search(n, e);

            return child == nullptr
                   || (!this->comparator(child->element, e)
                       && !this->comparator(e, child->element));
        };
        inner_ptr node_parent = this->find_node(element, child_equal);

        if(node_parent == nullptr)
        {
            auto new_node = new avl_inner_node(element);

            this->set_root(new_node);
            ++this->count;

            return std::make_pair(iterator(new_node), true);
        }

        inner_ptr the_node = this->search(node_parent, element);

        if(the_node != nullptr)
            return std::make_pair(iterator(the_node), false);

        auto new_node = new avl_inner_node(element);

        if(this->comparator(element, node_parent->element))
            node_parent->set_left(new_node);
        else
            node_parent->set_right(new_node);

        this->balance(node_parent);
        ++this->count;

        return std::make_pair(iterator(new_node), true);
    }

    template <typename E, typename Compare>
    typename avl_tree<E, Compare>::size_type avl_tree<E, Compare>::erase(const_reference element)
    {
        std::function<bool(inner_ptr, const_reference)> equal = [this](inner_ptr n,
                                                                       const_reference e) {
            return !this->comparator(n->element, e) && !this->comparator(e, n->element);
        };
        inner_ptr the_node = this->find_node(element, equal);

        if(the_node == nullptr)
            return 0;

        this->delete_node(the_node);

        return 1;
    }

    template <typename E, typename Compare>
    void avl_tree<E, Compare>::clear()
    {
        delete this->get_root();
        this->set_root(nullptr);
        this->count = 0;
    }

    template <typename E, typename Compare>
    typename avl_tree<E, Compare>::inner_ptr
            avl_tree<E, Compare>::search(inner_ptr node, const_reference element) const
    {
        return this->comparator(element, node->element)
                       ? node->get_left()
                       : this->comparator(node->element, element) ? node->get_right() : node;
    }

    template <typename E, typename Compare>
    typename avl_tree<E, Compare>::inner_ptr avl_tree<E, Compare>::find_node(
            const_reference element,
            std::function<bool(inner_ptr, const_reference)> predicate) const
    {
        inner_ptr node = this->get_root();

        while(node != nullptr && !predicate(node, element))
            node = this->search(node, element);

        return node;
    }

    template <typename E, typename Compare>
    void avl_tree<E, Compare>::delete_node(inner_ptr node)
    {
        if(node->get_left() != nullptr && node->get_right() != nullptr)
        {
            inner_ptr succ = node->get_right()->minimum();

            std::swap(succ->element, node->element);
            this->delete_node(succ);
        }
        else
        {
            inner_ptr child = node->get_left() != nullptr ? node->get_left() : node->get_right();

            if(node->get_parent()->get_height() > 0)
            {
                node_ptr node_parent = node->get_parent();

                this->replace_node(node, child);
                this->balance(node_parent);
            }
            else
                this->set_root(child);

            node->set_left(nullptr);
            node->set_right(nullptr);
            --this->count;
            delete node;
        }
    }

    template <typename E, typename Compare>
    void avl_tree<E, Compare>::replace_node(inner_ptr node1, inner_ptr node2)
    {
        if(this->is_left_child(node1))
            node1->get_parent()->set_left(node2);
        else if(this->is_right_child(node1))
            node1->get_parent()->set_right(node2);
        else
            this->set_root(node2);

        node1->set_parent(nullptr);
    }

    template <typename E, typename Compare>
    void avl_tree<E, Compare>::rotate(inner_ptr node)
    {
        if(this->is_right_child(node))
        {
            auto upper_node = static_cast<inner_ptr>(node->get_parent());

            upper_node->set_right(node->get_left());
            this->replace_node(upper_node, node);
            node->set_left(upper_node);
        }
        else if(this->is_left_child(node))
        {
            auto upper_node = static_cast<inner_ptr>(node->get_parent());

            upper_node->set_left(node->get_right());
            this->replace_node(upper_node, node);
            node->set_right(upper_node);
        }
    }

    template <typename E, typename Compare>
    void avl_tree<E, Compare>::balance(node_ptr node)
    {
        while(node->get_height() > 0)
        {
            node->count_height();

            int new_balance = this->count_balance(node);
            auto rnode = static_cast<inner_ptr>(node);

            if(new_balance >= 2)
            {
                if(this->count_balance(node->get_left()) > 0)
                    this->rotate(rnode->get_left());
                else if(this->count_balance(node->get_left()) < 0)
                {
                    this->rotate(rnode->get_left()->get_right());
                    this->rotate(rnode->get_left());
                }
            }
            else if(new_balance <= -2)
            {
                if(this->count_balance(node->get_right()) < 0)
                    this->rotate(rnode->get_right());
                else if(this->count_balance(node->get_right()) > 0)
                {
                    this->rotate(rnode->get_right()->get_left());
                    this->rotate(rnode->get_right());
                }
            }

            node = node->get_parent();
        }
    }

    template <typename E, typename Compare>
    int avl_tree<E, Compare>::count_balance(avl_tree<E, Compare>::node_ptr node)
    {
        int left_height = node->get_left() == nullptr ? 0 : node->get_left()->get_height();
        int right_height = node->get_right() == nullptr ? 0 : node->get_right()->get_height();

        return left_height - right_height;
    }

#pragma endregion
#pragma region avl_node

    template <typename E, typename Compare>
    struct avl_tree<E, Compare>::avl_node
    {
        virtual ~avl_node() = default;

        virtual size_t get_height() = 0;

        virtual node_ptr get_left() = 0;

        virtual void set_left(node_ptr node) = 0;

        virtual node_ptr get_right() = 0;

        virtual void set_right(node_ptr node) = 0;

        virtual node_ptr get_parent() = 0;

        virtual void set_parent(node_ptr node) = 0;

        // Recounts the height of the node.
        virtual void count_height() = 0;

        // Searches in its subtree for the node with minimal value.
        virtual node_ptr minimum() = 0;

        // Searches in its subtree for the node with maximal value.
        virtual node_ptr maximum() = 0;
    };

#pragma endregion
#pragma region avl_inner_node

    template <typename E, typename Compare>
    class avl_tree<E, Compare>::avl_inner_node : public avl_tree<E, Compare>::avl_node
    {
    public:
        explicit avl_inner_node(const_reference elem)
            : avl_tree<E, Compare>::avl_node(),
              element{elem},
              height{1},
              left{nullptr},
              right{nullptr},
              parent{nullptr}
        {
        }

        ~avl_inner_node() override;
        avl_inner_node(const avl_inner_node & node);
        avl_inner_node(avl_inner_node &&) = delete;
        avl_inner_node & operator=(const avl_inner_node & node);
        avl_inner_node & operator=(avl_inner_node &&) = delete;

        size_t get_height() override
        {
            return this->height;
        }

        inner_ptr get_left() override
        {
            return this->left;
        }

        void set_left(node_ptr node) override
        {
            this->do_set_left(node);
        }

        inner_ptr get_right() override
        {
            return this->right;
        }

        void set_right(node_ptr node) override
        {
            this->do_set_right(node);
        }

        node_ptr get_parent() override
        {
            return this->parent;
        }

        void set_parent(node_ptr node) override
        {
            this->parent = node;
        }

        void count_height() override
        {
            this->do_count_height();
        }

        inner_ptr minimum() override
        {
            return this->left == nullptr ? this : this->left->minimum();
        }

        inner_ptr maximum() override
        {
            return this->right == nullptr ? this : this->right->maximum();
        }

        value_type element;  //!< Value in the node.

    private:
        void do_set_left(node_ptr node);
        void do_set_right(node_ptr node);
        void do_count_height();

        int height;
        inner_ptr left;
        inner_ptr right;
        node_ptr parent;
    };

    template <typename E, typename Compare>
    avl_tree<E, Compare>::avl_inner_node::~avl_inner_node()
    {
        delete this->left;
        delete this->right;
    }

    template <typename E, typename Compare>
    avl_tree<E, Compare>::avl_inner_node::avl_inner_node(
            const avl_tree<E, Compare>::avl_inner_node & node)
        : avl_tree<E, Compare>::avl_node(),
          element{node.element},
          height{node.height},
          left{nullptr},
          right{nullptr},
          parent{nullptr}
    {
        if(node.left != nullptr)
            this->do_set_left(new avl_inner_node(*node.left));

        if(node.right != nullptr)
            this->do_set_right(new avl_inner_node(*node.right));
    }

    template <typename E, typename Compare>
    typename avl_tree<E, Compare>::avl_inner_node & avl_tree<E, Compare>::avl_inner_node::operator=(
            const avl_tree<E, Compare>::avl_inner_node & node)
    {
        node_ptr left_orig = this->left;
        node_ptr right_orig = this->right;

        this->element = node.element;
        this->height = node.height;
        this->set_left(node.left == nullptr ? nullptr : new avl_inner_node(*node.left));
        this->set_right(node.right == nullptr ? nullptr : new avl_inner_node(*node.right));
        delete left_orig;
        delete right_orig;

        return *this;
    }

    template <typename E, typename Compare>
    void avl_tree<E, Compare>::avl_inner_node::do_set_left(node_ptr node)
    {
        this->left = static_cast<inner_ptr>(node);

        if(this->left != nullptr)
            this->left->set_parent(this);

        this->do_count_height();
    }

    template <typename E, typename Compare>
    void avl_tree<E, Compare>::avl_inner_node::do_set_right(node_ptr node)
    {
        this->right = static_cast<inner_ptr>(node);

        if(this->right != nullptr)
            this->right->set_parent(this);

        this->do_count_height();
    }

    template <typename E, typename Compare>
    void avl_tree<E, Compare>::avl_inner_node::do_count_height()
    {
        int left_height = this->left == nullptr ? 0 : this->left->get_height();
        int right_height = this->right == nullptr ? 0 : this->right->get_height();

        this->height = std::max(left_height, right_height) + 1;
    }

#pragma endregion
#pragma region avl_header_node

    template <typename E, typename Compare>
    class avl_tree<E, Compare>::avl_header_node : public avl_tree<E, Compare>::avl_node
    {
    public:
        avl_header_node() : avl_tree<E, Compare>::avl_node(), inner{nullptr}
        {
        }

        ~avl_header_node() override
        {
            delete this->inner;
        }

        avl_header_node(const avl_header_node & node)
            : avl_tree<E, Compare>::avl_node(), inner{nullptr}
        {
            if(node.inner != nullptr)
                this->do_set_parent(new avl_inner_node(*node.inner));
        }

        avl_header_node(avl_header_node && node) = delete;
        avl_header_node & operator=(const avl_header_node & node);
        avl_header_node & operator=(avl_header_node && node) = delete;

        size_t get_height() override
        {
            return 0;
        }

        inner_ptr get_left() override
        {
            return nullptr;
        }

        void set_left(node_ptr) override
        {
        }

        inner_ptr get_right() override
        {
            return nullptr;
        }

        void set_right(node_ptr) override
        {
        }

        inner_ptr get_parent() override
        {
            return this->inner;
        }

        void set_parent(node_ptr node) override
        {
            this->do_set_parent(node);
        }

        void count_height() override
        {
        }

        node_ptr minimum() override
        {
            return this;
        }

        node_ptr maximum() override
        {
            return this;
        }

    private:
        void do_set_parent(node_ptr node)
        {
            this->inner = static_cast<inner_ptr>(node);

            if(this->inner != nullptr)
                this->inner->set_parent(this);
        }

        inner_ptr inner;
    };

    template <typename E, typename Compare>
    typename avl_tree<E, Compare>::avl_header_node &
            avl_tree<E, Compare>::avl_header_node::operator=(
                    const avl_tree<E, Compare>::avl_header_node & node)
    {
        node_ptr inner_orig = this->inner;

        this->set_parent(node.inner == nullptr ? nullptr : new avl_inner_node(*node.inner));
        delete inner_orig;

        return *this;
    }

#pragma endregion
#pragma region avl_iterator

    template <typename E, typename Compare>
    class avl_tree<E, Compare>::avl_iterator
    {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = E;
        using reference = value_type &;
        using pointer = value_type *;
        using difference_type = ptrdiff_t;

        explicit avl_iterator(node_ptr node) : current_node{node}
        {
        }

        ~avl_iterator() = default;

        avl_iterator(const avl_iterator & it) : current_node{it.current_node}
        {
        }

        avl_iterator(avl_iterator && it) noexcept : current_node{it.current_node}
        {
        }

        avl_iterator & operator=(const avl_iterator & it)
        {
            this->current_node = it.current_node;

            return *this;
        }

        avl_iterator & operator=(avl_iterator && it) noexcept
        {
            this->current_node = it.current_node;

            return *this;
        }

        reference operator*() const
        {
            return static_cast<inner_ptr>(this->current_node)->element;
        }

        pointer operator->() const
        {
            return &(operator*());
        }

        avl_iterator & operator++();

        avl_iterator operator++(int) &;

        avl_iterator & operator--();

        avl_iterator operator--(int) &;

        bool operator==(const avl_iterator & it) const;

        bool operator!=(const avl_iterator & it) const;

    private:
        node_ptr current_node;
    };

    template <typename E, typename Compare>
    typename avl_tree<E, Compare>::avl_iterator & avl_tree<E, Compare>::avl_iterator::operator++()
    {
        if(this->current_node->get_height() > 0)
        {
            if(this->current_node->get_right() != nullptr)
                this->current_node = this->current_node->get_right()->minimum();
            else
            {
                while(this->current_node->get_parent()->get_height() > 0
                      && this->current_node->get_parent()->get_left() != this->current_node)
                    this->current_node = this->current_node->get_parent();

                this->current_node = this->current_node->get_parent();
            }
        }

        return *this;
    }

    template <typename E, typename Compare>
    typename avl_tree<E, Compare>::avl_iterator
            avl_tree<E, Compare>::avl_iterator::operator++(int) &
    {
        avl_tree<E, Compare>::avl_const_iterator result = *this;

        ++(*this);
        return result;
    }

    template <typename E, typename Compare>
    typename avl_tree<E, Compare>::avl_iterator & avl_tree<E, Compare>::avl_iterator::operator--()
    {
        if(this->current_node->get_height() > 0)
        {
            if(this->current_node->get_left() != nullptr)
                this->current_node = this->current_node->get_left()->maximum();
            else
            {
                while(this->current_node->get_parent()->get_height() > 0
                      && this->current_node->get_parent()->get_right() != this->current_node)
                    this->current_node = this->current_node->get_parent();

                this->current_node = this->current_node->get_parent();
            }
        }
        else
            this->current_node = this->current_node->get_parent()->maximum();

        return *this;
    }

    template <typename E, typename Compare>
    typename avl_tree<E, Compare>::avl_iterator
            avl_tree<E, Compare>::avl_iterator::operator--(int) &
    {
        avl_tree<E, Compare>::avl_const_iterator result = *this;

        --(*this);
        return result;
    }

    template <typename E, typename Compare>
    bool avl_tree<E, Compare>::avl_iterator::operator==(
            const avl_tree<E, Compare>::avl_iterator & it) const
    {
        return this->current_node == it.current_node;
    }

    template <typename E, typename Compare>
    bool avl_tree<E, Compare>::avl_iterator::operator!=(
            const avl_tree<E, Compare>::avl_iterator & it) const
    {
        return this->current_node != it.current_node;
    }

#pragma endregion
#pragma region avl_const_iterator

    template <typename E, typename Compare>
    class avl_tree<E, Compare>::avl_const_iterator
    {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = E;
        using reference = const value_type &;
        using pointer = const value_type *;
        using difference_type = ptrdiff_t;

        explicit avl_const_iterator(node_ptr node) : current_node{node}
        {
        }

        ~avl_const_iterator() = default;

        explicit avl_const_iterator(const avl_iterator & it) : current_node{it.current_node}
        {
        }

        avl_const_iterator(const avl_const_iterator & it) : current_node{it.current_node}
        {
        }

        avl_const_iterator(avl_const_iterator && it) noexcept : current_node{it.current_node}
        {
        }

        avl_const_iterator & operator=(const avl_const_iterator & it)
        {
            this->current_node = it.current_node;
            return *this;
        }

        avl_const_iterator & operator=(avl_const_iterator && it) noexcept
        {
            this->current_node = it.current_node;
            return *this;
        }

        reference operator*() const
        {
            return static_cast<inner_ptr>(this->current_node)->element;
        }

        pointer operator->() const
        {
            return &(operator*());
        }

        avl_const_iterator & operator++();

        avl_const_iterator operator++(int) &;

        avl_const_iterator & operator--();

        avl_const_iterator operator--(int) &;

        bool operator==(const avl_const_iterator & it) const;

        bool operator!=(const avl_const_iterator & it) const;

    private:
        node_ptr current_node;
    };

    template <typename E, typename Compare>
    typename avl_tree<E, Compare>::avl_const_iterator &
            avl_tree<E, Compare>::avl_const_iterator::operator++()
    {
        if(this->current_node->get_height() > 0)
        {
            if(this->current_node->get_right() != nullptr)
                this->current_node = this->current_node->get_right()->minimum();
            else
            {
                while(this->current_node->get_parent()->get_height() > 0
                      && this->current_node->get_parent()->get_left() != this->current_node)
                    this->current_node = this->current_node->get_parent();

                this->current_node = this->current_node->get_parent();
            }
        }

        return *this;
    }

    template <typename E, typename Compare>
    typename avl_tree<E, Compare>::avl_const_iterator
            avl_tree<E, Compare>::avl_const_iterator::operator++(int) &
    {
        avl_tree<E, Compare>::avl_const_iterator result = *this;

        ++(*this);
        return result;
    }

    template <typename E, typename Compare>
    typename avl_tree<E, Compare>::avl_const_iterator &
            avl_tree<E, Compare>::avl_const_iterator::operator--()
    {
        if(this->current_node->get_height() > 0)
        {
            if(this->current_node->get_left() != nullptr)
                this->current_node = this->current_node->get_left()->maximum();
            else
            {
                while(this->current_node->get_parent()->get_height() > 0
                      && this->current_node->get_parent()->get_right() != this->current_node)
                    this->current_node = this->current_node->get_parent();

                this->current_node = this->current_node->get_parent();
            }
        }
        else
            this->current_node = this->current_node->get_parent()->maximum();

        return *this;
    }

    template <typename E, typename Compare>
    typename avl_tree<E, Compare>::avl_const_iterator
            avl_tree<E, Compare>::avl_const_iterator::operator--(int) &
    {
        avl_tree<E, Compare>::avl_const_iterator result = *this;

        --(*this);

        return result;
    }

    template <typename E, typename Compare>
    bool avl_tree<E, Compare>::avl_const_iterator::operator==(
            const avl_tree<E, Compare>::avl_const_iterator & it) const
    {
        return this->current_node == it.current_node;
    }

    template <typename E, typename Compare>
    bool avl_tree<E, Compare>::avl_const_iterator::operator!=(
            const avl_tree<E, Compare>::avl_const_iterator & it) const
    {
        return this->current_node != it.current_node;
    }

#pragma endregion
}

#endif
