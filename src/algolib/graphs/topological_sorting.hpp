// ALGORYTMY SORTOWANIA TOPOLOGICZNEGO
#ifndef TOPOLOGICAL_SORTING_HPP
#define TOPOLOGICAL_SORTING_HPP

#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <vector>
#include <queue>

#include "graph.hpp"

namespace algolib
{
    namespace detail
    {
        /**
        Algorytm DFS wyznaczający kolejność wierzchołków.
        @param vertex aktualny wierzchołek
        @param digraph graf skierowany
        @param order aktualny porządek topologiczny
        @param visited czy wierzchołek odwiedzony
        */
        void dfs(int vertex, graph digraph, std::vector<int> & order,
            std::vector<bool> & is_visited);
    }

    /**
    Sortowanie topologiczne przez liczenie poprzedników.
    @param digraph graf skierowany
    @return porządek topologiczny wierzchołków
    */
    std::vector<int> sort_topological1(graph digraph);

    /**
    Sortowanie topologiczne z użyciem DFS.
    @param digraph graf skierowany
    @return porządek topologiczny wierzchołków
    */
    std::vector<int> sort_topological2(graph digraph);
};

#endif

