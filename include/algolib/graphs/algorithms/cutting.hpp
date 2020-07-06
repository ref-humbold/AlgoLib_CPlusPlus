/**!
 * \file cutting.hpp
 * \brief Algorithms for graph cutting (edge cut and vertex cut)
 */
#ifndef CUTTING_HPP_
#define CUTTING_HPP_

#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <limits>
#include "algolib/graphs/algorithms/searching.hpp"
#include "algolib/graphs/undirected_graph.hpp"

namespace internal
{
    namespace algr = algolib::graphs;

    template <typename V>
    struct cutting_strategy : public algr::dfs_strategy<V>
    {
        cutting_strategy() : depth{0}
        {
        }

        void for_root(const V & root) override
        {
        }

        void on_entry(const V & vertex) override
        {
            this->dfs_depths.emplace(vertex, depth);
            this->low_values.emplace(vertex, depth);
            this->dfs_children.emplace(vertex, std::vector<V>());
            ++depth;
        }

        void on_next_vertex(const V & vertex, const V & neighbour) override
        {
            this->dfs_parents.emplace(neighbour, vertex);
            this->dfs_children[vertex].push_back(neighbour);
        }

        void on_exit(const V & vertex) override
        {
            int minimal_low_value = std::numeric_limits<int>::max();

            for(auto && child : this->dfs_children[vertex])
                minimal_low_value = std::min(this->low_values[child], minimal_low_value);

            this->low_values[vertex] = std::min(this->low_values[vertex], minimal_low_value);
            --depth;
        }

        void on_edge_to_visited(const V & vertex, const V & neighbour) override
        {
            if(neighbour != this->dfs_parents[vertex])
                this->low_values[vertex] =
                        std::min(this->low_values[vertex], this->dfs_depths[neighbour]);
        }

        bool has_bridge(const V & vertex)
        {
            return !this->is_dfs_root(vertex)
                   && this->low_values[vertex] == this->dfs_depths[vertex];
        }

        bool is_separator(const V & vertex)
        {
            if(this->is_dfs_root(vertex))
                return dfs_children[vertex].size() > 1;

            return std::any_of(this->dfs_children[vertex].begin(), this->dfs_children[vertex].end(),
                               [&](const V & child) {
                                   return this->low_values[child] >= this->dfs_depths[vertex];
                               });
        }

        bool is_dfs_root(const V & vertex)
        {
            return this->dfs_depths[vertex] == 0;
        }

        std::unordered_map<V, V> dfs_parents;
        std::unordered_map<V, std::vector<V>> dfs_children;
        std::unordered_map<V, int> dfs_depths;
        std::unordered_map<V, int> low_values;
        int depth;
    };
}

namespace algolib
{
    namespace graphs
    {
        /**!
         * \brief Finds an edge cut of given graph.
         * \param graph an undirected graph
         * \return vector of edges in the edge cut
         */
        template <typename V = size_t, typename VP = no_prop, typename EP = no_prop>
        std::vector<typename undirected_graph<V, VP, EP>::edge_type>
                find_edge_cut(const undirected_graph<V, VP, EP> & graph)
        {
            std::vector<typename undirected_graph<V, VP, EP>::edge_type> bridges;
            internal::cutting_strategy<typename undirected_graph<V, VP, EP>::vertex_type> strategy;

            dfs_recursive(graph, strategy, graph.vertices());

            for(auto && vertex : graph.vertices())
                if(strategy.has_bridge(vertex))
                    bridges.push_back(graph.get_edge(vertex, strategy.dfs_parents[vertex]));

            return bridges;
        }

        /**!
         * \brief Finds a vertex cut of given graph.
         * \param graph an undirected graph
         * \return vector of vertices in the vertex cut
         */
        template <typename V = size_t, typename VP = no_prop, typename EP = no_prop>
        std::vector<typename undirected_graph<V, VP, EP>::vertex_type>
                find_vertex_cut(const undirected_graph<V, VP, EP> & graph)
        {
            std::vector<typename undirected_graph<V, VP, EP>::vertex_type> separators;
            internal::cutting_strategy<typename undirected_graph<V, VP, EP>::vertex_type> strategy;
            std::vector<typename undirected_graph<V, VP, EP>::vertex_type> vertices =
                    graph.vertices();

            dfs_recursive(graph, strategy, vertices);

            std::copy_if(vertices.begin(), vertices.end(), std::back_inserter(separators),
                         [&](const typename undirected_graph<V, VP, EP>::vertex_type & vertex) {
                             return strategy.is_separator(vertex);
                         });

            return separators;
        }
    }
}

#endif
