/*!
 * \file avl_tree.hpp
 * \brief AVL tree structure.
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

namespace algolib
{
    namespace structures
    {
#pragma region avl_tree

        template <typename E, typename C = std::less<E>>
        class avl_tree
        {
        private:
            class avl_node;
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

            using compare = C;
            using iterator = avl_iterator;
            using const_iterator = avl_const_iterator;
            using reverse_iterator = std::reverse_iterator<avl_iterator>;
            using const_reverse_iterator = std::reverse_iterator<avl_const_iterator>;

            using difference_type = typename std::iterator_traits<iterator>::difference_type;
            using size_type = size_t;

            explicit avl_tree(const compare & cmp = compare()) : cmp{cmp}
            {
            }

            avl_tree(std::initializer_list<value_type> il, const compare & cmp = compare())
                : cmp{cmp}
            {
                insert(il);
            }

            ~avl_tree()
            {
                delete tree;
            }

            avl_tree(const avl_tree & avl)
                : tree{new avl_header_node(*avl.tree)}, elems{avl.elems}, cmp{avl.cmp}
            {
            }

            avl_tree(avl_tree && avl) noexcept
                : elems{std::move(avl.elems)}, cmp{std::move(avl.cmp)}
            {
                std::swap(this->tree, avl.tree);
            }

            avl_tree<E, C> & operator=(const avl_tree<E, C> & avl);
            avl_tree<E, C> & operator=(avl_tree<E, C> && avl) noexcept;

            const_iterator cbegin() const
            {
                return const_iterator(get_root()->minimum());
            }

            const_iterator cend() const
            {
                return const_iterator(tree);
            }

            const_reverse_iterator crbegin() const
            {
                return const_reverse_iterator(cend());
            }

            const_reverse_iterator crend() const
            {
                return const_reverse_iterator(cbegin());
            }

            iterator begin()
            {
                return iterator(get_root()->minimum());
            }

            const_iterator begin() const
            {
                return cbegin();
            }

            iterator end()
            {
                return iterator(tree);
            }

            const_iterator end() const
            {
                return cend();
            }

            reverse_iterator rbegin()
            {
                return reverse_iterator(end());
            }

            const_reverse_iterator rbegin() const
            {
                return crbegin();
            }

            reverse_iterator rend()
            {
                return reverse_iterator(begin());
            }

            const_reverse_iterator rend() const
            {
                return crend();
            }

            size_type size() const
            {
                return elems;
            }

            bool empty() const
            {
                return get_root() == nullptr;
            }

            /*!
             * \brief Checks whether given value is present in the tree.
             * \param element value to check
             * \return iterator on the element if found, otherwise iterator at the end
             */
            iterator find(const_reference element);

            /*!
             * \brief Checks whether given value is present in the tree.
             * \param element value to check
             * \return iterator on the element if found, otherwise iterator at the end
             */
            const_iterator find(const_reference element) const;

            /*!
             * \brief Adds a new value to the tree.
             * \param element value to be added
             * \return iterator at the new element and \c true whether insert was successful,
             * otherwise \c false
             */
            std::pair<iterator, bool> insert(const_reference element);

            /*!
             * \brief Adds values from initializer list to the tree.
             * \param il An initializer list with new values
             */
            void insert(std::initializer_list<value_type> il);

            /*!
             * \brief Removes element from the tree if present.
             * \param element value to be removed
             * \return number of element removed
             */
            size_type erase(const_reference element);

            //! \brief Removes all elements in the tree.
            void clear();

        private:
            /*!
             * \brief Removes node from the tree.
             * @param node node to be removed
             */
            void destroy_node(inner_ptr node)
            {
                node->set_left(nullptr);
                node->set_right(nullptr);
                --elems;
                delete node;
            }

            //! \return root of the tree
            inner_ptr get_root() const
            {
                return tree->get_parent();
            }

            //! \param node node that will become the new root of the tree
            void set_root(inner_ptr node)
            {
                tree->set_parent(node);
            }

            /*!
             * \brief Checks whether given node is a left child.
             * @param node node to be checked
             * @return \c true if the node is left child, otherwise \c false
             */
            bool is_left_child(inner_ptr node)
            {
                return node->get_parent()->get_height() > 0
                       && node->get_parent()->get_left() == node;
            }

            /*!
             * \brief Checks whether given node is a right child.
             * @param node node to be checked
             * @return \c true if the node is right child, otherwise \c false
             */
            bool is_right_child(inner_ptr node)
            {
                return node->get_parent()->get_height() > 0
                       && node->get_parent()->get_right() == node;
            }

            /*!
             * \brief Determines the subtree where given value might be present.
             * \param node node
             * \param element value to find
             * \return the node if it hold given value, otherwise left child if the value is less or
             * right child if the value is greater
             */
            inner_ptr search(inner_ptr node, const_reference element) const;

            /*!
             * \brief Searches for node that satisfies given predicate with given value.
             * \param element value for predicate
             * \param predicate predicate for node and argument value
             * \return node that satisfies the predicate if any, otherwise \c nullptr
             */
            inner_ptr find_node(const_reference element,
                                std::function<bool(inner_ptr, const_reference)> predicate) const;

            /*!
             * \brief Removes inner node from the tree.
             * \param node node to be removed
             */
            void delete_node(inner_ptr node);

            /*!
             * \brief Replaces the subtree rootted in one node with subtree of another node.
             * @param node1 root of the subtree to be replaced
             * @param node2 root of the new subtree
             */
            void replace_node(inner_ptr node1, inner_ptr node2);

            /*!
             * \brief Rotates the node along the egde to its parent.
             * @param node node to be rotated
             */
            void rotate(inner_ptr node);

            /**
             * \brief Restores balancing on a path from given node to the root.
             * \param node node to start balancing from
             */
            void balance(node_ptr node);

            /*!
             * \brief Counts current node balance.
             * \param node node
             * \return balance value
             */
            int count_balance(node_ptr node);

            header_ptr tree = new avl_header_node();    //!< The tree denoted by its header.
            size_type elems = 0;    //!< Number of elements.
            compare cmp;    //!< Comparator.
        };

        template <typename E, typename C>
        avl_tree<E, C> & avl_tree<E, C>::operator=(const avl_tree<E, C> & avl)
        {
            header_ptr tree_orig = this->tree;

            this->elems = avl.elems;
            this->cmp = avl.cmp;
            this->tree = new avl_header_node(*avl.tree);
            delete tree_orig;

            return *this;
        }

        template <typename E, typename C>
        avl_tree<E, C> & avl_tree<E, C>::operator=(avl_tree<E, C> && avl) noexcept
        {
            std::swap(this->tree, avl.tree);
            std::swap(this->elems, avl.elems);
            std::swap(this->cmp, avl.cmp);

            return *this;
        }

        template <typename E, typename C>
        typename avl_tree<E, C>::iterator avl_tree<E, C>::find(const_reference element)
        {
            if(empty())
                return end();

            std::function<bool(inner_ptr, const_reference)> equal =
                    [this](inner_ptr n, const_reference e) -> bool {
                return !cmp(n->element, e) && !cmp(e, n->element);
            };
            node_ptr the_node = find_node(element, equal);

            return the_node == nullptr ? end() : iterator(the_node);
        }

        template <typename E, typename C>
        typename avl_tree<E, C>::const_iterator avl_tree<E, C>::find(const_reference element) const
        {
            if(empty())
                return cend();

            std::function<bool(inner_ptr, const_reference)> equal =
                    [this](inner_ptr n, const_reference e) -> bool {
                return !cmp(n->element, e) && !cmp(e, n->element);
            };
            node_ptr the_node = find_node(element, equal);

            return the_node == nullptr ? cend() : const_iterator(the_node);
        }

        template <typename E, typename C>
        std::pair<typename avl_tree<E, C>::iterator, bool>
                avl_tree<E, C>::insert(const_reference element)
        {
            std::function<bool(inner_ptr, const_reference)> child_equal =
                    [this](inner_ptr n, const_reference e) -> bool {
                inner_ptr child = search(n, e);

                return child == nullptr || (!cmp(child->element, e) && !cmp(e, child->element));
            };
            inner_ptr node_parent = find_node(element, child_equal);

            if(node_parent == nullptr)
            {
                auto new_node = new avl_inner_node(element);

                set_root(new_node);
                ++elems;

                return std::make_pair(iterator(new_node), true);
            }

            inner_ptr the_node = search(node_parent, element);

            if(the_node != nullptr)
                return std::make_pair(iterator(the_node), false);

            auto new_node = new avl_inner_node(element);

            if(cmp(element, node_parent->element))
                node_parent->set_left(new_node);
            else
                node_parent->set_right(new_node);

            balance(node_parent);
            ++elems;

            return std::make_pair(iterator(new_node), true);
        }

        template <typename E, typename C>
        void avl_tree<E, C>::insert(std::initializer_list<value_type> il)
        {
            for(auto i : il)
                insert(i);
        }

        template <typename E, typename C>
        typename avl_tree<E, C>::size_type avl_tree<E, C>::erase(const_reference element)
        {
            std::function<bool(inner_ptr, const_reference)> equal =
                    [this](inner_ptr n, const_reference e) -> bool {
                return !cmp(n->element, e) && !cmp(e, n->element);
            };
            inner_ptr the_node = find_node(element, equal);

            if(the_node == nullptr)
                return 0;

            delete_node(the_node);

            return 1;
        }

        template <typename E, typename C>
        void avl_tree<E, C>::clear()
        {
            delete get_root();
            set_root(nullptr);
            elems = 0;
        }

        template <typename E, typename C>
        typename avl_tree<E, C>::inner_ptr avl_tree<E, C>::search(inner_ptr node,
                                                                  const_reference element) const
        {
            return cmp(element, node->element)
                           ? node->get_left()
                           : cmp(node->element, element) ? node->get_right() : node;
        }

        template <typename E, typename C>
        typename avl_tree<E, C>::inner_ptr avl_tree<E, C>::find_node(
                const_reference element,
                std::function<bool(inner_ptr, const_reference)> predicate) const
        {
            inner_ptr node = get_root();

            while(node != nullptr && !predicate(node, element))
                node = search(node, element);

            return node;
        }

        template <typename E, typename C>
        void avl_tree<E, C>::delete_node(inner_ptr node)
        {
            if(node->get_left() != nullptr && node->get_right() != nullptr)
            {
                inner_ptr succ = node->get_right()->minimum();

                std::swap(succ->element, node->element);
                delete_node(succ);
            }
            else
            {
                inner_ptr child =
                        node->get_left() != nullptr ? node->get_left() : node->get_right();

                if(node->get_parent()->get_height() > 0)
                {
                    node_ptr node_parent = node->get_parent();

                    replace_node(node, child);
                    balance(node_parent);
                }
                else
                    set_root(child);

                destroy_node(node);
            }
        }

        template <typename E, typename C>
        void avl_tree<E, C>::replace_node(inner_ptr node1, inner_ptr node2)
        {
            if(is_left_child(node1))
                node1->get_parent()->set_left(node2);
            else if(is_right_child(node1))
                node1->get_parent()->set_right(node2);
            else
                set_root(node2);

            node1->set_parent(nullptr);
        }

        template <typename E, typename C>
        void avl_tree<E, C>::rotate(inner_ptr node)
        {
            if(is_right_child(node))
            {
                auto upper_node = static_cast<inner_ptr>(node->get_parent());

                upper_node->set_right(node->get_left());
                replace_node(upper_node, node);
                node->set_left(upper_node);
            }
            else if(is_left_child(node))
            {
                auto upper_node = static_cast<inner_ptr>(node->get_parent());

                upper_node->set_left(node->get_right());
                replace_node(upper_node, node);
                node->set_right(upper_node);
            }
        }

        template <typename E, typename C>
        void avl_tree<E, C>::balance(node_ptr node)
        {
            while(node->get_height() > 0)
            {
                node->count_height();

                int new_balance = count_balance(node);
                auto rnode = static_cast<inner_ptr>(node);

                if(new_balance >= 2)
                {
                    if(count_balance(node->get_left()) > 0)
                        rotate(rnode->get_left());
                    else if(count_balance(node->get_left()) < 0)
                    {
                        rotate(rnode->get_left()->get_right());
                        rotate(rnode->get_left());
                    }
                }
                else if(new_balance <= -2)
                {
                    if(count_balance(node->get_right()) < 0)
                        rotate(rnode->get_right());
                    else if(count_balance(node->get_right()) > 0)
                    {
                        rotate(rnode->get_right()->get_left());
                        rotate(rnode->get_right());
                    }
                }

                node = node->get_parent();
            }
        }

        template <typename E, typename C>
        int avl_tree<E, C>::count_balance(avl_tree<E, C>::node_ptr node)
        {
            int left_height = node->get_left() == nullptr ? 0 : node->get_left()->get_height();
            int right_height = node->get_right() == nullptr ? 0 : node->get_right()->get_height();

            return left_height - right_height;
        }

