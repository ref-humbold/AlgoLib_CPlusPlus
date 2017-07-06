/**
 * @file avl_tree.h
 * DRZEWO AVL
 */
#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <cstdlib>
#include <cmath>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <initializer_list>
#include <iterator>

namespace algolib
{
    namespace structures
    {
        // avl_tree

        template <typename E>
        class avl_tree
        {
        protected:
            class avl_node;
            class avl_inner_node;
            class avl_root_node;

            class avl_iterator;
            class avl_fwd_iterator;
            class avl_rev_iterator;

            using node_pointer = avl_node *;

        public:
            using iterator = avl_fwd_iterator;
            using reverse_iterator = avl_rev_iterator;

        private:
            /// Korzeń drzewa.
            node_pointer tree = new avl_root_node();

            ///  Liczba elementów drzewa.
            size_t elems = 0;

        public:
            avl_tree()
            {
            }

            explicit avl_tree(std::initializer_list<E> init_list)
            {
                for(auto i : init_list)
                    insert(i);
            }

            ~avl_tree()
            {
                delete tree;
            }

            avl_tree(const avl_tree & avl) : tree{new avl_root_node(*avl.tree)}, elems{avl.elems}
            {
            }

            avl_tree(avl_tree && avl) : elems{std::move(avl.elems)}
            {
                std::swap(this->tree, avl.tree);
            }

            avl_tree<E> & operator=(const avl_tree<E> & avl);
            avl_tree<E> & operator=(avl_tree<E> && avl);

            /**
             * Ustawia iterator na początek.
             * @return iterator na najniższym elemencie
             */
            iterator begin() const;

            /**
             * Ustawia iterator na koniec.
             * @return iterator poza drzewem
             */
            iterator end() const;

            /**
             * Ustawia odwrócony iterator na odwrócony początek.
             * @return iterator na nawyższym elemencie
             */
            reverse_iterator rbegin() const;

            /**
             * Ustawia odwrócony iterator na odwrócony koniec.
             * @return iterator poza drzewem
             */
            reverse_iterator rend() const;

            /**
             * Określanie pustości drzewa.
             * @return czy drzewo jest puste
             */
            bool empty() const
            {
                return get_inner_root() == nullptr;
            }

            /**
             * Określanie liczby elementów drzewa.
             * @return liczba elemenów drzewa
             */
            size_t size() const
            {
                return elems;
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

            /**
             * Usuwanie wszystkich elementów z drzewa.
             */
            void clear();

        private:
            /**
             * @return wewnętrzny korzeń drzewa
             */
            node_pointer get_inner_root() const
            {
                return tree->get_right();
            }

            /**
             * @param node węzeł, który zostanie wewnętrznym korzeniem
             */
            void set_inner_root(node_pointer node)
            {
                tree->set_left(node);
            }

            /**
             * Sprawdzanie, czy węzeł jest wewnętrznym korzeniem.
             * @param node węzeł
             * @return czy węzeł to korzeń
             */
            bool is_inner_root(node_pointer node)
            {
                return node->get_parent()->get_height() < 0;
            }

            /**
             * Sprawdzanie, czy węzeł jest lewym synem.
             * @param node węzeł
             * @return czy węzeł to lewy syn
             */
            bool is_left_son(node_pointer node)
            {
                return is_inner_root(node) ? false : node->get_parent()->get_left() == node;
            }

            /**
             * Sprawdzanie, czy węzeł jest prawym synem.
             * @param node węzeł
             * @return czy węzeł to prawy syn
             */
            bool is_right_son(node_pointer node)
            {
                return is_inner_root(node) ? false : node->get_parent()->get_right() == node;
            }

            /**
             * Wskazanie poddrzewa, w którym może znaleźć się element.
             * @param node węzeł
             * @param element element
             * @return korzeń poddrzewa z elementem
             */
            node_pointer get_subtree(node_pointer node, const E & element) const;

            /**
             * Wyszukiwanie ojca węzła z daną wartością.
             * @param element wartość do znalezienia
             * @return ojciec węzła z wartością
             */
            node_pointer find_node_parent(const E & element) const;

            /**
             * Usuwanie elementu z korzenia drzewa.
             * @param root korzeń drzewa
             */
            void delete_root(node_pointer root);

            /**
             * Usuwanie elementu z węzła wewnętrznego drzewa.
             * @param node węzeł do usunięcia
             */
            void delete_node(node_pointer node);

            /**
             * Zamiana poddrzewa ukorzenionego w danym węźle.
             * @param node1 węzeł do zamiany
             * @param node2 korzeń nowego poddrzewa
             */
            void replace_subtree(node_pointer node1, node_pointer node2);

            /**
             * Rotowanie węzła wzdłuż krawędzi z jego ojcem.
             * @param node węzeł do rotacji
             */
            void rotate(node_pointer node);

            /**
             * Przywracanie balansowania na ścieżce od wierzchołka do korzenia.
             * @param node wierzchołek początkowy
             */
            void rebalance(node_pointer node);
        };

