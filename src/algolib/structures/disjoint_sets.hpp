/**
 * @file disjoint_sets.hpp
 * STRUKTURA ZBIORÓW ROZŁĄCZNYCH UNION-FIND
 */
#ifndef DISJOINT_SETS_HPP
#define DISJOINT_SETS_HPP

#include <cstdlib>
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

        public:
            explicit disjoint_sets(std::initializer_list<E> universe)
            {
                for(E e : universe)
                    represents.insert(std::make_pair(e, e));
            }

            explicit disjoint_sets(std::vector<E> universe)
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
            size_t size();

            /**
             * Należenie do dowolnego zbioru.
             * @param element element
             * @return czy element w jednym ze zbiorów
             */
            bool contains(E element);

            /**
             * Tworzenie nowego zbioru jednoelementowego.
             * @param element nowy element
             */
            void make_set(E element);

            /**
             * Ustalanie reprezentanta zbioru.
             * @param element element ze zbioru
             * @return reprezentant elementu
             */
            E find_set(E element);

            /**
             * Scalanie dwóch zbiorów.
             * @param element1 element pierwszego zbioru
             * @param element2 element drugiego zbioru
             */
            void union_set(E element1, E element2);

            /**
             * Sprawdzanie, czy elementy należą do tego samego zbioru.
             * @param element1 element pierwszego zbioru
             * @param element2 element drugiego zbioru
             * @return czy elementy znajdują się w różnych składowych
             */
            bool is_same_set(E element1, E element2) const;
        };
    }
}

#endif
