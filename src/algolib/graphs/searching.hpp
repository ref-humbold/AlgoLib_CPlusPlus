// ALGORYTMY PRZESZUKIWANIA GRAFU
#ifndef SEARCHING_HPP
#define SEARCHING_HPP

#include <cstdlib>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

#include "graph.hpp"

namespace detail
{
    /**
    Krok rekurencyjnego DFS.
    @param graph graf
    @param vertex aktualny wierzchołek
    @param is_visited lista odwiedzonych wierzchołków
    */
    void dfsR_step(const algolib::graphs::graph & gr, vertex_t vertex,
        std::vector<bool> & is_visited);
}

namespace algolib
{
    namespace graphs
    {
        /**
        Algorytm BFS.
        @param gr graf
        @param root wierzchołek początkowy
        @return lista odwiedzonych wierzchołków
        */
        std::vector<bool> bfs(const graph & gr, vertex_t root);

        /**
        Iteracyjny algorytm DFS.
        @param gr graf
        @param root wierzchołek początkowy
        @return lista odwiedzonych wierzchołków
        */
        std::vector<bool> dfsI(const graph & gr, vertex_t root);

        /**
        Rekurencyjny algorytm DFS.
        @param gr graf
        @param root wierzchołek początkowy
        @return lista odwiedzonych wierzchołków
        */
        std::vector<bool> dfsR(const graph & gr, vertex_t root);
    }
}

#endif
