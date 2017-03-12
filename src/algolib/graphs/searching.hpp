// ALGORYTMY PRZESZUKIWANIA GRAFU
#ifndef SEARCHING_HPP
#define SEARCHING_HPP

#include <cstdlib>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

#include "graph.hpp"

namespace algolib
{
    namespace detail
    {
        /**
        Krok rekurencyjnego DFS.
        @param graph graf
        @param vertex aktualny wierzchołek
        @param is_visited lista odwiedzonych wierzchołków
        */
        void dfsR_step(const graph & gr, int vertex, std::vector<bool> & is_visited);
    }

    /**
    Algorytm BFS.
    @param gr graf
    @param root wierzchołek początkowy
    @return lista odwiedzonych wierzchołków
    */
    std::vector<bool> bfs(const graph & gr, int root);

    /**
    Iteracyjny algorytm DFS.
    @param gr graf
    @param root wierzchołek początkowy
    @return lista odwiedzonych wierzchołków
    */
    std::vector<bool> dfsI(const graph & gr, int root);

    /**
    Rekurencyjny algorytm DFS.
    @param gr graf
    @param root wierzchołek początkowy
    @return lista odwiedzonych wierzchołków
    */
    std::vector<bool> dfsR(const graph & gr, int root);
}

#endif