#pragma endregion
#pragma region avl_node

        template <typename E, typename C>
        class avl_tree<E, C>::avl_node
        {
        public:
            avl_node() = default;
            virtual ~avl_node() = default;
            avl_node(const avl_node & node) = default;
            avl_node(avl_node && node) = delete;
            avl_node & operator=(const avl_node & node) = default;
            avl_node & operator=(avl_node && node) = delete;

            virtual size_t get_height() = 0;

            virtual node_ptr get_left() = 0;

            virtual void set_left(node_ptr node) = 0;

            virtual node_ptr get_right() = 0;

            virtual void set_right(node_ptr node) = 0;

            virtual node_ptr get_parent() = 0;

            virtual void set_parent(node_ptr node) = 0;

            //! \brief Recounts the height of the node.
            virtual void count_height() = 0;

            /*!
             * \brief Searches in its subtree for the node with minimal value.
             * @returnthe node with minimal value
             */
            virtual node_ptr minimum() = 0;

            /*!
             * \brief Searches in its subtree for the node with maximal value.
             * \return the node with maximal value
             */
            virtual node_ptr maximum() = 0;
        };

#pragma endregion
#pragma region avl_inner_node

        template <typename E, typename C>
        class avl_tree<E, C>::avl_inner_node : public avl_tree<E, C>::avl_node
        {
        public:
            explicit avl_inner_node(const_reference elem)
                : avl_tree<E, C>::avl_node(), element{elem}
            {
            }

            ~avl_inner_node();
            avl_inner_node(const avl_inner_node & node);
            avl_inner_node(avl_inner_node &&) = delete;
            avl_inner_node & operator=(const avl_inner_node & node);
            avl_inner_node & operator=(avl_inner_node &&) = delete;

            value_type element;    //!< Value in the node.

            size_t get_height() override
            {
                return height;
            }

            inner_ptr get_left() override
            {
                return left;
            }

            void set_left(node_ptr node) override
            {
                left = static_cast<inner_ptr>(node);

                if(left != nullptr)
                    left->set_parent(this);

                count_height();
            }

            inner_ptr get_right() override
            {
                return right;
            }

            void set_right(node_ptr node) override
            {
                right = static_cast<inner_ptr>(node);

                if(right != nullptr)
                    right->set_parent(this);

                count_height();
            }

            node_ptr get_parent() override
            {
                return parent;
            }

            void set_parent(node_ptr node) override
            {
                parent = node;
            }

            void count_height() override;

            inner_ptr minimum() override
            {
                return left == nullptr ? this : left->minimum();
            }

            inner_ptr maximum() override
            {
                return right == nullptr ? this : right->maximum();
            }

        private:
            int height = 1;    //!< Height of the node.
            inner_ptr left = nullptr;    //!< Left child of the node.
            inner_ptr right = nullptr;    //!< Right child of the node.
            node_ptr parent = nullptr;    //!< Parent of the node.
        };

        template <typename E, typename C>
        avl_tree<E, C>::avl_inner_node::~avl_inner_node()
        {
            delete left;
            delete right;
        }

        template <typename E, typename C>
        avl_tree<E, C>::avl_inner_node::avl_inner_node(const avl_tree<E, C>::avl_inner_node & node)
            : avl_tree<E, C>::avl_node(),
              element{node.element},
              height{node.height},
              left{nullptr},
              right{nullptr},
              parent{nullptr}
        {
            if(node.left != nullptr)
                set_left(new avl_inner_node(*node.left));

            if(node.right != nullptr)
                set_right(new avl_inner_node(*node.right));
        }

        template <typename E, typename C>
        typename avl_tree<E, C>::avl_inner_node & avl_tree<E, C>::avl_inner_node::
                operator=(const avl_tree<E, C>::avl_inner_node & node)
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

        template <typename E, typename C>
        void avl_tree<E, C>::avl_inner_node::count_height()
        {
            int left_height = left == nullptr ? 0 : left->get_height();
            int right_height = right == nullptr ? 0 : right->get_height();

            height = std::max(left_height, right_height) + 1;
        }

