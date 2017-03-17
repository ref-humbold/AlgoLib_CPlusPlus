// STRUKTURA ZBIORÓW ROZŁĄCZNYCH UNION-FIND
#ifndef DISJOINT_SETS_HPP
#define DISJOINT_SETS_HPP

#include <cstdlib>
#include <initializer_list>
#include <vector>
#include <map>
#include <algorithm>

namespace algolib
{
    template<typename E>
    class disjoint_sets
    {
        private:
        /** mapa reprezentantów elementów */
        std::map<E, E> represents;

        public:
        explicit disjoint_sets(std::initializer_list<E> universe)
        {
            for(E e : universe)
                represents.insert( std::make_pair(e, e) );
        }

        explicit disjoint_sets(std::vector<E> universe)
        {
            for(E e : universe)
                represents.insert( std::make_pair(e, e) );
        }

        ~disjoint_sets() = default;
        disjoint_sets(const disjoint_sets & ds) = default;
        disjoint_sets(disjoint_sets && ds) = default;
        disjoint_sets& operator=(const disjoint_sets & ds) = default;
        disjoint_sets& operator=(disjoint_sets && ds) = default;

        /**
        Ustala reprezentanta składowej.
        @param element element ze składowej
        @return reprezentant elementu
        */
        E find_set(E element);

        /**
        Scala dwie składowe.
        @param element1 element pierwszej składowej
        @param element2 element drugiej składowej
        */
        void union_set(E element1, E element2);

        /**
        Sprawdza, czy elementy są w różnych składowych.
        @param element1 element pierwszej składowej
        @param element2 element drugiej składowej
        @return czy elementy znajdują się w różnych składowych
        */
        bool is_set_different(E element1, E element2) const;
    };
}

#endif

