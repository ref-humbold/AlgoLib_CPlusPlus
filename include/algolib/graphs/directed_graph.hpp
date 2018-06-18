/**
 * @file directed_graph.hpp
 * STRUKTURY GRAFÓW SKIEROWANYCH
 */
#ifndef _DIRECTED_GRAPH_HPP_
#define _DIRECTED_GRAPH_HPP_

#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <numeric>
#include <set>
#include <tuple>
#include <vector>

#include "graph.hpp"

namespace algolib
{
    namespace graphs
    {
        class directed_graph : public virtual graph
        {
        public:
            directed_graph() = default;
            virtual ~directed_graph() = default;
            directed_graph(const directed_graph &) = default;
            directed_graph(directed_graph &&) = default;
            directed_graph & operator=(const directed_graph &) = default;
            directed_graph & operator=(directed_graph &&) = default;

            /// Odwracanie skierowania grafu.
            virtual void reverse() = 0;
        };

        class directed_simple_graph : public simple_graph, public directed_graph
        {
        public:
            explicit directed_simple_graph(int n, std::vector<edge_t> edges = std::vector<edge_t>())
                : simple_graph(n)
            {
                for(const auto & e : edges)
                    add_edge(std::get<0>(e), std::get<1>(e));
            }

            virtual ~directed_simple_graph() = default;
            directed_simple_graph(const directed_simple_graph &) = default;
            directed_simple_graph(directed_simple_graph &&) = default;
            directed_simple_graph & operator=(const directed_simple_graph &) = default;
            directed_simple_graph & operator=(directed_simple_graph &&) = default;

            size_t get_edges_number() const override;

            std::vector<edge_t> get_edges() const override;

            void add_edge(vertex_t vertex1, vertex_t vertex2) override;

            size_t get_indegree(vertex_t vertex) const override;

            virtual void reverse() override;
        };

        class directed_weighted_simple_graph : public directed_simple_graph, public weighted_graph
        {
        public:
            explicit directed_weighted_simple_graph(
                int n, std::vector<edge_t> edges = std::vector<edge_t>())
                : directed_simple_graph(n, edges)
            {
            }

            directed_weighted_simple_graph(int n, std::vector<wedge_t> edges)
                : directed_simple_graph(n)
            {
                for(const auto & e : edges)
                    add_weighted_edge(std::get<0>(e), std::get<1>(e), std::get<2>(e));
            }

            virtual ~directed_weighted_simple_graph() = default;
            directed_weighted_simple_graph(const directed_weighted_simple_graph &) = default;
            directed_weighted_simple_graph(directed_weighted_simple_graph &&) = default;
            directed_weighted_simple_graph &
                operator=(const directed_weighted_simple_graph &) = default;
            directed_weighted_simple_graph & operator=(directed_weighted_simple_graph &&) = default;

            std::vector<wedge_t> get_weighted_edges() const override;

            void add_weighted_edge(vertex_t vertex1, vertex_t vertex2, weight_t weight) override;

            std::vector<wvertex_t> get_weighted_neighbours(vertex_t vertex) const override;

            void reverse() override;
        };
    }
}

#endif
