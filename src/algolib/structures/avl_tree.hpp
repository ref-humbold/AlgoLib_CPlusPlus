// DRZEWO AVL
#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <iterator>

namespace algolib
{
    template<typename E>
    class avl_tree
    {
        protected:
        class avl_node;

        public:
        class iterator;
        class reverse_iterator;

        private:
        /** Korzeń drzewa. */
        avl_node * tree = nullptr;

        /** Liczba elementów drzewa. */
        size_t elems = 0;

        avl_tree()
        {
        }

        explicit avl_tree(std::initializer_list<E> init_list);

        ~avl_tree()
        {
            delete tree;
            tree = nullptr;
        }

        avl_tree(const avl_tree & avl) :
            tree{new avl_node(*avl.tree)},
            elems{avl.elems}
        {
        }

        avl_tree(avl_tree && avl) :
            tree{std::move(avl.tree)},
            elems{std::move(avl.elems)}
        {
        }

        avl_tree<E> & operator=(const avl_tree<E> & avl);

        avl_tree<E> & operator=(avl_tree<E> && avl);

        /**
        Ustawia iterator na początek.
        @return iterator na najniższym elemencie
        */
        iterator begin();

        /**
        Ustawia iterator na koniec.
        @return iterator poza drzewem
        */
        iterator end();

        /**
        Ustawia odwrócony iterator na odwrócony początek.
        @return iterator na nawyższym elemencie
        */
        reverse_iterator rbegin();

        /**
        Ustawia odwrócony iterator na odwrócony koniec.
        @return iterator poza drzewem
        */
        reverse_iterator rend();

        /**
        Określanie pustości drzewa.
        @return czy drzewo jest puste
        */
        bool empty() const
        {
            return tree == nullptr;
        }

        /**
        Określanie liczby elementów drzewa.
        @return liczba elemenów drzewa
        */
        size_t size() const
        {
            return elems;
        }

        /**
        Sprawdzanie występowania elementu w drzewie.
        @param element wartość do znalezienia
        @return iterator na wartość w drzewie
        */
        iterator find(const E & element) const;

        /**
        Dodawanie elementu do drzewa.
        @param element wartość do dodania
        @return iterator na nowy element z infromacją o jego dodaniu
        */
        std::pair<iterator, bool> insert(const E & element);

        /**
        Usuwanie elementu z drzewa.
        @param element wartość do usunięcia
        */
        void erase(const E & element);

        /** Usuwanie wszystkich elementów z drzewa. */
        void clear();

        private:
        /**
        Wyszukiwanie ojca węzła z daną wartością.
        @param element wartość do znalezienia
        @return ojciec węzła z wartością
        */
        avl_node * find_node_parent(const E & element) const;

        /**
        Usuwanie elementu z korzenia drzewa.
        @param root korzeń drzewa
        */
        void delete_root(avl_node * root);

        /**
        Usuwanie elementu z węzła wewnętrznego drzewa.
        @param node węzeł do usunięcia
        */
        void delete_node(avl_node * node);

        /**
        Zamiana poddrzewa ukorzenionego w danym węźle.
        @param node węzeł do zamiany
        @param root korzeń nowego poddrzewa
        */
        void replace_subtree(avl_node * node, avl_node * root);

        /**
        Rotowanie węzła wzdłuż krawędzi z jego ojcem.
        @param node węzeł do rotacji
        */
        void rotate(avl_node * node);

        /**
        Przywracanie balansowania na ścieżce od wierzchołka do korzenia.
        @param node wierzchołek początkowy
        */
        void rebalance(avl_node * node);
    };

    template<typename E>
    class avl_tree<E>::avl_node
    {
        private:
        /** Wysokość węzła. */
        int height = 0;

        /** Lewy syn węzła. */
        avl_node * left = nullptr;

        /** Prawy syn węzła. */
        avl_node * right = nullptr;

        public:
        /** Wartość w węźle. */
        E element;

        /** Ojciec węzła. */
        avl_node * parent = nullptr;

        avl_node(const E & elem) : element{elem}
        {
        }

        ~avl_node();

        avl_node(const avl_node & node) :
            height{node.height},
            element{node.element},
            left{new avl_node(*node.left)},
            right{new avl_node(*node.right)}
        {
            left->parent = this;
            right->parent = this;
        }

        avl_node(avl_node && node) :
            height{std::move(node.height)},
            element{std::move(node.element)},
            left{new avl_node( std::move(*node.left) )},
            right{new avl_node( std::move(*node.right) )}
        {
            left->parent = this;
            right->parent = this;
        }

        avl_node & operator=(const avl_node & node);

        avl_node & operator=(avl_node && node);

        /** Getter dla lewego syna węzła. */
        avl_node * get_left()
        {
            return left;
        }

        /**
        Setter dla lewego syna węzła.
        @param node nowy syn węzła
        */
        void set_left(avl_node * node)
        {
            left = node;

            if(left != nullptr)
                left->parent = this;

            count_height();
        }

