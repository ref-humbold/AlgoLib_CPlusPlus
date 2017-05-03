// ALGORYTMY WYLICZANIA NAJKRÓTSZYCH ŚCIEŻEK W GRAFIE WAŻONYM
#ifndef PATHS_HPP
#define PATHS_HPP

#include <cstdlib>
#include <stdexcept>
#include <exception>
#include <limits>
#include <tuple>
#include <vector>
#include <queue>
#include <algorithm>

#include "graph.hpp"

namespace algolib
{
    namespace graphs
    {
        /**
         * Algorytm Bellmana-Forda.
         * @param wgraph graf ważony
         * @param source wierzchołek początkowy
         * @return lista odległości wierzchołków
         */
        std::vector<weight_type> bellman_ford(const directed_weighted_graph & wgraph, vertex_type source);

        /**
         * Algorytm Dijkstry.
         * @param wgraph graf ważony
         * @param source wierzchołek początkowy
         * @return lista odległości wierzchołków
         */
        std::vector<weight_type> dijkstra(const weighted_graph & wgraph, vertex_type source);

        /**
         * Algorytm Floyda-Warshalla.
         * @param wgraph graf ważony
         * @return macierz odległości
         */
        std::vector<std::vector<weight_type>> floyd_warshall(const directed_weighted_graph & wgraph);
    }
}

#endif
