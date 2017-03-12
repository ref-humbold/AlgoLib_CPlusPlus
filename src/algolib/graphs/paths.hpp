// ALGORYTMY WYLICZANIA NAJKRÓTSZYCH ŚCIEŻEK W GRAFIE WAŻONYM
#ifdef PATHS_HPP
#define PATHS_HPP

#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <tuple>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

#include "graph.hpp"

namespace algolib
{
    namespace detail
    {
        constexpr double INF = std::numeric_limits<double>::infinity();
    }

    /**
    Algorytm Belllmana-Forda
    @param wgraph graf ważony
    @param source wierzchołek początkowy
    @return lista odległości wierzchołków
    */
    std::vector<double> bellman_ford(weighted_graph wgraph, int source);

    /**
    Algorytm Dijkstry.
    @param wgraph graf ważony
    @param source wierzchołek początkowy
    @return lista odległości wierzchołków
    */
    std::vector<double> dijkstra(weighted_graph wgraph, int source);

    /**
    Algorytm Floyda-Warshalla.
    @param wgraph graf ważony
    @return macierz odległości
    */
    std::vector< std::vector<double> > floyd_warshall(weighted_graph wgraph);
}

#endif
