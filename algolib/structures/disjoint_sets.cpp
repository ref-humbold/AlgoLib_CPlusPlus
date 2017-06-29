// STRUKTURA ZBIORÓW ROZŁĄCZNYCH UNION-FIND
#include "disjoint_sets.hpp"

namespace alst = algolib::structures;

template <typename E>
size_t alst::disjoint_sets<E>::size()
{
    std::set<E> reprs;

    for(auto e : represents)
        reprs.insert(find_set(e));

    return reprs.size();
}

template <typename E>
bool alst::disjoint_sets<E>::contains(E element)
{
    return represents.find(element) != represents.end();
}

template <typename E>
void alst::disjoint_sets<E>::make_set(E element)
{
    if(!contains(element))
        represents.emplace(element, element);
}

template <typename E>
E alst::disjoint_sets<E>::find_set(E element)
{
    if(represents[element] != element)
        represents[element] = find_set(represents[element]);

    return represents[element];
}

template <typename E>
void alst::disjoint_sets<E>::union_set(E element1, E element2)
{
    if(!is_same_set(element1, element2))
        represents[find_set(element1)] = find_set(element2);
}

template <typename E>
bool alst::disjoint_sets<E>::is_same_set(E element1, E element2) const
{
    return find_set(element1) == find_set(element2);
}
