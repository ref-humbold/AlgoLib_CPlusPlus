/*!
 * \file undirected_graph.hpp
 * \brief Struktury grafów nieskierowanych
 */
#ifndef UNDIRECTED_GRAPH_HPP_
#define UNDIRECTED_GRAPH_HPP_

#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <tuple>
#include <vector>
#include <numeric>
#include "graph.hpp"

namespace algolib
{
    namespace graphs
    {
#pragma region undirected_graph

        struct undirected_graph : public virtual graph
        {
            ~undirected_graph() override = default;
        };

#pragma endregion
#pragma region undirected_simple_graph

        class undirected_simple_graph : public simple_graph, public undirected_graph
        {
        public:
            explicit undirected_simple_graph(int n, const std::vector<edge_t> & edges = {})
                : simple_graph(n)
            {
                for(const auto & e : edges)
                    add_edge(std::get<0>(e), std::get<1>(e));
            }

            ~undirected_simple_graph() override = default;
            undirected_simple_graph(const undirected_simple_graph &) = default;
            undirected_simple_graph(undirected_simple_graph &&) = default;
            undirected_simple_graph & operator=(const undirected_simple_graph &) = default;
            undirected_simple_graph & operator=(undirected_simple_graph &&) = default;

            size_t get_edges_number() const override;

            std::vector<edge_t> get_edges() const override;

            void add_edge(vertex_t vertex1, vertex_t vertex2) override;

            size_t get_indegree(vertex_t vertex) const override;
        };

#pragma endregion
#pragma region undirected_weighted_simple_graph

        class undirected_weighted_simple_graph : public undirected_simple_graph,
                                                 public weighted_graph
        {
        public:
            explicit undirected_weighted_simple_graph(int n, const std::vector<edge_t> & edges = {})
                : undirected_simple_graph(n, edges)
            {
            }

            undirected_weighted_simple_graph(int n, std::vector<wedge_t> edges)
                : undirected_simple_graph(n)
            {
                for(const auto & e : edges)
                    add_weighted_edge(std::get<0>(e), std::get<1>(e), std::get<2>(e));
            }

            ~undirected_weighted_simple_graph() override = default;
            undirected_weighted_simple_graph(const undirected_weighted_simple_graph &) = default;
            undirected_weighted_simple_graph(undirected_weighted_simple_graph &&) = default;
            undirected_weighted_simple_graph &
                    operator=(const undirected_weighted_simple_graph &) = default;
            undirected_weighted_simple_graph &
                    operator=(undirected_weighted_simple_graph &&) = default;

            std::vector<wedge_t> get_weighted_edges() const override;

            void add_weighted_edge(vertex_t vertex1, vertex_t vertex2, weight_t weight) override;

            std::vector<wvertex_t> get_weighted_neighbours(vertex_t vertex) const override;
        };

#pragma endregion
    }
}

#endif
