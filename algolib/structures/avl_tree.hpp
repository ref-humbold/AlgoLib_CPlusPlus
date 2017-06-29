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
    }
}

#endif
