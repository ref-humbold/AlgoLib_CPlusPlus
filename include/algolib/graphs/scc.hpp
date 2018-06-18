/**
 * @file scc.hpp
 * ALGORYTM WYZNACZANIA SILNIE SPÓLJNYCH SKŁADOWYCH W GRAFIE SKIEROWANYM
 */
#ifndef _SCC_HPP_
#define _SCC_HPP_

#include <cstdlib>
#include <algorithm>
#include <set>
#include <vector>

#include "directed_graph.hpp"

namespace detail
{
    class graph_components
    {
    private:
        /// Reprezentacja grafu skierowanego.
        algolib::graphs::directed_graph & digraph;

        /// Numery silnie spójnych składowych dla wierzchołków
        std::vector<int> components;

        /// Czasy post-order wierzchołków
        std::vector<std::pair<int, vertex_t>> postorder;

    public:
        explicit graph_components(algolib::graphs::directed_graph & digr);

        /**
         * Algorytm wyznaczania silnie spójnych składowych grafu.
         * @return numery silnie spójnych składowych dla wierzchołków
         */
        std::vector<int> find_scc();

    private:
        /**
         * Algorytm DFS z licznikiem czasu wyznaczający porządek post-order wierzchołków.
         * @param vertex aktualny wierzchołek
         * @param timer aktualny czas
         * @return nowy czas po przetworzeniu wierzchołka
         */
        int dfs_order(vertex_t vertex, int timer);

        /**
         * Algorytm DFS wyznaczający silnie spójne składowe.
         * @param vertex aktualny wierzchołek
         * @param component numer składowej
         */
        void dfs_scc(vertex_t vertex, int component);
    };
}

namespace algolib
{
    namespace graphs
    {
        /**
         * Algorytm wyznaczania silnie spójnych składowych grafu.
         * @param digraph graf skierowany
         * @return numery silnie spójnych składowych dla wierzchołków
         */
        std::vector<std::set<vertex_t>> find_scc(directed_graph & digraph);
    }
}

#endif
