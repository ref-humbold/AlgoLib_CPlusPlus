/**!
 * \file paths.hpp
 * \brief ALGORYTMY WYLICZANIA NAJKRÓTSZYCH ŚCIEŻEK W GRAFIE WAŻONYM
 */
#ifndef PATHS_HPP_
#define PATHS_HPP_

#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <queue>
#include <tuple>
#include <vector>
#include "algolib/graphs/directed_graph.hpp"

namespace algolib
{
    namespace graphs
    {
        /**!
         * \brief Algorytm Bellmana-Forda
         * \param wgraph graf ważony
         * \param source wierzchołek początkowy
         * \return lista odległości wierzchołków
         */
        std::vector<weight_t> bellman_ford(const directed_weighted_simple_graph & diwgraph,
                                           vertex_t source);

        /**!
         * \brief Algorytm Dijkstry
         * \param wgraph graf ważony
         * \param source wierzchołek początkowy
         * \return lista odległości wierzchołków
         */
        std::vector<weight_t> dijkstra(const weighted_graph & wgraph, vertex_t source);

        /**!
         * \brief Algorytm Floyda-Warshalla
         * \param wgraph graf ważony
         * \return macierz odległości
         */
        std::vector<std::vector<weight_t>>
                floyd_warshall(const directed_weighted_simple_graph & diwgraph);
    }
}

#endif
