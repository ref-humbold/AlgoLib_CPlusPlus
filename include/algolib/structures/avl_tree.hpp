/*!
 * \file avl_tree.hpp
 * \brief Structure of AVL tree.
 */
#ifndef AVL_TREE_HPP_
#define AVL_TREE_HPP_

#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <exception>
#include <functional>
#include <initializer_list>
#include <iterator>
#include <stdexcept>

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
        using value_compare = Compare;
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

        explicit avl_tree(const value_compare & compare = value_compare()) : compare{compare}
        {
        }

        template <typename InputIterator>
        avl_tree(InputIterator first,
                InputIterator last,
                const value_compare & compare = value_compare())
            : avl_tree(compare)
        {
            for(InputIterator it = first; it != last; ++it)
                this->insert(*it);
        }

        avl_tree(std::initializer_list<value_type> init,
                const value_compare & compare = value_compare())
            : avl_tree(init.begin(), init.end(), compare)
        {
        }

        ~avl_tree()
        {
            delete this->tree;
        }

        avl_tree(const avl_tree & avl)
            : tree{new avl_header_node(*avl.tree)}, size_{avl.size_}, compare{avl.compare}
        {
        }

        avl_tree(avl_tree && avl) noexcept
            : size_{std::move(avl.size_)}, compare{std::move(avl.compare)}
        {
            std::swap(this->tree, avl.tree);
        }

        avl_tree & operator=(const avl_tree & avl);
        avl_tree & operator=(avl_tree && avl) noexcept;

        const_iterator cbegin() const
        {
            return const_iterator(this->tree->minimum());
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
            return iterator(this->tree->minimum());
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

        /*!
         * \brief Gets the number of elements in this tree.
         * \return the number of elements
         */
        size_type size() const
        {
            return this->size_;
        }

        /*!
         * \brief Checks whether this tree is empty.
         * \return \c true if the tree is empty, otherwise \c false
         */
        bool empty() const
        {
            return this->get_root() == nullptr;
        }

        //! \brief Removes all elements from this tree.
        void clear();

        /*!
         * \brief Checks whether given element belongs to this tree.
         * \param element the element
         * \return the iterator at the element if found, otherwise iterator at the end
         */
        iterator find(const_reference element);

        /*!
         * \brief Checks whether given element belongs to this tree.
         * \param element the element
         * \return the iterator at the element if found, otherwise iterator at the end
         */
        const_iterator find(const_reference element) const;

        /*!
         * \brief Adds new element to this tree.
         * \param element the new element
         * \return the iterator at the new element and \c true whether insert was successful,
         * otherwise \c false
         */
        std::pair<iterator, bool> insert(const_reference element);

        /*!
         * \brief Adds new element to this tree constructed in-place with the given arguments.
         * \param args the arguments to forward to the new element's constructor
         * \return the iterator at the new element and \c true whether emplace was successful,
         * otherwise \c false
         */
        template <typename... Args>
        std::pair<iterator, bool> emplace(Args &&... args);

        /*!
         * \brief Removes given element from this tree, if present.
         * \param element the element
         * \return the number of element removed
         */
        size_type erase(const_reference element);

    private:
        inner_ptr get_root() const
        {
            return this->tree->parent();
        }

        void set_root(inner_ptr node)
        {
            this->tree->parent(node);
        }

        bool is_left_child(inner_ptr node)
        {
            return node->parent()->height() > 0 && node->parent()->left() == node;
        }

        bool is_right_child(inner_ptr node)
        {
            return node->parent()->height() > 0 && node->parent()->right() == node;
        }

        // Determines the subtree where given value might be present:
        // - node if element is in it
        // - left child if element is less than node's element
        // - right child if element is greater than node's element
        inner_ptr search(inner_ptr node, const_reference element) const;

        // Searches for node that satisfies given predicate with given value.
        inner_ptr find_node(const_reference element,
                std::function<bool(inner_ptr, const_reference)> predicate) const;

        // Inserts inner node to this tree
        std::pair<iterator, bool> insert_node(inner_ptr node);

        // Removes inner node from this tree.
        void delete_node(inner_ptr node);

        // Replaces the subtree rooted in one node with subtree of another node.
        void replace_node(inner_ptr node1, inner_ptr node2);

        // Rotates the node along the edge to its parent.
        void rotate(inner_ptr node);

        // Restores balancing on the path from given node to the root.
        void balance(node_ptr node);

        // Counts current node balance.
        int count_balance(inner_ptr node);

        header_ptr tree = new avl_header_node();
        size_type size_ = 0;
        value_compare compare;
    };

    template <typename E, typename Compare>
    avl_tree<E, Compare> & avl_tree<E, Compare>::operator=(const avl_tree<E, Compare> & avl)
    {
        header_ptr tree_orig = this->tree;

        this->size_ = avl.size_;
        this->compare = avl.compare;
        this->tree = new avl_header_node(*avl.tree);
        delete tree_orig;

        return *this;
    }

    template <typename E, typename Compare>
    avl_tree<E, Compare> & avl_tree<E, Compare>::operator=(avl_tree<E, Compare> && avl) noexcept
    {
        std::swap(this->tree, avl.tree);
        std::swap(this->size_, avl.size_);
        std::swap(this->compare, avl.compare);

        return *this;
    }

    template <typename E, typename Compare>
    void avl_tree<E, Compare>::clear()
    {
        delete this->get_root();
        this->set_root(nullptr);
        this->size_ = 0;
    }

    template <typename E, typename Compare>
    typename avl_tree<E, Compare>::iterator avl_tree<E, Compare>::find(const_reference element)
    {
        if(this->empty())
            return this->end();

        std::function<bool(inner_ptr, const_reference)> equal =
                [this](inner_ptr n, const_reference e)
        { return !compare(n->element, e) && !compare(e, n->element); };
        node_ptr the_node = this->find_node(element, equal);

        return the_node == nullptr ? this->end() : iterator(the_node);
    }

    template <typename E, typename Compare>
    typename avl_tree<E, Compare>::const_iterator avl_tree<E, Compare>::find(
            const_reference element) const
    {
        if(this->empty())
            return this->cend();

        std::function<bool(inner_ptr, const_reference)> equal =
                [this](inner_ptr n, const_reference e)
        { return !compare(n->element, e) && !compare(e, n->element); };
        node_ptr the_node = this->find_node(element, equal);

        return the_node == nullptr ? this->cend() : const_iterator(the_node);
    }

    template <typename E, typename Compare>
    std::pair<typename avl_tree<E, Compare>::iterator, bool> avl_tree<E, Compare>::insert(
            const_reference element)
    {
        return this->insert_node(new avl_inner_node(element));
    }

    template <typename E, typename Compare>
    template <typename... Args>
    std::pair<typename avl_tree<E, Compare>::iterator, bool> avl_tree<E, Compare>::emplace(
            Args &&... args)
    {
        return this->insert_node(new avl_inner_node(value_type(std::forward<Args>(args)...)));
    }

    template <typename E, typename Compare>
    typename avl_tree<E, Compare>::size_type avl_tree<E, Compare>::erase(const_reference element)
    {
        std::function<bool(inner_ptr, const_reference)> equal =
                [this](inner_ptr n, const_reference e)
        { return !this->compare(n->element, e) && !this->compare(e, n->element); };
        inner_ptr the_node = this->find_node(element, equal);

        if(the_node == nullptr)
            return 0;

        this->delete_node(the_node);

        return 1;
    }

    template <typename E, typename Compare>
    typename avl_tree<E, Compare>::inner_ptr avl_tree<E, Compare>::search(inner_ptr node,
            const_reference element) const
    {
        if(this->compare(element, node->element))
            return node->left();

        if(this->compare(node->element, element))
            return node->right();

        return node;
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
    std::pair<typename avl_tree<E, Compare>::iterator, bool> avl_tree<E, Compare>::insert_node(
            typename avl_tree<E, Compare>::inner_ptr node)
    {
        std::function<bool(inner_ptr, const_reference)> child_equal =
                [this](inner_ptr n, const_reference e)
        {
            inner_ptr child = this->search(n, e);

            return child == nullptr
                   || (!this->compare(child->element, e) && !this->compare(e, child->element));
        };
        inner_ptr node_parent = this->find_node(node->element, child_equal);

        if(node_parent == nullptr)
        {
            this->set_root(node);
            ++this->size_;

            return std::make_pair(iterator(node), true);
        }

        inner_ptr the_node = this->search(node_parent, node->element);

        if(the_node != nullptr)
        {
            delete node;
            return std::make_pair(iterator(the_node), false);
        }

        if(this->compare(node->element, node_parent->element))
            node_parent->left(node);
        else
            node_parent->right(node);

        this->balance(node_parent);
        ++this->size_;

        return std::make_pair(iterator(node), true);
    }

    template <typename E, typename Compare>
    void avl_tree<E, Compare>::delete_node(inner_ptr node)
    {
        if(node->left() != nullptr && node->right() != nullptr)
        {
            inner_ptr succ = node->right()->minimum();

            std::swap(succ->element, node->element);
            this->delete_node(succ);
        }
        else
        {
            inner_ptr child = node->left() != nullptr ? node->left() : node->right();

            if(node->parent()->height() > 0)
            {
                node_ptr node_parent = node->parent();

                this->replace_node(node, child);
                this->balance(node_parent);
            }
            else
                this->set_root(child);

            node->left(nullptr);
            node->right(nullptr);
            --this->size_;
            delete node;
        }
    }

    template <typename E, typename Compare>
    void avl_tree<E, Compare>::replace_node(inner_ptr node1, inner_ptr node2)
    {
        if(this->is_left_child(node1))
            node1->parent()->left(node2);
        else if(this->is_right_child(node1))
            node1->parent()->right(node2);
        else
            this->set_root(node2);

        node1->parent(nullptr);
    }

    template <typename E, typename Compare>
    void avl_tree<E, Compare>::rotate(inner_ptr node)
    {
        if(this->is_right_child(node))
        {
            auto upper_node = static_cast<inner_ptr>(node->parent());

            upper_node->right(node->left());
            this->replace_node(upper_node, node);
            node->left(upper_node);
        }
        else if(this->is_left_child(node))
        {
            auto upper_node = static_cast<inner_ptr>(node->parent());

            upper_node->left(node->right());
            this->replace_node(upper_node, node);
            node->right(upper_node);
        }
    }

    template <typename E, typename Compare>
    void avl_tree<E, Compare>::balance(node_ptr node)
    {
        while(node->height() > 0)
        {
            inner_ptr the_node = static_cast<inner_ptr>(node);
            int new_balance = this->count_balance(the_node);

            if(new_balance >= 2)
            {
                if(this->count_balance(the_node->left()) > 0)
                    this->rotate(the_node->left());
                else if(this->count_balance(the_node->left()) < 0)
                {
                    this->rotate(the_node->left()->right());
                    this->rotate(the_node->left());
                }
            }
            else if(new_balance <= -2)
            {
                if(this->count_balance(the_node->right()) < 0)
                    this->rotate(the_node->right());
                else if(this->count_balance(the_node->right()) > 0)
                {
                    this->rotate(the_node->right()->left());
                    this->rotate(the_node->right());
                }
            }

            node = the_node->parent();
        }
    }

    template <typename E, typename Compare>
    int avl_tree<E, Compare>::count_balance(avl_tree<E, Compare>::inner_ptr node)
    {
        int left_height = node->left() == nullptr ? 0 : node->left()->height();
        int right_height = node->right() == nullptr ? 0 : node->right()->height();

        return left_height - right_height;
    }

#pragma endregion
#pragma region avl_node

    template <typename E, typename Compare>
    struct avl_tree<E, Compare>::avl_node
    {
        virtual ~avl_node() = default;

        virtual size_t height() = 0;

        virtual node_ptr left() = 0;

        virtual void left(node_ptr node) = 0;

        virtual node_ptr right() = 0;

        virtual void right(node_ptr node) = 0;

        virtual node_ptr parent() = 0;

        virtual void parent(node_ptr node) = 0;

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
        explicit avl_inner_node(const_reference element)
            : avl_tree<E, Compare>::avl_node(),
              element{element},
              height_{1},
              left_{nullptr},
              right_{nullptr},
              parent_{nullptr}
        {
        }

        ~avl_inner_node() override;
        avl_inner_node(const avl_inner_node & node);
        avl_inner_node(avl_inner_node &&) = delete;
        avl_inner_node & operator=(const avl_inner_node & node);
        avl_inner_node & operator=(avl_inner_node &&) = delete;

        size_t height() override
        {
            return this->height_;
        }

        inner_ptr left() override
        {
            return this->left_;
        }

        void left(node_ptr node) override
        {
            this->set_left(static_cast<inner_ptr>(node));
        }

        inner_ptr right() override
        {
            return this->right_;
        }

        void right(node_ptr node) override
        {
            this->set_right(static_cast<inner_ptr>(node));
        }

        node_ptr parent() override
        {
            return this->parent_;
        }

        void parent(node_ptr node) override
        {
            this->parent_ = node;
        }

        inner_ptr minimum() override
        {
            return this->left_ == nullptr ? this : this->left_->minimum();
        }

        inner_ptr maximum() override
        {
            return this->right_ == nullptr ? this : this->right_->maximum();
        }

        value_type element;  //!< Value in the node.

    private:
        void count_height();
        void set_left(inner_ptr node);
        void set_right(inner_ptr node);

        int height_;
        inner_ptr left_;
        inner_ptr right_;
        node_ptr parent_;
    };

    template <typename E, typename Compare>
    avl_tree<E, Compare>::avl_inner_node::~avl_inner_node()
    {
        delete this->left_;
        delete this->right_;
    }

    template <typename E, typename Compare>
    avl_tree<E, Compare>::avl_inner_node::avl_inner_node(
            const avl_tree<E, Compare>::avl_inner_node & node)
        : avl_tree<E, Compare>::avl_node(),
          element{node.element},
          height_{node.height_},
          left_{nullptr},
          right_{nullptr},
          parent_{nullptr}
    {
        if(node.left_ != nullptr)
            this->set_left(new avl_inner_node(*node.left_));

        if(node.right_ != nullptr)
            this->set_right(new avl_inner_node(*node.right_));
    }

    template <typename E, typename Compare>
    typename avl_tree<E, Compare>::avl_inner_node & avl_tree<E, Compare>::avl_inner_node::operator=(
            const avl_tree<E, Compare>::avl_inner_node & node)
    {
        node_ptr left_orig = this->left_;
        node_ptr right_orig = this->right_;

        this->element = node.element;
        this->height_ = node.height_;
        this->left(node.left_ == nullptr ? nullptr : new avl_inner_node(*node.left_));
        this->right(node.right_ == nullptr ? nullptr : new avl_inner_node(*node.right_));
        delete left_orig;
        delete right_orig;
        return *this;
    }

    template <typename E, typename Compare>
    void avl_tree<E, Compare>::avl_inner_node::count_height()
    {
        int left_height = this->left_ == nullptr ? 0 : this->left_->height();
        int right_height = this->right_ == nullptr ? 0 : this->right_->height();

        this->height_ = std::max(left_height, right_height) + 1;
    }

    template <typename E, typename Compare>
    void avl_tree<E, Compare>::avl_inner_node::set_left(inner_ptr node)
    {
        this->left_ = node;

        if(this->left_ != nullptr)
            this->left_->parent(this);

        this->count_height();
    }

    template <typename E, typename Compare>
    void avl_tree<E, Compare>::avl_inner_node::set_right(inner_ptr node)
    {
        this->right_ = node;

        if(this->right_ != nullptr)
            this->right_->parent(this);

        this->count_height();
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
                this->set_parent(new avl_inner_node(*node.inner));
        }

        avl_header_node(avl_header_node && node) = delete;
        avl_header_node & operator=(const avl_header_node & node);
        avl_header_node & operator=(avl_header_node && node) = delete;

        size_t height() override
        {
            return 0;
        }

        inner_ptr left() override
        {
            return nullptr;
        }

        void left(node_ptr) override
        {
        }

        inner_ptr right() override
        {
            return nullptr;
        }

        void right(node_ptr) override
        {
        }

        inner_ptr parent() override
        {
            return this->inner;
        }

        void parent(node_ptr node) override
        {
            this->set_parent(static_cast<inner_ptr>(node));
        }

        node_ptr minimum() override
        {
            return this->parent() == nullptr ? static_cast<node_ptr>(this)
                                             : static_cast<node_ptr>(this->parent()->minimum());
        }

        node_ptr maximum() override
        {
            return this->parent() == nullptr ? static_cast<node_ptr>(this)
                                             : static_cast<node_ptr>(this->parent()->maximum());
        }

    private:
        void set_parent(inner_ptr node)
        {
            this->inner = node;

            if(this->inner != nullptr)
                this->inner->parent(this);
        }

        inner_ptr inner;
    };

    template <typename E, typename Compare>
    typename avl_tree<E, Compare>::avl_header_node &
            avl_tree<E, Compare>::avl_header_node::operator=(
                    const avl_tree<E, Compare>::avl_header_node & node)
    {
        node_ptr inner_orig = this->inner;

        this->parent(node.inner == nullptr ? nullptr : new avl_inner_node(*node.inner));
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
        if(this->current_node->height() > 0)
        {
            if(this->current_node->right() != nullptr)
                this->current_node = this->current_node->right()->minimum();
            else
            {
                while(this->current_node->parent()->height() > 0
                        && this->current_node->parent()->left() != this->current_node)
                    this->current_node = this->current_node->parent();

                this->current_node = this->current_node->parent();
            }
        }

        return *this;
    }

    template <typename E, typename Compare>
    typename avl_tree<E, Compare>::avl_iterator avl_tree<E, Compare>::avl_iterator::operator++(
            int) &
    {
        avl_tree<E, Compare>::avl_const_iterator result = *this;

        ++(*this);
        return result;
    }

    template <typename E, typename Compare>
    typename avl_tree<E, Compare>::avl_iterator & avl_tree<E, Compare>::avl_iterator::operator--()
    {
        if(this->current_node->height() > 0)
        {
            if(this->current_node->left() != nullptr)
                this->current_node = this->current_node->left()->maximum();
            else
            {
                while(this->current_node->parent()->height() > 0
                        && this->current_node->parent()->right() != this->current_node)
                    this->current_node = this->current_node->parent();

                this->current_node = this->current_node->parent();
            }
        }
        else
            this->current_node = this->current_node->maximum();

        return *this;
    }

    template <typename E, typename Compare>
    typename avl_tree<E, Compare>::avl_iterator avl_tree<E, Compare>::avl_iterator::operator--(
            int) &
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
        if(this->current_node->height() > 0)
        {
            if(this->current_node->right() != nullptr)
                this->current_node = this->current_node->right()->minimum();
            else
            {
                while(this->current_node->parent()->height() > 0
                        && this->current_node->parent()->left() != this->current_node)
                    this->current_node = this->current_node->parent();

                this->current_node = this->current_node->parent();
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
        if(this->current_node->height() > 0)
        {
            if(this->current_node->left() != nullptr)
                this->current_node = this->current_node->left()->maximum();
            else
            {
                while(this->current_node->parent()->height() > 0
                        && this->current_node->parent()->right() != this->current_node)
                    this->current_node = this->current_node->parent();

                this->current_node = this->current_node->parent();
            }
        }
        else
            this->current_node = this->current_node->maximum();

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
