/**
 * @file avl_tree.hpp
 * @brief AVL tree structure.
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
            using reference = E &;
            using const_reference = const E &;
            using pointer = E *;
            using const_pointer = const E *;

            using compare = C;
            using iterator = avl_iterator;
            using const_iterator = avl_const_iterator;
            using reverse_iterator = std::reverse_iterator<avl_iterator>;
            using const_reverse_iterator = std::reverse_iterator<avl_const_iterator>;

            using difference_type = typename std::iterator_traits<iterator>::difference_type;
            using size_type = size_t;

            explicit avl_tree(const C & cmp = C()) : cmp{cmp}
            {
            }

            avl_tree(std::initializer_list<E> init_list, const C & cmp = C()) : cmp{cmp}
            {
                for(auto i : init_list)
                    insert(i);
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

            /// @return iterator na początku
            iterator begin() const
            {
                return iterator(get_root()->minimum());
            }

            /// @return iterator na końcu
            iterator end() const
            {
                return iterator(tree);
            }

            /// @return odwrócony iterator na początku
            reverse_iterator rbegin() const
            {
                return reverse_iterator(end());
            }

            /// @return odwrócony iterator na końcu
            reverse_iterator rend() const
            {
                return reverse_iterator(begin());
            }

            /// @return stały iterator na początku
            const_iterator cbegin() const
            {
                return const_iterator(get_root()->minimum());
            }

            /// @return stały iterator na końcu
            const_iterator cend() const
            {
                return const_iterator(tree);
            }

            /// @return stały odwrócony iterator na początku
            const_reverse_iterator crbegin() const
            {
                return const_reverse_iterator(cend());
            }

            /// @return stały odwrócony iterator na końcu
            const_reverse_iterator crend() const
            {
                return const_reverse_iterator(cbegin());
            }

            /// @return liczba elemenów drzewa
            size_type size() const
            {
                return elems;
            }

            /// @return czy drzewo jest puste
            bool empty() const
            {
                return get_root() == nullptr;
            }

            /**
             * Sprawdzanie występowania elementu w drzewie.
             * @param element wartość do znalezienia
             * @return iterator na wartość w drzewie
             */
            iterator find(const E & element) const;

            /**
             * Dodawanie elementu do drzewa.
             * @param element wartość do dodania
             * @return iterator na nowy element z infromacją o jego dodaniu
             */
            std::pair<iterator, bool> insert(const E & element);

            /**
             * Usuwanie elementu z drzewa.
             * @param element wartość do usunięcia
             */
            void erase(const E & element);

            /// Usuwanie wszystkich elementów z drzewa.
            void clear();

        private:
            /**
             * Usuwanie elementu z pamięci.
             * @param node węzeł do usunięcia
             */
            void destroy_node(inner_ptr node)
            {
                node->set_left(nullptr);
                node->set_right(nullptr);
                --elems;
                delete node;
            }

            /// @return wewnętrzny korzeń drzewa
            inner_ptr get_root() const
            {
                return tree->get_parent();
            }

            /// @param node węzeł, który zostanie wewnętrznym korzeniem
            void set_root(inner_ptr node)
            {
                tree->set_parent(node);
            }

            /**
             * Sprawdzanie, czy węzeł jest lewym synem.
             * @param node węzeł
             * @return czy węzeł to lewy syn
             */
            bool is_left_son(inner_ptr node)
            {
                return node->get_parent()->get_height() > 0
                       && node->get_parent()->get_left() == node;
            }

            /**
             * Sprawdzanie, czy węzeł jest prawym synem.
             * @param node węzeł
             * @return czy węzeł to prawy syn
             */
            bool is_right_son(inner_ptr node)
            {
                return node->get_parent()->get_height() > 0
                       && node->get_parent()->get_right() == node;
            }

            /**
             * Wskazanie poddrzewa, w którym może znaleźć się element.
             * @param node węzeł
             * @param element element
             * @return korzeń poddrzewa z elementem
             */
            inner_ptr search(inner_ptr node, const E & element) const;

            /**
             * Wyszukiwanie węzła spełniającego predykat związany z ustaloną wartością.
             * @param element wartość
             * @param predicate predykat nałożony na węzeł i wartość
             * @return węzeł spełniający predykat
             */
            inner_ptr find_node(
                    const E & element,
                    std::function<bool(avl_tree<E, C>::inner_ptr, const E &)> predicate) const;

            /**
             * Usuwanie elementu z węzła wewnętrznego drzewa.
             * @param node węzeł do usunięcia
             */
            void delete_node(inner_ptr node);

            /**
             * Zamiana poddrzewa ukorzenionego w danym węźle.
             * @param node1 węzeł do zamiany
             * @param node2 korzeń nowego poddrzewa
             */
            void replace_node(inner_ptr node1, inner_ptr node2);

            /**
             * Rotowanie węzła wzdłuż krawędzi z jego ojcem.
             * @param node węzeł do rotacji
             */
            void rotate(inner_ptr node);

            /**
             * Przywracanie balansowania na ścieżce od wierzchołka do korzenia.
             * @param node wierzchołek początkowy
             */
            void balance(node_ptr node);

            /**
             * Wyliczanie balansu wierzchołka.
             * @param node węzeł
             * @return wartość balansu
             */
            int count_balance(node_ptr node);

            /// Korzeń drzewa.
            header_ptr tree = new avl_header_node();

            ///  Liczba elementów drzewa.
            size_type elems = 0;

            /// Komparator.
            compare cmp;
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
        typename avl_tree<E, C>::iterator avl_tree<E, C>::find(const E & element) const
        {
            if(empty())
                return end();

            std::function<bool(inner_ptr, const E &)> equal = [this](inner_ptr n,
                                                                     const E & e) -> bool {
                return !cmp(n->element(), e) && !cmp(e, n->element());
            };
            node_ptr the_node = find_node(element, equal);

            return the_node == nullptr ? end() : iterator(the_node);
        }

        template <typename E, typename C>
        std::pair<typename avl_tree<E, C>::iterator, bool> avl_tree<E, C>::insert(const E & element)
        {
            std::function<bool(inner_ptr, const E &)> child_equal = [this](inner_ptr n,
                                                                           const E & e) -> bool {
                inner_ptr child = search(n, e);

                return child == nullptr || (!cmp(child->element(), e) && !cmp(e, child->element()));
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

            if(cmp(element, node_parent->element()))
                node_parent->set_left(new_node);
            else
                node_parent->set_right(new_node);

            balance(node_parent);
            ++elems;

            return std::make_pair(iterator(new_node), true);
        }

        template <typename E, typename C>
        void avl_tree<E, C>::erase(const E & element)
        {
            std::function<bool(inner_ptr, const E &)> equal = [this](inner_ptr n,
                                                                     const E & e) -> bool {
                return !cmp(n->element(), e) && !cmp(e, n->element());
            };
            inner_ptr the_node = find_node(element, equal);

            if(the_node == nullptr)
                return;

            delete_node(the_node);
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
                                                                  const E & element) const
        {
            if(cmp(element, node->element()))
                return node->get_left();

            if(cmp(node->element(), element))
                return node->get_right();

            return node;
        }

        template <typename E, typename C>
        typename avl_tree<E, C>::inner_ptr avl_tree<E, C>::find_node(
                const E & element,
                std::function<bool(avl_tree<E, C>::inner_ptr, const E &)> predicate) const
        {
            typename avl_tree<E, C>::inner_ptr node = get_root();

            while(node != nullptr && !predicate(node, element))
                node = search(node, element);

            return node;
        }

        template <typename E, typename C>
        void avl_tree<E, C>::delete_node(inner_ptr node)
        {
            if(node->get_left() != nullptr && node->get_right() != nullptr)
            {
                avl_tree<E, C>::inner_ptr succ = node->get_right()->minimum();

                std::swap(succ->element(), node->element());
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
            if(is_left_son(node1))
                node1->get_parent()->set_left(node2);
            else if(is_right_son(node1))
                node1->get_parent()->set_right(node2);
            else
                set_root(node2);

            node1->set_parent(nullptr);
        }

        template <typename E, typename C>
        void avl_tree<E, C>::rotate(inner_ptr node)
        {
            if(is_right_son(node))
            {
                auto upper_node = static_cast<inner_ptr>(node->get_parent());

                upper_node->set_right(node->get_left());
                replace_node(upper_node, node);
                node->set_left(upper_node);
            }
            else if(is_left_son(node))
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

            /// Wyliczanie wysokości wierzchołka.
            virtual void count_height() = 0;

            /**
             * Wyszukiwanie minimum w poddrzewie.
             * @return węzeł z minimalną wartością w poddrzewie
             */
            virtual node_ptr minimum() = 0;

            /**
             * Wyszukiwanie maksimum w ukorzenionym poddrzewie.
             * @return węzeł z maksymalną wartością w poddrzewie
             */
            virtual node_ptr maximum() = 0;
        };

#pragma endregion
#pragma region avl_inner_node

        template <typename E, typename C>
        class avl_tree<E, C>::avl_inner_node : public avl_tree<E, C>::avl_node
        {
        public:
            explicit avl_inner_node(const E & elem) : avl_tree<E, C>::avl_node(), elem{elem}
            {
            }

            ~avl_inner_node();
            avl_inner_node(const avl_inner_node & node);
            avl_inner_node(avl_inner_node &&) = delete;
            avl_inner_node & operator=(const avl_inner_node & node);
            avl_inner_node & operator=(avl_inner_node &&) = delete;

            E & element()
            {
                return elem;
            }

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
            /// Wartość w węźle.
            E elem;

            /// Wysokość węzła.
            int height = 1;

            /// Lewy syn węzła.
            inner_ptr left = nullptr;

            /// Prawy syn węzła.
            inner_ptr right = nullptr;

            /// Ojciec węzła.
            node_ptr parent = nullptr;
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
              elem{node.elem},
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

            this->elem = node.elem;
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
            /// Wewnętrzne wierzchołki.
            inner_ptr inner = nullptr;
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
            using reference = E &;
            using pointer = E *;
            using difference_type = ptrdiff_t;

            explicit avl_iterator(avl_tree<E, C>::node_ptr node) : current_node{node}
            {
            }

            reference operator*() const
            {
                return static_cast<avl_tree<E, C>::inner_ptr>(current_node)->element();
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

            explicit operator avl_const_iterator()
            {
                return avl_const_iterator(current_node);
            }

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
            avl_tree<E, C>::avl_iterator result = *this;

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
            avl_tree<E, C>::avl_iterator result = *this;

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
            using reference = const E &;
            using pointer = const E *;
            using difference_type = ptrdiff_t;

            explicit avl_const_iterator(avl_tree<E, C>::node_ptr node) : current_node{node}
            {
            }

            reference operator*() const
            {
                return const_cast<const E &>(
                        static_cast<avl_tree<E, C>::inner_ptr>(current_node)->element());
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
