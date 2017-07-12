/**
 * @file mst.hpp
 * ALGORYTMY WYZNACZAJĄCE MINIMALNE DRZEWO SPINAJĄCE
 */
#ifndef MST_HPP
#define MST_HPP

#include <cstdlib>
#include <algorithm>
#include <queue>
#include <tuple>
#include <vector>

#include "../structures/disjoint_sets.hpp"
#include "undirected_graph.hpp"

namespace algolib
{
    namespace graphs
    {
        /**
         * Algorytm Kruskala wyliczający długość MST.
         * @param uwgraph graf ważony
         * @return długość minimalnego drzewa spinającego
         */
        double kruskal(const undirected_weighted_graph & uwgraph);

        /**
         * Algorytm Prima wyliczający długość MST.
         * @param uwgraph graf ważony
         * @param source początkowy wierzchołek
         * @return długość minimalnego drzewa spinającego
         */
        double prim(const undirected_weighted_graph & uwgraph, vertex_t source);
    }
}

#endif
