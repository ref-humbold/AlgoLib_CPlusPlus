/**!
 * \file mst.hpp
 * \brief ALGORYTMY WYZNACZAJĄCE MINIMALNE DRZEWO SPINAJĄCE
 */
#ifndef MINIMAL_SPANNING_TREE_HPP_
#define MINIMAL_SPANNING_TREE_HPP_

#include <cstdlib>
#include <algorithm>
#include <queue>
#include <tuple>
#include <vector>
#include "algolib/graphs/undirected_graph.hpp"
#include "algolib/structures/disjoint_sets.hpp"

namespace algolib
{
    namespace graphs
    {
        /**!
         * \brief Algorytm Kruskala wyliczający długość MST
         * \param uwgraph graf ważony
         * \return długość minimalnego drzewa spinającego
         */
        double kruskal(const undirected_weighted_simple_graph & uwgraph);

        /**!
         * \brief Algorytm Prima wyliczający długość MST
         * \param uwgraph graf ważony
         * \param source początkowy wierzchołek
         * \return długość minimalnego drzewa spinającego
         */
        double prim(const undirected_weighted_simple_graph & uwgraph, vertex_t source);
    }
}

#endif
