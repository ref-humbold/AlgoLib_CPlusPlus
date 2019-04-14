/**
 * @file disjoint_sets.hpp
 * @brief Disjoint sets structure (union-find)
 */
#ifndef _DISJOINT_SETS_HPP_
#define _DISJOINT_SETS_HPP_

#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <initializer_list>
#include <set>
#include <unordered_map>
#include <vector>

namespace algolib
{
    namespace structures
    {
        template <typename E>
        class disjoint_sets
        {
        public:
            disjoint_sets() : elems{0}
            {
            }

            explicit disjoint_sets(std::initializer_list<E> universe) : elems{universe.size()}
            {
                for(E e : universe)
                    represents.emplace(e, e);
            }

            template <typename InputIterator>
            disjoint_sets(InputIterator first, InputIterator last);

            ~disjoint_sets() = default;
            disjoint_sets(const disjoint_sets & ds) = default;
            disjoint_sets(disjoint_sets && ds) = default;
            disjoint_sets & operator=(const disjoint_sets & ds) = default;
            disjoint_sets & operator=(disjoint_sets && ds) = default;

            /// @return liczba zbiorów
            size_t size() const
            {
                return elems;
            }

            /**
             * Sprawdzanie należenia do dowolnego zbioru.
             * @param element element
             * @return czy element w jednym ze zbiorów
             */
            bool contains(const E & element) const;

            /**
             * Dodawanie nowego elementu jako singleton.
             * @param element nowy element
             */
            void insert(const E & element);

            /**
             * Dodawanie nowych elementów jako singletony.
             * @param element nowy element
             */
            template <typename InputIterator>
            void insert(InputIterator first, InputIterator last);

            /**
             * Ustalanie reprezentanta zbioru.
             * @param element element ze zbioru
             * @return reprezentant elementu
             */
            const E & find_set(const E & element);

            /**
             * Ustalanie reprezentanta zbioru.
             * @param element element ze zbioru
             * @return reprezentant elementu
             */
            const E & find_set(const E & element) const;

            /**
             * Ustalanie reprezentanta zbioru.
             * @param element element ze zbioru
             * @return reprezentant elementu
             */
            const E & operator[](const E & element)
            {
                return find_set(element);
            }

            /**
             * Ustalanie reprezentanta zbioru.
             * @param element element ze zbioru
             * @return reprezentant elementu
             */
            const E & operator[](const E & element) const
            {
                return find_set(element);
            }

            /**
             * Scalanie dwóch zbiorów.
             * @param element1 element pierwszego zbioru
             * @param element2 element drugiego zbioru
             */
            void union_set(const E & element1, const E & element2);

            /**
             * Sprawdzanie, czy elementy należą do tego samego zbioru.
             * @param element1 element pierwszego zbioru
             * @param element2 element drugiego zbioru
             * @return czy elementy znajdują się w różnych składowych
             */
            bool is_same_set(const E & element1, const E & element2);

            /**
             * Sprawdzanie, czy elementy należą do tego samego zbioru.
             * @param element1 element pierwszego zbioru
             * @param element2 element drugiego zbioru
             * @return czy elementy znajdują się w różnych składowych
             */
            bool is_same_set(const E & element1, const E & element2) const;

        private:
            /// Mapa reprezentantów elementów.
            std::unordered_map<E, E> represents;

            /// Liczba elementów
            size_t elems;
        };

        template <typename E>
        template <typename InputIterator>
        disjoint_sets<E>::disjoint_sets(InputIterator first, InputIterator last) : elems{0}
        {
            for(InputIterator it = first; it != last; ++it)
            {
                represents.emplace(*it, *it);
                ++elems;
            }
        }

        template <typename E>
        bool disjoint_sets<E>::contains(const E & element) const
        {
            return represents.find(element) != represents.end();
        }

        template <typename E>
        void disjoint_sets<E>::insert(const E & element)
        {
            if(contains(element))
                throw std::invalid_argument("Value already present");

            represents.emplace(element, element);
            elems++;
        }

        template <typename E>
        template <typename InputIterator>
        void disjoint_sets<E>::insert(InputIterator first, InputIterator last)
        {
            for(InputIterator it = first; it != last; ++it)
                insert(*it);
        }

        template <typename E>
        const E & disjoint_sets<E>::find_set(const E & element)
        {
            if(represents.at(element) != element)
                represents[element] = find_set(represents[element]);

            return represents.at(element);
        }

        template <typename E>
        const E & disjoint_sets<E>::find_set(const E & element) const
        {
            return represents.at(element) == element ? element : find_set(represents.at(element));
        }

        template <typename E>
        void disjoint_sets<E>::union_set(const E & element1, const E & element2)
        {
            if(!is_same_set(element1, element2))
            {
                represents[find_set(element1)] = find_set(element2);
                elems--;
            }
        }

        template <typename E>
        bool disjoint_sets<E>::is_same_set(const E & element1, const E & element2)
        {
            return find_set(element1) == find_set(element2);
        }

        template <typename E>
        bool disjoint_sets<E>::is_same_set(const E & element1, const E & element2) const
        {
            return find_set(element1) == find_set(element2);
        }
    }
}

#endif
