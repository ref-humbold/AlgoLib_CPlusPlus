/**!
 * \file cutting.hpp
 * \brief Algorithms for graph cutting (edge cut and vertex cut)
 */
#ifndef CUTTING_HPP_
#define CUTTING_HPP_

#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <limits>
#include <unordered_map>
#include <vector>
#include "algolib/graphs_new/algorithms/searching.hpp"
#include "algolib/graphs_new/undirected_graph.hpp"

namespace internal
{
    namespace algr = algolib::graphs;

    template <typename Vertex>
    struct cutting_strategy : public algr::dfs_strategy<Vertex>
    {
        cutting_strategy() : depth{0}
        {
        }

        ~cutting_strategy() override = default;

        void for_root(const Vertex &) override
        {
        }

        void on_entry(const Vertex & vertex) override
        {
            this->dfs_depths.emplace(vertex, depth);
            this->low_values.emplace(vertex, depth);
            this->dfs_children.emplace(vertex, std::vector<Vertex>());
            ++depth;
        }

        void on_next_vertex(const Vertex & vertex, const Vertex & neighbour) override
        {
            this->dfs_parents.emplace(neighbour, vertex);
            this->dfs_children[vertex].push_back(neighbour);
        }

        void on_exit(const Vertex & vertex) override
        {
            int minimal_low_value = std::numeric_limits<int>::max();

            for(auto && child : this->dfs_children[vertex])
                minimal_low_value = std::min(this->low_values[child], minimal_low_value);

            this->low_values[vertex] = std::min(this->low_values[vertex], minimal_low_value);
            --depth;
        }

        void on_edge_to_visited(const Vertex & vertex, const Vertex & neighbour) override
        {
            if(neighbour != this->dfs_parents.at(vertex))
                this->low_values[vertex] =
                        std::min(this->low_values[vertex], this->dfs_depths[neighbour]);
        }

        bool has_bridge(const Vertex & vertex)
        {
            return !this->is_dfs_root(vertex)
                   && this->low_values[vertex] == this->dfs_depths[vertex];
        }

        bool is_separator(const Vertex & vertex)
        {
            if(this->is_dfs_root(vertex))
                return dfs_children[vertex].size() > 1;

            return std::any_of(this->dfs_children[vertex].begin(), this->dfs_children[vertex].end(),
                               [&](auto && child) {
                                   return this->low_values[child] >= this->dfs_depths[vertex];
                               });
        }

        bool is_dfs_root(const Vertex & vertex)
        {
            return this->dfs_depths[vertex] == 0;
        }

        std::unordered_map<Vertex, Vertex> dfs_parents;
        std::unordered_map<Vertex, std::vector<Vertex>> dfs_children;
        std::unordered_map<Vertex, int> dfs_depths;
        std::unordered_map<Vertex, int> low_values;
        int depth;
    };
}

#include <iostream>

namespace algolib::graphs
{
    /*!
     * \brief Finds an edge cut of given graph.
     * \param graph an undirected graph
     * \return vector of edges in the edge cut
     */
    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    std::vector<typename undirected_graph<VertexId, VertexProperty, EdgeProperty>::edge_type>
            find_edge_cut(const undirected_graph<VertexId, VertexProperty, EdgeProperty> & graph)
    {
        std::vector<typename undirected_graph<VertexId, VertexProperty, EdgeProperty>::edge_type>
                bridges;
        internal::cutting_strategy<
                typename undirected_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type>
                strategy;
        std::vector<typename undirected_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type>
                vertices = graph.vertices();

        dfs_recursive(graph, strategy, vertices);
        vertices.erase(std::remove_if(vertices.begin(), vertices.end(),
                                      [&](auto && vertex) { return !strategy.has_bridge(vertex); }),
                       vertices.end());
        std::transform(vertices.begin(), vertices.end(), std::back_inserter(bridges),
                       [&](auto && vertex) {
                           return graph[std::make_pair(vertex, strategy.dfs_parents.at(vertex))];
                       });
        return bridges;
    }

    /*!
     * \brief Finds a vertex cut of given graph.
     * \param graph an undirected graph
     * \return vector of vertices in the vertex cut
     */
    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    std::vector<typename undirected_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type>
            find_vertex_cut(const undirected_graph<VertexId, VertexProperty, EdgeProperty> & graph)
    {
        std::vector<typename undirected_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type>
                separators;
        internal::cutting_strategy<
                typename undirected_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type>
                strategy;
        std::vector<typename undirected_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type>
                vertices = graph.vertices();

        dfs_recursive(graph, strategy, vertices);
        std::copy_if(vertices.begin(), vertices.end(), std::back_inserter(separators),
                     [&](auto && vertex) { return strategy.is_separator(vertex); });
        return separators;
    }
}

#endif