        template <typename E>
        avl_tree<E> & avl_tree<E>::operator=(const avl_tree<E> & avl)
        {
            delete this->tree;
            this->tree = new avl_root_node(*avl.tree);
            this->elems = avl.elems;

            return *this;
        }

        template <typename E>
        avl_tree<E> & avl_tree<E>::operator=(avl_tree<E> && avl)
        {
            std::swap(this->tree, avl.tree);
            std::swap(this->elems, avl.elems);

            return *this;
        }

        template <typename E>
        typename avl_tree<E>::iterator avl_tree<E>::begin() const
        {
            return iterator(get_inner_root()->minimum());
        }

        template <typename E>
        typename avl_tree<E>::iterator avl_tree<E>::end() const
        {
            return iterator(tree);
        }

        template <typename E>
        typename avl_tree<E>::reverse_iterator avl_tree<E>::rbegin() const
        {
            return reverse_iterator(get_inner_root()->maximum());
        }

        template <typename E>
        typename avl_tree<E>::reverse_iterator avl_tree<E>::rend() const
        {
            return reverse_iterator(tree);
        }

        template <typename E>
        typename avl_tree<E>::iterator avl_tree<E>::find(const E & element) const
        {
            if(empty())
                return end();

            avl_tree<E>::node_pointer node_parent = find_node_parent(element);

            if(node_parent == nullptr)
                return iterator(get_inner_root());

            avl_tree<E>::node_pointer the_node = get_subtree(node_parent, element);

            if(the_node == nullptr)
                return end();

            return iterator(the_node);
        }

        template <typename E>
        std::pair<typename avl_tree<E>::iterator, bool> avl_tree<E>::insert(const E & element)
        {
            avl_tree<E>::node_pointer node_parent = find_node_parent(element);
            avl_tree<E>::node_pointer the_node =
                node_parent == nullptr ? get_inner_root() : get_subtree(node_parent, element);

            if(the_node != nullptr)
                return std::make_pair(iterator(the_node), false);

            avl_tree<E>::node_pointer new_node = new avl_inner_node(element);

            if(node_parent != nullptr)
            {
                if(element > node_parent->get_element())
                    node_parent->set_right(new_node);
                else
                    node_parent->set_left(new_node);

                rebalance(node_parent);
            }
            else
                set_inner_root(new_node);

            ++elems;

            return std::make_pair(iterator(new_node), true);
        }

        template <typename E>
        void avl_tree<E>::erase(const E & element)
        {
            avl_tree<E>::node_pointer node_parent = find_node_parent(element);
            avl_tree<E>::node_pointer the_node =
                node_parent == nullptr ? get_inner_root() : get_subtree(node_parent, element);

            if(the_node == nullptr)
                return;

            if(node_parent == nullptr)
                delete_root(the_node);
            else
                delete_node(the_node);
        }

        template <typename E>
        void avl_tree<E>::clear()
        {
            set_inner_root(nullptr);
            elems = 0;
        }

        template <typename E>
        typename avl_tree<E>::node_pointer avl_tree<E>::get_subtree(avl_tree<E>::node_pointer node,
                                                                    const E & element) const
        {
            if(element == node->get_element())
                return node;
            else if(element < node->get_element())
                return node->get_left();
            else
                return node->get_right();
        }

