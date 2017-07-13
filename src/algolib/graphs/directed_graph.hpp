/**
 * @file directed_graph.hpp
 * STRUKTURY GRAFÓW SKIEROWANYCH
 */
#ifndef DIRECTED_GRAPH_HPP
#define DIRECTED_GRAPH_HPP

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
            directed_graph(const directed_graph & g) = default;
            directed_graph(directed_graph && g) = default;
            directed_graph & operator=(const directed_graph & g) = default;
            directed_graph & operator=(directed_graph && g) = default;

            /**
             * Odwracanie skierowania grafu
             */
            virtual void reverse() = 0;
        };

        class directed_weighted_graph : public virtual directed_graph, public virtual weighted_graph
        {
        public:
            directed_weighted_graph() = default;
            virtual ~directed_weighted_graph() = default;
            directed_weighted_graph(const directed_weighted_graph & g) = default;
            directed_weighted_graph(directed_weighted_graph && g) = default;
            directed_weighted_graph & operator=(const directed_weighted_graph & g) = default;
            directed_weighted_graph & operator=(directed_weighted_graph && g) = default;
        };

        class directed_simple_graph : public simple_graph, public virtual directed_graph
        {
        public:
            explicit directed_simple_graph(int n, std::vector<edge_t> edges = std::vector<edge_t>())
                : simple_graph(n)
            {
                for(const auto & e : edges)
                    add_edge(std::get<0>(e), std::get<1>(e));
            }

            virtual ~directed_simple_graph() = default;
            directed_simple_graph(const directed_simple_graph & g) = default;
            directed_simple_graph(directed_simple_graph && g) = default;
            directed_simple_graph & operator=(const directed_simple_graph & g) = default;
            directed_simple_graph & operator=(directed_simple_graph && g) = default;

            size_t get_edges_number() const override;

            std::vector<edge_t> get_edges() const override;

            void add_edge(vertex_t v, vertex_t u) override;

            size_t get_indegree(vertex_t v) const override;

            virtual void reverse() override;
        };

        class directed_weighted_simple_graph : public directed_simple_graph,
                                               public virtual directed_weighted_graph
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
            directed_weighted_simple_graph(const directed_weighted_simple_graph & g) = default;
            directed_weighted_simple_graph(directed_weighted_simple_graph && g) = default;
            directed_weighted_simple_graph &
                operator=(const directed_weighted_simple_graph & g) = default;
            directed_weighted_simple_graph &
                operator=(directed_weighted_simple_graph && g) = default;

            std::vector<wedge_t> get_weighted_edges() const override;

            void add_weighted_edge(vertex_t v, vertex_t u, weight_t wg) override;

            std::vector<wvertex_t> get_weighted_neighbours(vertex_t v) const override
            {
                return std::vector<wvertex_t>(graphrepr[v].begin(), graphrepr[v].end());
            }

            void reverse() override;
        };
    }
}

#endif
