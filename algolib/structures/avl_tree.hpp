/**
 * @file avl_tree.h
 * DRZEWO AVL
 */
#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <cstdlib>
#include <cmath>
#include <memory>
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
            class avl_node_element;
            class avl_node_null;

            class avl_iterator;
            class avl_fwd_iterator;
            class avl_rev_iterator;

            using node = avl_node;
            using node_pointer = node *;

        public:
            using iterator = avl_fwd_iterator;
            using reverse_iterator = avl_rev_iterator;

        private:
            /// Korzeń drzewa.
            node_pointer tree = nullptr;

            ///  Liczba elementów drzewa.
            size_t elems = 0;

        public:
            avl_tree()
            {
            }

            explicit avl_tree(std::initializer_list<E> init_list)
                : tree{nullptr}, elems{init_list.size()}
            {
                for(auto i : init_list)
                    insert(i);
            }

            ~avl_tree()
            {
                delete tree;
            }

            avl_tree(const avl_tree & avl) : tree{new node(*avl.tree)}, elems{avl.elems}
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
                return tree == nullptr;
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
             * Sprawdzanie, czy węzeł jest korzeniem.
             * @param node węzeł
             * @return czy węzeł to korzeń
             */
            bool is_root(node_pointer node)
            {
                return node->parent == nullptr;
            }

            /**
             * Sprawdzanie, czy węzeł jest lewym synem.
             * @param node węzeł
             * @return czy węzeł to lewy syn
             */
            bool is_left_son(node_pointer node)
            {
                return is_root(node) ? false : node->parent->left == this;
            }

            /**
             * Sprawdzanie, czy węzeł jest prawym synem.
             * @param node węzeł
             * @return czy węzeł to prawy syn
             */
            bool is_right_son(node_pointer node)
            {
                return is_root(node) ? false : node->parent->right == this;
            }

            /**
             * Wskazanie poddrzewa, w którym może znaleźć się element.
             * @param node węzeł
             * @param element element
             * @return korzeń poddrzewa z elementem
             */
            node_pointer get_subtree(node_pointer node, const E & element);

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
            this->tree = new node(*avl.tree);
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
            return iterator(tree->minimum());
        }

        template <typename E>
        typename avl_tree<E>::iterator avl_tree<E>::end() const
        {
            return iterator(nullptr);
        }

        template <typename E>
        typename avl_tree<E>::reverse_iterator avl_tree<E>::rbegin() const
        {
            return reverse_iterator(tree->maximum());
        }

        template <typename E>
        typename avl_tree<E>::reverse_iterator avl_tree<E>::rend() const
        {
            return reverse_iterator(nullptr);
        }

        template <typename E>
        typename avl_tree<E>::iterator avl_tree<E>::find(const E & element) const
        {
            if(tree == nullptr)
                return end();

            avl_tree<E>::node_pointer node_parent = find_node_parent(element);

            if(node_parent == nullptr)
                return iterator(tree);

            avl_tree<E>::node_pointer the_node = node_parent->get_subtree(element);

            if(the_node == nullptr)
                return end();

            return iterator(the_node);
        }

        template <typename E>
        std::pair<typename avl_tree<E>::iterator, bool> avl_tree<E>::insert(const E & element)
        {
            avl_tree<E>::node_pointer node_parent = find_node_parent(element);
            avl_tree<E>::node_pointer the_node =
                node_parent == nullptr ? tree : node_parent->get_subtree(element);

            if(the_node != nullptr)
                return std::make_pair(iterator(the_node), false);

            avl_tree<E>::node_pointer new_node = new node(element);

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

        template <typename E>
        void avl_tree<E>::erase(const E & element)
        {
            avl_tree<E>::node_pointer node_parent = find_node_parent(element);
            avl_tree<E>::node_pointer the_node =
                node_parent == nullptr ? tree : node_parent->get_subtree(element);

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
            delete tree;
            elems = 0;
        }

        template <typename E>
        typename avl_tree<E>::node_pointer avl_tree<E>::get_subtree(avl_tree<E>::node_pointer node,
                                                                    const E & element)
        {
            if(element == node->element)
                return node;
            else if(element < node->element)
                return node->left;
            else
                return node->right;
        }

        template <typename E>
        typename avl_tree<E>::node_pointer avl_tree<E>::find_node_parent(const E & element) const
        {
            typename avl_tree<E>::node_pointer tree_iter = tree;
            typename avl_tree<E>::node_pointer iter_parent = nullptr;

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

        template <typename E>
        void avl_tree<E>::delete_root(avl_tree<E>::node_pointer root)
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

        template <typename E>
        void avl_tree<E>::delete_node(avl_tree<E>::node_pointer node)
        {
            if(node->get_left() != nullptr && node->get_right() != nullptr)
            {
                avl_tree<E>::node_pointer succ = node->get_right()->minimum();

                std::swap(succ->element, node->element);
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
            if(is_root(node1))
            {
                tree = node2;
                node2->set_parent(nullptr);
            }
            else if(is_left_son(node1))
                node1->get_parent()->set_left(node2);
            else if(is_right_son(node1))
                node1->get_parent()->set_right(node2);

            node1->set_parent(nullptr);
        }

        template <typename E>
        void avl_tree<E>::rotate(avl_tree<E>::node_pointer node)
        {
            if(is_root(node))
                return;

            avl_tree<E>::node_pointer upper_node = node->get_parent();

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

        template <typename E>
        void avl_tree<E>::rebalance(avl_tree<E>::node_pointer node)
        {
            while(node != nullptr)
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
            /// Wartość w węźle.
            E element;

        private:
            /// Wysokość węzła.
            int height = 0;

            /// Lewy syn węzła.
            node_pointer left = nullptr;

            /// Prawy syn węzła.
            node_pointer right = nullptr;

            /// Ojciec węzła.
            node_pointer parent = nullptr;

        public:
            avl_node(const E & elem) : element{elem}
            {
            }

            ~avl_node();
            avl_node(const avl_node & node);
            avl_node(avl_node && node) = delete;
            avl_node & operator=(const avl_node & node);
            avl_node & operator=(avl_node && node) = delete;

            node_pointer get_left()
            {
                return left;
            }

            void set_left(node_pointer node)
            {
                left = node;

                if(left != nullptr)
                    left->parent = this;

                recount_height();
            }

            node_pointer get_right()
            {
                return right;
            }

            void set_right(node_pointer node)
            {
                right = node;

                if(right != nullptr)
                    right->parent = this;

                recount_height();
            }

            node_pointer get_parent()
            {
                return parent;
            }

            void set_parent(node_pointer node)
            {
                parent = node;
            }

            /**
             * Wyliczanie balansu wierzchołka.
             * @return wartość balansu
             */
            int count_balance();

            /**
             * Wyliczanie wysokości wierzchołka.
             */
            void recount_height();

            /**
             * Wyszukiwanie minimum w poddrzewie.
             * @return węzeł z minimalną wartością w poddrzewie
             */
            node_pointer minimum();

            /**
             * Wyszukiwanie maksimum w ukorzenionym poddrzewie.
             * @return węzeł z maksymalną wartością w poddrzewie
             */
            node_pointer maximum();
        };

        template <typename E>
        avl_tree<E>::avl_node::~avl_node()
        {
            if(left != nullptr)
                delete left;

            if(right != nullptr)
                delete right;
        }

        template <typename E>
        avl_tree<E>::avl_node::avl_node(const avl_tree<E>::avl_node & node)
            : element{node.element}, height{node.height}
        {
            this->set_left(new avl_node(*node.left));
            this->set_right(new avl_node(*node.right));
        }

        template <typename E>
        typename avl_tree<E>::avl_node & avl_tree<E>::avl_node::
            operator=(const avl_tree<E>::avl_node & node)
        {
            this->element = node.element;
            this->height = node.height;
            delete this->left;
            this->set_left(new avl_node(*node.left));
            delete this->right;
            this->set_right(new avl_node(*node.right));

            return *this;
        }

        template <typename E>
        int avl_tree<E>::avl_node::count_balance()
        {
            int left_height = left == nullptr ? 0 : left->height;
            int right_height = right == nullptr ? 0 : right->height;

            return left_height - right_height;
        }

        template <typename E>
        void avl_tree<E>::avl_node::recount_height()
        {
            int left_height = left == nullptr ? -1 : left->height;
            int right_height = right == nullptr ? -1 : right->height;

            height = std::max(left_height, right_height) + 1;
        }

        template <typename E>
        typename avl_tree<E>::node_pointer avl_tree<E>::avl_node::minimum()
        {
            return left == nullptr ? this : left->minimum();
        }

        template <typename E>
        typename avl_tree<E>::node_pointer avl_tree<E>::avl_node::maximum()
        {
            return right == nullptr ? this : right->maximum();
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
             * Prefiksowe przesunięcie iteratora w przód.
             * @return nowe położenie iteratora
             */
            virtual avl_iterator & operator++() = 0;

            /**
             * Postfiksowe przesunięcie iteratora w przód.
             * @return stare położenie iteratora
             */
            virtual avl_iterator & operator++(int) = 0;

            /**
             * Prefiksowe przesunięcie iteratora w tył.
             * @return nowe położenie iteratora
             */
            virtual avl_iterator & operator--() = 0;

            /**
             * Postfiksowe przesunięcie iteratora w tył.
             * @return stare położenie iteratora
             */
            virtual avl_iterator & operator--(int) = 0;

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
            return this->current_node->element;
        }

        template <typename E>
        E * avl_tree<E>::avl_iterator::operator->() const
        {
            return &this->current_node->element;
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

            while(succ->height >= 0 && succ->element <= node->element)
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

            while(pred->height >= 0 && pred->element >= node->element)
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

            avl_fwd_iterator & operator++() override;

            avl_fwd_iterator operator++(int)override;

            avl_fwd_iterator & operator--() override;

            avl_fwd_iterator operator--(int)override;
        };

        template <typename E>
        typename avl_tree<E>::avl_fwd_iterator & avl_tree<E>::avl_fwd_iterator::operator++()
        {
            if(this->current_node != nullptr)
                this->current_node = successor(this->current_node);

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
            if(this->current_node != nullptr)
                this->current_node = predecessor(this->current_node);

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

            avl_rev_iterator & operator++() override;

            avl_rev_iterator operator++(int)override;

            avl_rev_iterator & operator--() override;

            avl_rev_iterator operator--(int)override;
        };

        template <typename E>
        typename avl_tree<E>::avl_rev_iterator & avl_tree<E>::avl_rev_iterator::operator++()
        {
            if(this->current_node != nullptr)
                this->current_node = predecessor(this->current_node);

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
            if(this->current_node != nullptr)
                this->current_node = successor(this->current_node);

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