        template <typename E>
        typename avl_tree<E>::node_pointer avl_tree<E>::find_node_parent(const E & element) const
        {
            typename avl_tree<E>::node_pointer tree_iter = get_inner_root();
            typename avl_tree<E>::node_pointer iter_parent = nullptr;

            while(tree_iter != nullptr && tree_iter->get_element() != element)
            {
                iter_parent = tree_iter;
                tree_iter = get_subtree(tree_iter, element);
            }

            return iter_parent;
        }

        template <typename E>
        void avl_tree<E>::delete_root(avl_tree<E>::node_pointer root)
        {
            if(root->get_left() != nullptr && root->get_right() != nullptr)
                delete_node(root);
            else if(root->get_left() != nullptr && root->get_right() == nullptr)
            {
                std::swap(root->get_left()->get_element(), root->get_element());
                set_inner_root(root->get_left());
                root->set_left(nullptr);
                --elems;
            }
            else if(root->get_left() == nullptr && root->get_right() != nullptr)
            {
                std::swap(root->get_right()->get_element(), root->get_element());
                set_inner_root(root->get_right());
                root->set_right(nullptr);
                --elems;
            }
            else
                clear();
        }

        template <typename E>
        void avl_tree<E>::delete_node(avl_tree<E>::node_pointer node)
        {
            if(node->get_left() != nullptr && node->get_right() != nullptr)
            {
                avl_tree<E>::node_pointer succ = node->get_right()->minimum();

                std::swap(succ->get_element(), node->get_element());
                delete_node(succ);
            }
            else
            {
                avl_tree<E>::node_pointer son =
                    node->get_left() != nullptr ? node->get_left() : node->get_right();
                avl_tree<E>::node_pointer node_parent = node->get_parent();

                replace_subtree(node, son);
                rebalance(node_parent);
                --elems;
                delete node;
            }
        }

        template <typename E>
        void avl_tree<E>::replace_subtree(avl_tree<E>::node_pointer node1,
                                          avl_tree<E>::node_pointer node2)
        {
            if(is_inner_root(node1))
                set_inner_root(node2);
            else if(is_left_son(node1))
                node1->get_parent()->set_left(node2);
            else if(is_right_son(node1))
                node1->get_parent()->set_right(node2);

            node1->set_parent(nullptr);
        }

        template <typename E>
        void avl_tree<E>::rotate(avl_tree<E>::node_pointer node)
        {
            if(is_inner_root(node))
                return;

            avl_tree<E>::node_pointer upper_node = node->get_parent();

            if(is_right_son(node))
            {
                upper_node->set_right(node->get_left());
                replace_subtree(upper_node, node);
                node->set_left(upper_node);
            }
            else if(is_left_son(node))
            {
                upper_node->set_left(node->get_right());
                replace_subtree(upper_node, node);
                node->set_right(upper_node);
            }
        }

        template <typename E>
        void avl_tree<E>::rebalance(avl_tree<E>::node_pointer node)
        {
            while(node->get_height() >= 0)
            {
                node->recount_height();

                int new_balance = node->count_balance();

                if(new_balance >= 2)
                {
                    if(node->get_left()->count_balance() > 0)
                        rotate(node->get_left());
                    else if(node->get_left()->count_balance() < 0)
                    {
                        rotate(node->get_left()->get_right());
                        rotate(node->get_left());
                    }
                }
                else if(new_balance <= -2)
                {
                    if(node->get_right()->count_balance() < 0)
                        rotate(node->get_right());
                    else if(node->get_right()->count_balance() > 0)
                    {
                        rotate(node->get_right()->get_left());
                        rotate(node->get_right());
                    }
                }

                node = node->get_parent();
            }
        }

        // avl_node

        template <typename E>
        class avl_tree<E>::avl_node
        {
        public:
            avl_node()
            {
            }

            virtual ~avl_node() = default;
            avl_node(const avl_node & node) = default;
            avl_node(avl_node && node) = delete;
            avl_node & operator=(const avl_node & node) = default;
            avl_node & operator=(avl_node && node) = delete;

            virtual E & get_element() = 0;

            virtual int get_height() = 0;

            virtual node_pointer get_left() = 0;

            virtual void set_left(node_pointer node) = 0;

            virtual node_pointer get_right() = 0;

