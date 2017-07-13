/**
 * @file undirected_graph.hpp
 * STRUKTURY GRAFÓW NIESKIEROWANYCH
 */
#ifndef UNDIRECTED_GRAPH_HPP
#define UNDIRECTED_GRAPH_HPP

#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <numeric>
#include <tuple>
#include <vector>

#include "directed_graph.hpp"
#include "graph.hpp"

namespace algolib
{
    namespace graphs
    {
        class undirected_graph : public virtual graph
        {
        public:
            undirected_graph() = default;
            virtual ~undirected_graph() = default;
            undirected_graph(const undirected_graph & g) = default;
            undirected_graph(undirected_graph && g) = default;
            undirected_graph & operator=(const undirected_graph & g) = default;
            undirected_graph & operator=(undirected_graph && g) = default;

            /**
             * Zamiana krawędzi nieskierowanych na skierowane.
             * @return graf ze skierowanymi krawędziami
             */
            virtual directed_graph * as_directed() const = 0;
        };

        class undirected_weighted_graph : public virtual undirected_graph,
                                          public virtual weighted_graph
        {
        public:
            undirected_weighted_graph() = default;
            virtual ~undirected_weighted_graph() = default;
            undirected_weighted_graph(const undirected_weighted_graph & g) = default;
            undirected_weighted_graph(undirected_weighted_graph && g) = default;
            undirected_weighted_graph & operator=(const undirected_weighted_graph & g) = default;
            undirected_weighted_graph & operator=(undirected_weighted_graph && g) = default;

            /**
             * Zamiana krawędzi nieskierowanych na skierowane.
             * @return graf ze skierowanymi krawędziami
             */
            virtual directed_weighted_graph * as_directed() const override = 0;
        };

        class undirected_simple_graph : public simple_graph, public virtual undirected_graph
        {
        public:
            explicit undirected_simple_graph(int n,
                                             std::vector<edge_t> edges = std::vector<edge_t>())
                : simple_graph(n)
            {
                for(const auto & e : edges)
                    add_edge(std::get<0>(e), std::get<1>(e));
            }

            virtual ~undirected_simple_graph() = default;
            undirected_simple_graph(const undirected_simple_graph & g) = default;
            undirected_simple_graph(undirected_simple_graph && g) = default;
            undirected_simple_graph & operator=(const undirected_simple_graph & g) = default;
            undirected_simple_graph & operator=(undirected_simple_graph && g) = default;

            size_t get_edges_number() const override;

            std::vector<edge_t> get_edges() const override;

            void add_edge(vertex_t v, vertex_t u) override;

            size_t get_indegree(vertex_t v) const override
            {
                return get_outdegree(v);
            }

            virtual directed_simple_graph * as_directed() const override;
        };

        class undirected_weighted_simple_graph : public undirected_simple_graph,
                                                 public virtual undirected_weighted_graph
        {
        public:
            explicit undirected_weighted_simple_graph(
                int n, std::vector<edge_t> edges = std::vector<edge_t>())
                : undirected_simple_graph(n, edges)
            {
            }

            undirected_weighted_simple_graph(int n, std::vector<wedge_t> edges)
                : undirected_simple_graph(n)
            {
                for(const auto & e : edges)
                    add_weighted_edge(std::get<0>(e), std::get<1>(e), std::get<2>(e));
            }

            virtual ~undirected_weighted_simple_graph() = default;
            undirected_weighted_simple_graph(const undirected_weighted_simple_graph & g) = default;
            undirected_weighted_simple_graph(undirected_weighted_simple_graph && g) = default;
            undirected_weighted_simple_graph &
                operator=(const undirected_weighted_simple_graph & g) = default;
            undirected_weighted_simple_graph &
                operator=(undirected_weighted_simple_graph && g) = default;

            std::vector<wedge_t> get_weighted_edges() const override;

            void add_weighted_edge(vertex_t v, vertex_t u, weight_t wg) override;

            std::vector<wvertex_t> get_weighted_neighbours(vertex_t v) const override
            {
                return std::vector<wvertex_t>(graphrepr[v].begin(), graphrepr[v].end());
            }

            directed_weighted_simple_graph * as_directed() const override;
        };
    }
}

#endif