#pragma endregion
#pragma region avl_header_node

        template <typename E, typename C>
        class avl_tree<E, C>::avl_header_node : public avl_tree<E, C>::avl_node
        {
        public:
            avl_header_node() : avl_tree<E, C>::avl_node()
            {
            }

            ~avl_header_node()
            {
                delete inner;
            }

            avl_header_node(const avl_header_node & node)
                : avl_tree<E, C>::avl_node(), inner{nullptr}
            {
                if(node.inner != nullptr)
                    set_parent(new avl_inner_node(*node.inner));
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
                return inner;
            }

            void set_parent(node_ptr node) override
            {
                inner = static_cast<inner_ptr>(node);

                if(inner != nullptr)
                    inner->set_parent(this);
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
            inner_ptr inner = nullptr;    //!< The real tree denoted by its root.
        };

        template <typename E, typename C>
        typename avl_tree<E, C>::avl_header_node & avl_tree<E, C>::avl_header_node::
                operator=(const avl_tree<E, C>::avl_header_node & node)
        {
            node_ptr inner_orig = this->inner;

            this->set_parent(node.inner == nullptr ? nullptr : new avl_inner_node(*node.inner));
            delete inner_orig;

            return *this;
        }

#pragma endregion
#pragma region avl_iterator

        template <typename E, typename C>
        class avl_tree<E, C>::avl_iterator
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

            avl_iterator(const avl_iterator & it) : current_node{it.current_node}
            {
            }

            avl_iterator(avl_iterator && it) noexcept : current_node{it.current_node}
            {
            }

            avl_iterator & operator=(const avl_iterator & it)
            {
                this->current_node = it.current_node;
            }

            avl_iterator & operator=(avl_iterator && it) noexcept
            {
                this->current_node = it.current_node;
            }

            reference operator*() const
            {
                return static_cast<inner_ptr>(current_node)->element;
            }

            pointer operator->() const
            {
                return &(operator*());
            }

            avl_iterator & operator++();

            const avl_iterator operator++(int);

            avl_iterator & operator--();

            const avl_iterator operator--(int);

            bool operator==(const avl_iterator & it) const;

            bool operator!=(const avl_iterator & it) const;

        private:
            node_ptr current_node;
        };

        template <typename E, typename C>
        typename avl_tree<E, C>::avl_iterator & avl_tree<E, C>::avl_iterator::operator++()
        {
            if(current_node->get_height() > 0)
            {
                if(current_node->get_right() != nullptr)
                    current_node = current_node->get_right()->minimum();
                else
                {
                    while(current_node->get_parent()->get_height() > 0
                          && current_node->get_parent()->get_left() != current_node)
                        current_node = current_node->get_parent();

                    current_node = current_node->get_parent();
                }
            }

            return *this;
        }

        template <typename E, typename C>
        const typename avl_tree<E, C>::avl_iterator avl_tree<E, C>::avl_iterator::operator++(int)
        {
            avl_tree<E, C>::avl_const_iterator result = *this;

            ++(*this);

            return result;
        }

        template <typename E, typename C>
        typename avl_tree<E, C>::avl_iterator & avl_tree<E, C>::avl_iterator::operator--()
        {
            if(current_node->get_height() > 0)
            {
                if(current_node->get_left() != nullptr)
                    current_node = current_node->get_left()->maximum();
                else
                {
                    while(current_node->get_parent()->get_height() > 0
                          && current_node->get_parent()->get_right() != current_node)
                        current_node = current_node->get_parent();

                    current_node = current_node->get_parent();
                }
            }
            else
                current_node = current_node->get_parent()->maximum();

            return *this;
        }

        template <typename E, typename C>
        const typename avl_tree<E, C>::avl_iterator avl_tree<E, C>::avl_iterator::operator--(int)
        {
            avl_tree<E, C>::avl_const_iterator result = *this;

            --(*this);

            return result;
        }

        template <typename E, typename C>
        bool avl_tree<E, C>::avl_iterator::operator==(const avl_tree<E, C>::avl_iterator & it) const
        {
            return this->current_node == it.current_node;
        }

        template <typename E, typename C>
        bool avl_tree<E, C>::avl_iterator::operator!=(const avl_tree<E, C>::avl_iterator & it) const
        {
            return this->current_node != it.current_node;
        }