            virtual void set_right(node_pointer node) = 0;

            virtual node_pointer get_parent() = 0;

            virtual void set_parent(node_pointer node) = 0;

            /**
             * Kopiowanie obiektu węzła.
             * @return kopia obiektu
             */
            virtual node_pointer clone() = 0;

            /**
             * Wyliczanie balansu wierzchołka.
             * @return wartość balansu
             */
            virtual int count_balance() = 0;

            /**
             * Wyliczanie wysokości wierzchołka.
             */
            virtual void recount_height() = 0;

            /**
             * Wyszukiwanie minimum w poddrzewie.
             * @return węzeł z minimalną wartością w poddrzewie
             */
            virtual node_pointer minimum() = 0;

            /**
             * Wyszukiwanie maksimum w ukorzenionym poddrzewie.
             * @return węzeł z maksymalną wartością w poddrzewie
             */
            virtual node_pointer maximum() = 0;
        };

        // avl_inner_node

        template <typename E>
        class avl_tree<E>::avl_inner_node : public avl_tree<E>::avl_node
        {
        private:
            /// Wartość w węźle.
            E element;

            /// Wysokość węzła.
            int height = 1;

            /// Lewy syn węzła.
            node_pointer left = nullptr;

            /// Prawy syn węzła.
            node_pointer right = nullptr;

            /// Ojciec węzła.
            node_pointer parent = nullptr;

        public:
            avl_inner_node(const E & elem) : avl_tree<E>::avl_node(), element{elem}
            {
            }

            ~avl_inner_node();
            avl_inner_node(const avl_inner_node & node);
            avl_inner_node(avl_inner_node && node) = delete;
            avl_inner_node & operator=(const avl_inner_node & node);
            avl_inner_node & operator=(avl_inner_node && node) = delete;

            E & get_element()
            {
                return element;
            }

            int get_height()
            {
                return this->height;
            }

            node_pointer get_left()
            {
                return this->left;
            }

            void set_left(node_pointer node)
            {
                this->left = node;

                if(this->left != nullptr)
                    this->left->set_parent(this);

                recount_height();
            }

            node_pointer get_right()
            {
                return this->right;
            }

            void set_right(node_pointer node)
            {
                this->right = node;

                if(this->right != nullptr)
                    this->right->set_parent(this);

                recount_height();
            }

            node_pointer get_parent()
            {
                return this->parent;
            }

            void set_parent(node_pointer node)
            {
                this->parent = node;
            }

            node_pointer clone()
            {
                return new avl_inner_node(*this);
            }

            int count_balance();

            void recount_height();

            node_pointer minimum();

            node_pointer maximum();
        };

        template <typename E>
        avl_tree<E>::avl_inner_node::~avl_inner_node()
        {
            if(left != nullptr)
                delete left;

            if(right != nullptr)
                delete right;
        }

        template <typename E>
        avl_tree<E>::avl_inner_node::avl_inner_node(const avl_tree<E>::avl_inner_node & node)
            : avl_tree<E>::avl_node(), element{node.element}, height{node.height}
        {
            this->set_left(node.left->clone());
            this->set_right(node.right->clone());
        }

        template <typename E>
        typename avl_tree<E>::avl_inner_node & avl_tree<E>::avl_inner_node::
            operator=(const avl_tree<E>::avl_inner_node & node)
        {
            this->element = node.element;
            this->height = node.height;
            delete this->left;
            this->set_left(node.left->clone());
            delete this->right;
            this->set_right(node.right->clone());

            return *this;
        }

        template <typename E>
        int avl_tree<E>::avl_inner_node::count_balance()
        {
            int left_height = left == nullptr ? 0 : left->get_height();
            int right_height = right == nullptr ? 0 : right->get_height();

            return left_height - right_height;
        }

        template <typename E>
        void avl_tree<E>::avl_inner_node::recount_height()
        {
            int left_height = left == nullptr ? -1 : left->get_height();
            int right_height = right == nullptr ? -1 : right->get_height();

            height = std::max(left_height, right_height) + 1;
        }

        template <typename E>
        typename avl_tree<E>::node_pointer avl_tree<E>::avl_inner_node::minimum()
        {
            return left == nullptr ? this : left->minimum();
        }

