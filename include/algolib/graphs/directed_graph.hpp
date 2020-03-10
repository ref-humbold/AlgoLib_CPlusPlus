/*!
 * \file directed_graph.hpp
 * \brief Struktury grafów skierowanych
 */
#ifndef DIRECTED_GRAPH_HPP_
#define DIRECTED_GRAPH_HPP_

#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <set>
#include <tuple>
#include <vector>
#include <numeric>
#include "undirected_graph.hpp"

namespace algolib
{
    namespace graphs
    {
        // region directed_graph

        struct directed_graph : public virtual graph
        {
            ~directed_graph() override = default;

            //! \brief Odwracanie skierowania grafu.
            virtual void reverse() = 0;
        };

        // endregion
        // region directed_simple_graph

        class directed_simple_graph : public simple_graph, public directed_graph
        {
        public:
            explicit directed_simple_graph(int n, const std::vector<edge_t> & edges = {})
                : simple_graph(n)
            {
                for(const auto & e : edges)
                    add_edge(std::get<0>(e), std::get<1>(e));
            }

            directed_simple_graph(const undirected_simple_graph & ugraph);
            ~directed_simple_graph() override = default;
            directed_simple_graph(const directed_simple_graph &) = default;
            directed_simple_graph(directed_simple_graph &&) = default;
            directed_simple_graph & operator=(const directed_simple_graph &) = default;
            directed_simple_graph & operator=(directed_simple_graph &&) = default;

            size_t get_edges_number() const override;

            std::vector<edge_t> get_edges() const override;

            void add_edge(vertex_t vertex1, vertex_t vertex2) override;

            size_t get_indegree(vertex_t vertex) const override;

            void reverse() override;
        };

        // endregion
        // region directed_weighted_simple_graph

        class directed_weighted_simple_graph : public directed_simple_graph, public weighted_graph
        {
        public:
            explicit directed_weighted_simple_graph(int n, const std::vector<edge_t> & edges = {})
                : directed_simple_graph(n, edges)
            {
            }

            directed_weighted_simple_graph(int n, std::vector<wedge_t> edges)
                : directed_simple_graph(n)
            {
                for(const auto & e : edges)
                    add_weighted_edge(std::get<0>(e), std::get<1>(e), std::get<2>(e));
            }

            directed_weighted_simple_graph(const undirected_weighted_simple_graph & uwgraph);
            ~directed_weighted_simple_graph() override = default;
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

        // endregion
    }
}

#endif