#pragma endregion
#pragma region avl_const_iterator

        template <typename E, typename C>
        class avl_tree<E, C>::avl_const_iterator
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

            avl_const_iterator(const avl_iterator & it) : current_node{it.current_node}
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
            }

            avl_const_iterator & operator=(avl_const_iterator && it) noexcept
            {
                this->current_node = it.current_node;
            }

            reference operator*() const
            {
                return static_cast<inner_ptr>(current_node)->element;
            }

            pointer operator->() const
            {
                return &(operator*());
            }

            avl_const_iterator & operator++();

            const avl_const_iterator operator++(int);

            avl_const_iterator & operator--();

            const avl_const_iterator operator--(int);

            bool operator==(const avl_const_iterator & it) const;

            bool operator!=(const avl_const_iterator & it) const;

        private:
            node_ptr current_node;
        };

        template <typename E, typename C>
        typename avl_tree<E, C>::avl_const_iterator & avl_tree<E, C>::avl_const_iterator::
                operator++()
        {
            if(current_node->get_height() > 0)
            {
                if(current_node->get_right() != nullptr)
                    current_node = current_node->get_right()->minimum();
                else
                {
                    while(current_node->get_parent()->get_height() > 0
                          && current_node->get_parent()->get_left() != current_node)
                        current_node = current_node->get_parent();

                    current_node = current_node->get_parent();
                }
            }

            return *this;
        }

        template <typename E, typename C>
        const typename avl_tree<E, C>::avl_const_iterator avl_tree<E, C>::avl_const_iterator::
                operator++(int)
        {
            avl_tree<E, C>::avl_const_iterator result = *this;

            ++(*this);

            return result;
        }

        template <typename E, typename C>
        typename avl_tree<E, C>::avl_const_iterator & avl_tree<E, C>::avl_const_iterator::
                operator--()
        {
            if(current_node->get_height() > 0)
            {
                if(current_node->get_left() != nullptr)
                    current_node = current_node->get_left()->maximum();
                else
                {
                    while(current_node->get_parent()->get_height() > 0
                          && current_node->get_parent()->get_right() != current_node)
                        current_node = current_node->get_parent();

                    current_node = current_node->get_parent();
                }
            }
            else
                current_node = current_node->get_parent()->maximum();

            return *this;
        }

        template <typename E, typename C>
        const typename avl_tree<E, C>::avl_const_iterator avl_tree<E, C>::avl_const_iterator::
                operator--(int)
        {
            avl_tree<E, C>::avl_const_iterator result = *this;

            --(*this);

            return result;
        }

        template <typename E, typename C>
        bool avl_tree<E, C>::avl_const_iterator::
                operator==(const avl_tree<E, C>::avl_const_iterator & it) const
        {
            return this->current_node == it.current_node;
        }

        template <typename E, typename C>
        bool avl_tree<E, C>::avl_const_iterator::
                operator!=(const avl_tree<E, C>::avl_const_iterator & it) const
        {
            return this->current_node != it.current_node;
        }

#pragma endregion
    }
}

#endif