        /** Getter dla prawego syna węzła. */
        avl_node * get_right()
        {
            return right;
        }

        /**
        Setter dla prawego syna węzła.
        @param node nowy syn węzła
        */
        void set_right(avl_node * node)
        {
            right = node;

            if(right != nullptr)
                right->parent = this;

            count_height();
        }

        /** Getter dla wysokości węzła. */
        int get_height()
        {
            return height;
        }

        /**
        Wyliczanie balansu wierzchołka.
        @return wartość balansu
        */
        int get_balance()
        {
            int left_height = left == nullptr ? 0 : left->height;
            int right_height = right == nullptr ? 0 : right->height;

            return left_height-right_height;
        }

        /**
        Sprawdzanie, czy węzeł jest korzeniem
        @return czy węzeł to korzeń
        */
        bool is_root()
        {
            return parent == nullptr;
        }

        /**
        Sprawdzanie, czy węzeł jest lewym synem
        @return czy węzeł to lewy syn
        */
        bool is_left_son()
        {
            return is_root() ? false : parent->left == this;
        }

        /**
        Sprawdzanie, czy węzeł jest prawym synem
        @return czy węzeł to prawy syn
        */
        bool is_right_son()
        {
            return is_root() ? false : parent->right == this;
        }

        /** Wylicza wysokość wierzchołka. */
        void count_height();

        /**
        Wskazanie poddrzewa, w którym może znaleźć się element.
        @param element poszukiwana wartość
        @return korzeń poddrzewa z elementem
        */
        avl_node * get_subtree(const E & element);

        /**
        Wyszukiwanie minimum w poddrzewie.
        @return węzeł z minimalną wartością w poddrzewie
        */
        avl_node * minimum();

        /**
        Wyszukiwanie maksimum w ukorzenionym poddrzewie.
        @return węzeł z maksymalną wartością w poddrzewie
        */
        avl_node * maximum();

        /**
        Wyznaczanie następnika węzła w drzewie.
        @return węzeł z następną wartością
        */
        avl_node * successor();

        /**
        Wyznaczanie poprzednika węzła w drzewie.
        @return węzeł z poprzednią wartością
        */
        avl_node * predecessor();
    };

    template<typename E>
    class avl_tree<E>::iterator
    {
        private:
        /** Aktualny węzeł. */
        avl_tree<E>::avl_node * current_node;

        public:
        iterator(avl_tree<E>::avl_node * node) : current_node{node}
        {
        }

        /**
        Dereferencja iteratora.
        @return wartość w iteratorze
        */
        E & operator*() const;

        /**
        Prefiksowe przesunięcie iteratora w przód.
        @return nowe położenie iteratora
        */
        iterator & operator++();

        /**
        Postfiksowe przesunięcie iteratora w przód.
        @return stare położenie iteratora
        */
        iterator operator++(int i);

        /**
        Prefiksowe przesunięcie iteratora w tył.
        @return nowe położenie iteratora
        */
        iterator & operator--();

        /**
        Postfiksowe przesunięcie iteratora w tył.
        @return stare położenie iteratora
        */
        iterator operator--(int i);

        /**
        Porównanie iteratorów na równość.
        @return czy iteratory wskazują na ten sam węzeł
        */
        bool operator==(const iterator & it) const;

        /**
        Porównanie iteratorów na różność.
        @return czy iteratory wskazują na różne węzły
        */
        bool operator!=(const iterator & it) const;
    };

    template<typename E>
    class avl_tree<E>::reverse_iterator
    {
        private:
        /** Aktualny węzeł. */
        avl_tree<E>::avl_node * current_node;

        public:
        reverse_iterator(avl_tree<E>::avl_node * node) : current_node{node}
        {
        }

        /**
        Dereferencja iteratora.
        @return wartość w iteratorze
        */
        E & operator*() const;

        /**
        Prefiksowe przesunięcie iteratora w przód.
        @return nowe położenie iteratora
        */
        reverse_iterator & operator++();

        /**
        Postfiksowe przesunięcie iteratora w przód.
        @return stare położenie iteratora
        */
        reverse_iterator operator++(int i);

        /**
        Prefiksowe przesunięcie iteratora w tył.
        @return nowe położenie iteratora
        */
        reverse_iterator & operator--();

        /**
        Postfiksowe przesunięcie iteratora w tył.
        @return stare położenie iteratora
        */
        reverse_iterator operator--(int i);

        /**
        Porównanie iteratorów na równość.
        @return czy iteratory wskazują na ten sam węzeł
        */
        bool operator==(const reverse_iterator & rev_it) const;

        /**
        Porównanie iteratorów na różność.
        @return czy iteratory wskazują na różne węzły
        */
        bool operator!=(const reverse_iterator & rev_it) const;
    };
}

#endif
