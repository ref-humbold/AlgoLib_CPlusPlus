// STRUKTURA ZBIORÓW ROZŁĄCZNYCH UNION-FIND
#include "disjoint_sets.hpp"

template<typename E>
E algolib::structures::disjoint_sets<E>::find_set(E element)
{
    if(represents[element] != element)
        represents[element] = find_set(represents[element]);

    return represents[element];
}

template<typename E>
void algolib::structures::disjoint_sets<E>::union_set(E element1, E element2)
{
    represents[find_set(element1)] = find_set(element2);
}

template<typename E>
bool algolib::structures::disjoint_sets<E>::is_set_different(E element1, E element2) const
{
    return find_set(element1) != find_set(element2);
}