        template <typename E>
        typename avl_tree<E>::node_pointer avl_tree<E>::avl_inner_node::maximum()
        {
            return right == nullptr ? this : right->maximum();
        }

        // avl_root_node

        template <typename E>
        class avl_tree<E>::avl_root_node : public avl_tree<E>::avl_node
        {
        private:
            /// Wewnętrzne wierzchołki.
            node_pointer inner = nullptr;

            /// Ojciec węzła.
            node_pointer parent = nullptr;

        public:
            avl_root_node() : avl_tree<E>::avl_node()
            {
            }

            ~avl_root_node();
            avl_root_node(const avl_root_node & node);
            avl_root_node(avl_root_node && node) = delete;
            avl_root_node & operator=(const avl_root_node & node);
            avl_root_node & operator=(avl_root_node && node) = delete;

            E & get_element()
            {
                throw std::logic_error("Operation not permited.");
            }

            int get_height()
            {
                return -1;
            }

            node_pointer get_left()
            {
                return inner;
            }

            void set_left(node_pointer node)
            {
                inner = node;

                if(inner != nullptr)
                    inner->set_parent(this);
            }

            node_pointer get_right()
            {
                return get_left();
            }

            void set_right(node_pointer node)
            {
                set_left(node);
            }

            node_pointer get_parent()
            {
                return parent;
            }

            void set_parent(node_pointer node)
            {
                parent = node;
            }

            node_pointer clone()
            {
                return new avl_root_node(*this);
            }

            int count_balance()
            {
                return 0;
            }

            void recount_height()
            {
            }

            node_pointer minimum()
            {
                return this;
            }

            node_pointer maximum()
            {
                return this;
            }
        };

        template <typename E>
        avl_tree<E>::avl_root_node::~avl_root_node()
        {
            if(inner != nullptr)
                delete inner;
        }

        template <typename E>
        avl_tree<E>::avl_root_node::avl_root_node(const avl_tree<E>::avl_root_node & node)
            : avl_tree<E>::avl_node()
        {
            this->set_left(node.inner->clone());
        }

        template <typename E>
        typename avl_tree<E>::avl_root_node & avl_tree<E>::avl_root_node::
            operator=(const avl_tree<E>::avl_root_node & node)
        {
            delete this->inner;
            this->set_left(node.inner->clone());

            return *this;
        }

        // avl_iterator

        template <typename E>
        class avl_tree<E>::avl_iterator
        {
        protected:
            /// Aktualny węzeł.
            avl_tree<E>::node_pointer current_node;

        public:
            explicit avl_iterator(avl_tree<E>::node_pointer node) : current_node{node}
            {
            }

            /**
             * Dereferencja iteratora.
             * @return wartość w iteratorze
             */
            E & operator*() const;

            /**
             * Uzyskanie składowej spod iteratora.
             * @return wartość w iteratorze
             */
            E * operator->() const;

            /**
             * Porównanie iteratorów na równość.
             * @return czy iteratory wskazują na ten sam węzeł
             */
            bool operator==(const avl_iterator & it) const;

            /**
             * Porównanie iteratorów na różność.
             * @return czy iteratory wskazują na różne węzły
             */
            bool operator!=(const avl_iterator & it) const;

        protected:
            /**
             * Wyznaczanie następnika węzła w drzewie.
             * @param node węzeł
             * @return węzeł z następną wartością
             */
            avl_tree<E>::node_pointer successor(avl_tree<E>::node_pointer node);

            /**
             * Wyznaczanie poprzednika węzła w drzewie.
             * @param node węzeł
             * @return węzeł z poprzednią wartością
             */
            avl_tree<E>::node_pointer predecessor(avl_tree<E>::node_pointer node);
        };

        template <typename E>
        E & avl_tree<E>::avl_iterator::operator*() const
        {
            return this->current_node->get_element();
        }

        template <typename E>
        E * avl_tree<E>::avl_iterator::operator->() const
        {
            return &this->current_node->get_element();
        }

        template <typename E>
        bool avl_tree<E>::avl_iterator::operator==(const avl_tree<E>::avl_iterator & it) const
        {
            return this->current_node == it.current_node;
        }

