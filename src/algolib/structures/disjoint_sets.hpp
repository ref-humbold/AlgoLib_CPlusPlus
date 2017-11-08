/**
 * @file disjoint_sets.hpp
 * STRUKTURA ZBIORÓW ROZŁĄCZNYCH UNION-FIND
 */
#ifndef DISJOINT_SETS_HPP
#define DISJOINT_SETS_HPP

#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <initializer_list>
#include <map>
#include <set>
#include <vector>

namespace algolib
{
    namespace structures
    {
        template <typename E>
        class disjoint_sets
        {
        private:
            /// Mapa reprezentantów elementów.
            std::map<E, E> represents;

            /// Liczba elementów
            size_t elems;

        public:
            explicit disjoint_sets(std::initializer_list<E> universe) : elems{universe.size()}
            {
                for(E e : universe)
                    represents.insert(std::make_pair(e, e));
            }

            explicit disjoint_sets(std::vector<E> universe) : elems{universe.size()}
            {
                for(E e : universe)
                    represents.insert(std::make_pair(e, e));
            }

            ~disjoint_sets() = default;
            disjoint_sets(const disjoint_sets & ds) = default;
            disjoint_sets(disjoint_sets && ds) = default;
            disjoint_sets & operator=(const disjoint_sets & ds) = default;
            disjoint_sets & operator=(disjoint_sets && ds) = default;

            /**
             * @return liczba zbiorów
             */
            size_t size() const
            {
                return elems;
            }

            /**
             * Należenie do dowolnego zbioru.
             * @param element element
             * @return czy element w jednym ze zbiorów
             */
            bool contains(const E & element) const;

            /**
             * Tworzenie nowego zbioru jednoelementowego.
             * @param element nowy element
             */
            void make_set(const E & element);

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
        };

        template <typename E>
        bool disjoint_sets<E>::contains(const E & element) const
        {
            return represents.find(element) != represents.end();
        }

        template <typename E>
        void disjoint_sets<E>::make_set(const E & element)
        {
            if(contains(element))
                throw std::invalid_argument("Value already present.");

            represents.emplace(element, element);
            elems++;
        }

        template <typename E>
        const E & disjoint_sets<E>::find_set(const E & element)
        {
            if(represents.at(element) != element)
                represents[element] = find_set(represents[element]);

            return represents[element];
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
