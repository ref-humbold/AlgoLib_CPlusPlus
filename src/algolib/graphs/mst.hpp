// ALGORYTMY WYZNACZAJĄCE MINIMALNE DRZEWO SPINAJĄCE
#ifndef MST_HPP
#define MST_HPP

#include <cstdlib>
#include <tuple>
#include <vector>
#include <queue>
#include <algorithm>

#include "../structures/disjoint_sets.hpp"
#include "graph.hpp"

namespace algolib
{
    /**
    Algorytm Kruskala wyliczający długość MST.
    @param wgraph graf ważony
    @return długość minimalnego drzewa spinającego
    */
    double kruskal(const weighted_graph & wgraph);

    /**
    Algorytm Prima wyliczający długość MST.
    @param wgraph graf ważony
    @param source początkowy wierzchołek
    @return długość minimalnego drzewa spinającego
    */
    double prim(const weighted_graph & wgraph, int source);
};

#endif