        template <typename E>
        bool avl_tree<E>::avl_iterator::operator!=(const avl_tree<E>::avl_iterator & it) const
        {
            return this->current_node != it.current_node;
        }

        template <typename E>
        typename avl_tree<E>::node_pointer
            avl_tree<E>::avl_iterator::successor(avl_tree<E>::node_pointer node)
        {
            avl_tree<E>::node_pointer succ = node;

            if(node->get_right() != nullptr)
                return node->get_right()->minimum();

            while(succ->get_height() >= 0 && succ->get_element() <= node->get_element())
                succ = succ->get_parent();

            return succ;
        }

        template <typename E>
        typename avl_tree<E>::node_pointer
            avl_tree<E>::avl_iterator::predecessor(avl_tree<E>::node_pointer node)
        {
            avl_tree<E>::node_pointer pred = node;

            if(node->get_left() != nullptr)
                return node->get_left()->maximum();

            while(pred->get_height() >= 0 && pred->get_element() >= node->get_element())
                pred = pred->get_parent();

            return pred;
        }

        // avl_fwd_iterator

        template <typename E>
        class avl_tree<E>::avl_fwd_iterator : public avl_tree<E>::avl_iterator
        {
        public:
            explicit avl_fwd_iterator(avl_tree<E>::node_pointer node) : avl_iterator(node)
            {
            }

            avl_fwd_iterator & operator++();

            avl_fwd_iterator operator++(int);

            avl_fwd_iterator & operator--();

            avl_fwd_iterator operator--(int);
        };

        template <typename E>
        typename avl_tree<E>::avl_fwd_iterator & avl_tree<E>::avl_fwd_iterator::operator++()
        {
            if(this->current_node->get_height() >= 0)
                this->current_node = this->successor(this->current_node);

            return *this;
        }

        template <typename E>
        typename avl_tree<E>::avl_fwd_iterator avl_tree<E>::avl_fwd_iterator::operator++(int)
        {
            avl_tree<E>::avl_fwd_iterator result = *this;

            ++(*this);

            return result;
        }

        template <typename E>
        typename avl_tree<E>::avl_fwd_iterator & avl_tree<E>::avl_fwd_iterator::operator--()
        {
            if(this->current_node->get_height() >= 0)
                this->current_node = this->predecessor(this->current_node);
            else
                this->current_node = this->current_node->get_left()->maximum();

            return *this;
        }

        template <typename E>
        typename avl_tree<E>::avl_fwd_iterator avl_tree<E>::avl_fwd_iterator::operator--(int)
        {
            avl_tree<E>::avl_iterator result = *this;

            --(*this);

            return result;
        }

        // avl_rev_iterator

        template <typename E>
        class avl_tree<E>::avl_rev_iterator : public avl_tree<E>::avl_iterator
        {
        public:
            explicit avl_rev_iterator(avl_tree<E>::node_pointer node) : avl_iterator(node)
            {
            }

            avl_rev_iterator & operator++();

            avl_rev_iterator operator++(int);

            avl_rev_iterator & operator--();

            avl_rev_iterator operator--(int);
        };

        template <typename E>
        typename avl_tree<E>::avl_rev_iterator & avl_tree<E>::avl_rev_iterator::operator++()
        {
            if(this->current_node->get_height() >= 0)
                this->current_node = this->predecessor(this->current_node);

            return *this;
        }

        template <typename E>
        typename avl_tree<E>::avl_rev_iterator avl_tree<E>::avl_rev_iterator::operator++(int)
        {
            avl_tree<E>::avl_rev_iterator result = *this;

            ++(*this);

            return result;
        }

        template <typename E>
        typename avl_tree<E>::avl_rev_iterator & avl_tree<E>::avl_rev_iterator::operator--()
        {
            if(this->current_node->get_height() >= 0)
                this->current_node = this->successor(this->current_node);
            else
                this->current_node = this->current_node->get_left()->minimum();

            return *this;
        }

        template <typename E>
        typename avl_tree<E>::avl_rev_iterator avl_tree<E>::avl_rev_iterator::operator--(int)
        {
            avl_tree<E>::avl_rev_iterator result = *this;

            --(*this);

            return result;
        }
    }
}

#endif
