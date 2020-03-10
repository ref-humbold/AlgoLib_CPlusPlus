/**!
 * \file scc.hpp
 * \brief ALGORYTM WYZNACZANIA SILNIE SPÓLJNYCH SKŁADOWYCH W GRAFIE SKIEROWANYM
 */
#ifndef STRONGLY_CONNECTED_COMPONENTS_HPP_
#define STRONGLY_CONNECTED_COMPONENTS_HPP_

#include <cstdlib>
#include <algorithm>
#include <set>
#include <vector>
#include "directed_graph.hpp"

namespace impl
{
    class graph_components
    {
    public:
        explicit graph_components(algolib::graphs::directed_graph & digr);

        /**!
         * \brief Algorytm wyznaczania silnie spójnych składowych grafu
         * \return numery silnie spójnych składowych dla wierzchołków
         */
        std::vector<int> find_scc();

    private:
        /**!
         * \brief Algorytm DFS z licznikiem czasu wyznaczający porządek post-order wierzchołków
         * \param vertex aktualny wierzchołek
         * \param timer aktualny czas
         * \return nowy czas po przetworzeniu wierzchołka
         */
        int dfs_order(vertex_t vertex, int timer);

        /**!
         * \brief Algorytm DFS wyznaczający silnie spójne składowe
         * \param vertex aktualny wierzchołek
         * \param component numer składowej
         */
        void dfs_scc(vertex_t vertex, int component);

        algolib::graphs::directed_graph & digraph;  //!< Reprezentacja grafu skierowanego.
        std::vector<int> components;  //!< Numery silnie spójnych składowych dla wierzchołków.
        std::vector<std::pair<int, vertex_t>> postorder;  //!< Czasy post-order wierzchołków.
    };
}

namespace algolib
{
    namespace graphs
    {
        /**!
         * \brief Algorytm wyznaczania silnie spójnych składowych grafu
         * \param digraph graf skierowany
         * \return numery silnie spójnych składowych dla wierzchołków
         */
        std::vector<std::set<vertex_t>> find_scc(directed_graph & digraph);
    }
}

#endif
