/**
 * @file topological_sorting.hpp
 * ALGORYTMY SORTOWANIA TOPOLOGICZNEGO
 */
#ifndef TOPOLOGICAL_SORTING_HPP
#define TOPOLOGICAL_SORTING_HPP

#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <functional>
#include <queue>
#include <string>
#include <vector>

#include "directed_graph.hpp"

namespace detail
{
    /**
     * Algorytm DFS wyznaczający kolejność wierzchołków.
     * @param vertex aktualny wierzchołek
     * @param digraph graf skierowany
     * @param order aktualny porządek topologiczny
     * @param visited czy wierzchołek odwiedzony
     */
    void dfs(vertex_t vertex, vertex_t index, const algolib::graphs::directed_graph & digraph,
             std::vector<vertex_t> & order, std::vector<std::pair<vertex_t, bool>> & indices);
}

namespace algolib
{
    namespace graphs
    {
        class directed_cyclic_graph_exception : public std::logic_error
        {
        public:
            explicit directed_cyclic_graph_exception(const std::string & what_arg)
                : std::logic_error(what_arg)
            {
            }

            explicit directed_cyclic_graph_exception(const char * what_arg = "")
                : std::logic_error(what_arg)
            {
            }
        };

        /**
         * Sortowanie topologiczne przez liczenie poprzedników.
         * @param digraph graf skierowany
         * @return porządek topologiczny wierzchołków
         */
        std::vector<vertex_t> sort_topological1(const directed_graph & digraph);

        /**
         * Sortowanie topologiczne z użyciem DFS.
         * @param digraph graf skierowany
         * @return porządek topologiczny wierzchołków
         */
        std::vector<vertex_t> sort_topological2(const directed_graph & digraph);
    }
};

#endif
