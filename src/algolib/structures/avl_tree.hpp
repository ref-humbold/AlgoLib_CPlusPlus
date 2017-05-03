// DRZEWO AVL
#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <cstdlib>
#include <cmath>
#include <memory>
#include <algorithm>
#include <iterator>
#include <initializer_list>

namespace algolib
{
    namespace structures
    {
        template<typename E>
        class avl_tree
        {
        protected:
            class avl_node;
            class avl_iterator;
            class avl_rev_iterator;

            using node = avl_node;
            using node_pointer = node *;
        public:
            using iterator = avl_iterator;
            using reverse_iterator = avl_rev_iterator;

        private:
            /** Korzeń drzewa. */
            node_pointer tree = nullptr;

            /** Liczba elementów drzewa. */
            size_t elems = 0;

        public:
            avl_tree()
            {
            }

            avl_tree(std::initializer_list<E> init_list);

            ~avl_tree()
            {
                delete tree;
            }

            avl_tree(const avl_tree & avl) :
                tree{new node(*avl.tree)},
                elems{avl.elems}
            {
            }

            avl_tree(avl_tree && avl) :
                elems{std::move(avl.elems)}
            {
                std::swap(this->tree, avl.tree);
            }

            avl_tree<E> & operator =(const avl_tree<E> & avl);
            avl_tree<E> & operator =(avl_tree<E> && avl);

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

            /** Usuwanie wszystkich elementów z drzewa. */
            void clear();

        private:
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
             * @param node węzeł do zamiany
             * @param root korzeń nowego poddrzewa
             */
            void replace_subtree(node_pointer node, node_pointer root);

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

        template<typename E>
        class avl_tree<E>::avl_node
        {
        public:
            /** Wartość w węźle. */
            E element;

        private:
            /** Wysokość węzła. */
            int height = 0;

            /** Lewy syn węzła. */
            node_pointer left = nullptr;

            /** Prawy syn węzła. */
            node_pointer right = nullptr;

            /** Ojciec węzła. */
            node_pointer parent = nullptr;

        public:
            avl_node(const E & elem) :
                element{elem}
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

                count_height();
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

                count_height();
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
            int get_balance()
            {
                int left_height = left == nullptr ? 0 : left->height;
                int right_height = right == nullptr ? 0 : right->height;

                return left_height-right_height;
            }

            /**
             * Sprawdzanie, czy węzeł jest korzeniem.
             * @return czy węzeł to korzeń
             */
            bool is_root()
            {
                return parent == nullptr;
            }

            /**
             * Sprawdzanie, czy węzeł jest lewym synem.
             * @return czy węzeł to lewy syn
             */
            bool is_left_son()
            {
                return is_root() ? false : parent->left == this;
            }

            /**
             * Sprawdzanie, czy węzeł jest prawym synem.
             * @return czy węzeł to prawy syn
             */
            bool is_right_son()
            {
                return is_root() ? false : parent->right == this;
            }

            /** Wylicza wysokość wierzchołka. */
            void count_height();

            /**
             * Wskazanie poddrzewa, w którym może znaleźć się element.
             * @param element poszukiwana wartość
             * @return korzeń poddrzewa z elementem
             */
            node_pointer get_subtree(const E & element);

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

            /**
             * Wyznaczanie następnika węzła w drzewie.
             * @return węzeł z następną wartością
             */
            node_pointer successor();

            /**
             * Wyznaczanie poprzednika węzła w drzewie.
             * @return węzeł z poprzednią wartością
             */
            node_pointer predecessor();
        };

        template<typename E>
        class avl_tree<E>::avl_iterator
        {
        private:
            /** Aktualny węzeł. */
            avl_tree<E>::node_pointer current_node;

        public:
            avl_iterator(avl_tree<E>::node_pointer node) :
                current_node{node}
            {
            }

            /**
             * Dereferencja iteratora.
             * @return wartość w iteratorze
             */
            E & operator *() const;

            /**
             * Prefiksowe przesunięcie iteratora w przód.
             * @return nowe położenie iteratora
             */
            avl_iterator & operator ++();

            /**
             * Postfiksowe przesunięcie iteratora w przód.
             * @return stare położenie iteratora
             */
            avl_iterator operator ++(int i);

            /**
             * Prefiksowe przesunięcie iteratora w tył.
             * @return nowe położenie iteratora
             */
            avl_iterator & operator --();

            /**
             * Postfiksowe przesunięcie iteratora w tył.
             * @return stare położenie iteratora
             */
            avl_iterator operator --(int i);

            /**
             * Porównanie iteratorów na równość.
             * @return czy iteratory wskazują na ten sam węzeł
             */
            bool operator ==(const iterator & it) const;

            /**
             * Porównanie iteratorów na różność.
             * @return czy iteratory wskazują na różne węzły
             */
            bool operator !=(const iterator & it) const;
        };

        template<typename E>
        class avl_tree<E>::avl_rev_iterator
        {
        private:
            /** Aktualny węzeł. */
            avl_tree<E>::node_pointer current_node;

        public:
            avl_rev_iterator(avl_tree<E>::node_pointer node) :
                current_node{node}
            {
            }

            /**
             * Dereferencja iteratora.
             * @return wartość w iteratorze
             */
            E & operator *() const;

            /**
             * Prefiksowe przesunięcie iteratora w przód.
             * @return nowe położenie iteratora
             */
            avl_rev_iterator & operator ++();

            /**
             * Postfiksowe przesunięcie iteratora w przód.
             * @return stare położenie iteratora
             */
            avl_rev_iterator operator ++(int i);

            /**
             * Prefiksowe przesunięcie iteratora w tył.
             * @return nowe położenie iteratora
             */
            avl_rev_iterator & operator --();

            /**
             * Postfiksowe przesunięcie iteratora w tył.
             * @return stare położenie iteratora
             */
            avl_rev_iterator operator --(int i);

            /**
             * Porównanie iteratorów na równość.
             * @return czy iteratory wskazują na ten sam węzeł
             */
            bool operator ==(const avl_rev_iterator & rev_it) const;

            /**
             * Porównanie iteratorów na różność.
             * @return czy iteratory wskazują na różne węzły
             */
            bool operator !=(const avl_rev_iterator & rev_it) const;
        };
    }
}

#endif
