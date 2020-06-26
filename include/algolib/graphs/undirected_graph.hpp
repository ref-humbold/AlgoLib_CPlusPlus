/*!
 * \file undirected_graph.hpp
 * \brief Structure of undirected graph
 */
#ifndef UNDIRECTED_GRAPH_HPP_
#define UNDIRECTED_GRAPH_HPP_

#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <unordered_set>
#include <vector>
#include "simple_graph.hpp"

namespace algolib
{
    namespace graphs
    {
        template <typename V, typename VP, typename EP>
        struct undirected_graph : public virtual graph<V, VP, EP>
        {
        };

        template <typename V = size_t, typename VP = no_prop, typename EP = no_prop>
        class undirected_simple_graph : public simple_graph<V, VP, EP>,
                                        public virtual undirected_graph<V, VP, EP>
        {
        public:
            using vertex_type = typename simple_graph<V, VP, EP>::vertex_type;
            using edge_type = typename simple_graph<V, VP, EP>::edge_type;
            using vertex_property_type = typename simple_graph<V, VP, EP>::vertex_property_type;
            using edge_property_type = typename simple_graph<V, VP, EP>::edge_property_type;

        protected:
            using repr = typename simple_graph<V, VP, EP>::repr;

        public:
            explicit undirected_simple_graph(const std::vector<vertex_type> & vertices = {})
                : simple_graph<V, VP, EP>(vertices)
            {
            }

            ~undirected_simple_graph() override = default;
            undirected_simple_graph(const undirected_simple_graph &) = default;
            undirected_simple_graph(undirected_simple_graph &&) = default;
            undirected_simple_graph & operator=(const undirected_simple_graph &) = default;
            undirected_simple_graph & operator=(undirected_simple_graph &&) = default;

            size_t output_degree(const vertex_type & vertex) const override
            {
                return this->representation.adjacent_edges(vertex).size();
            }

            size_t input_degree(const vertex_type & vertex) const override
            {
                return this->representation.adjacent_edges(vertex).size();
            }

            size_t edges_count() const override;
            std::vector<edge_type> edges() const override;
            edge_type add_edge(const edge_type & edge) override;
            edge_type add_edge(const edge_type & edge,
                               const edge_property_type & property) override;
        };

        template <typename V, typename VP, typename EP>
        size_t undirected_simple_graph<V, VP, EP>::edges_count() const
        {
            std::vector<std::unordered_set<edge_type>> edges_set = this->representation.edges_set();
            std::unordered_set<edge_type> all_edges;

            for(const auto & edge_set : edges_set)
                for(const edge_type & edge : edge_set)
                    all_edges.insert(edge);

            return all_edges.size();
        }

        template <typename V, typename VP, typename EP>
        std::vector<typename undirected_simple_graph<V, VP, EP>::edge_type>
                undirected_simple_graph<V, VP, EP>::edges() const
        {
            std::vector<std::unordered_set<edge_type>> edges_set = this->representation.edges_set();
            std::unordered_set<edge_type> all_edges;

            for(const auto & edge_set : edges_set)
                for(const edge_type & edge : edge_set)
                    all_edges.insert(edge);

            return std::vector<edge_type>(all_edges.begin(), all_edges.end());
        }

        template <typename V, typename VP, typename EP>
        typename undirected_simple_graph<V, VP, EP>::edge_type
                undirected_simple_graph<V, VP, EP>::add_edge(
                        const typename undirected_simple_graph<V, VP, EP>::edge_type & edge)
        try
        {
            return this->get_edge(edge.source(), edge.destination());
        }
        catch(const std::out_of_range &)
        {
            this->representation.add_edge_to_source(edge);
            this->representation.add_edge_to_destination(edge);
            return edge;
        }

        template <typename V, typename VP, typename EP>
        typename undirected_simple_graph<V, VP, EP>::edge_type
                undirected_simple_graph<V, VP, EP>::add_edge(
                        const typename undirected_simple_graph<V, VP, EP>::edge_type & edge,
                        const typename undirected_simple_graph<V, VP, EP>::edge_property_type &
                                property)
        try
        {
            return this->get_edge(edge.source(), edge.destination());
        }
        catch(const std::out_of_range &)
        {
            this->representation.add_edge_to_source(edge);
            this->representation.add_edge_to_destination(edge);
            this->representation[edge] = property;
            return edge;
        }
    }
}

#endif
