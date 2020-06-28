/*!
 * \file tree_graph.hpp
 * \brief Structure of tree graph
 */
#ifndef TREE_GRAPH_HPP_
#define TREE_GRAPH_HPP_

#include <cstdlib>
#include <algorithm>
#include <vector>
#include "undirected_graph.hpp"

namespace algolib
{
    namespace graphs
    {
        template <typename V = size_t, typename VP = no_prop, typename EP = no_prop>
        class tree_graph : public virtual undirected_graph<V, VP, EP>
        {
        protected:
            using graph_t =
                    undirected_simple_graph<typename tree_graph<V, VP, EP>::vertex_type,
                                            typename tree_graph<V, VP, EP>::vertex_property_type,
                                            typename tree_graph<V, VP, EP>::edge_property_type>;

        public:
            explicit tree_graph(const typename tree_graph<V, VP, EP>::vertex_type & vertex)
                : graph{graph_t({vertex})}
            {
            }

            ~tree_graph() override = default;
            tree_graph(const tree_graph &) = default;
            tree_graph(tree_graph &&) = default;
            tree_graph & operator=(const tree_graph &) = default;
            tree_graph & operator=(tree_graph &&) = default;

            size_t vertices_count() const override
            {
                return this->graph.vertices_count();
            }

            size_t edges_count() const override
            {
                return this->graph.edges_count();
            }

            std::vector<typename tree_graph<V, VP, EP>::vertex_type> vertices() const override
            {
                return this->graph.vertices();
            }

            std::vector<typename tree_graph<V, VP, EP>::edge_type> edges() const override
            {
                return this->graph.edges();
            }

            typename tree_graph<V, VP, EP>::vertex_property_type &
                    operator[](const typename tree_graph<V, VP, EP>::vertex_type & vertex) override
            {
                return this->graph[vertex];
            }

            typename tree_graph<V, VP, EP>::edge_property_type &
                    operator[](const typename tree_graph<V, VP, EP>::edge_type & edge) override
            {
                return this->graph[edge];
            }

            const typename tree_graph<V, VP, EP>::vertex_property_type & property(
                    const typename tree_graph<V, VP, EP>::vertex_type & vertex) const override
            {
                return this->graph.property(vertex);
            }

            const typename tree_graph<V, VP, EP>::edge_property_type &
                    property(const typename tree_graph<V, VP, EP>::edge_type & edge) const override
            {
                return this->graph.property(edge);
            }

            bool has_property(
                    const typename tree_graph<V, VP, EP>::vertex_type & vertex) const override
            {
                return this->graph.has_property(vertex);
            }

            bool has_property(const typename tree_graph<V, VP, EP>::edge_type & edge) const override
            {
                return this->graph.has_property(edge);
            }

            typename tree_graph<V, VP, EP>::edge_type get_edge(
                    const typename tree_graph<V, VP, EP>::vertex_type & source,
                    const typename tree_graph<V, VP, EP>::vertex_type & destination) const override
            {
                return this->graph.get_edge(source, destination);
            }

            std::vector<typename tree_graph<V, VP, EP>::edge_type> adjacent_edges(
                    const typename tree_graph<V, VP, EP>::vertex_type & vertex) const override
            {
                return this->graph.adjacent_edges(vertex);
            }

            std::vector<typename tree_graph<V, VP, EP>::vertex_type> neighbours(
                    const typename tree_graph<V, VP, EP>::vertex_type & vertex) const override
            {
                return this->graph.neighbours(vertex);
            }

            size_t output_degree(
                    const typename tree_graph<V, VP, EP>::vertex_type & vertex) const override
            {
                return this->graph.output_degree(vertex);
            }

            size_t input_degree(
                    const typename tree_graph<V, VP, EP>::vertex_type & vertex) const override
            {
                return this->graph.input_degree(vertex);
            }

            directed_simple_graph<typename undirected_simple_graph<V, VP, EP>::vertex_type,
                                  typename undirected_simple_graph<V, VP, EP>::vertex_property_type,
                                  typename undirected_simple_graph<V, VP, EP>::edge_property_type>
                    as_directed() const
            {
                return this->graph.as_directed();
            }

            const typename tree_graph<V, VP, EP>::edge_type
                    add_vertex(const typename tree_graph<V, VP, EP>::vertex_type & vertex,
                               const typename tree_graph<V, VP, EP>::vertex_type & neighbour);
            const typename tree_graph<V, VP, EP>::edge_type add_vertex(
                    const typename tree_graph<V, VP, EP>::vertex_type & vertex,
                    const typename tree_graph<V, VP, EP>::vertex_type & neighbour,
                    const typename tree_graph<V, VP, EP>::vertex_property_type & vertex_property,
                    const typename tree_graph<V, VP, EP>::edge_property_type & edge_property);

        private:
            graph_t graph;
        };

        template <typename V, typename VP, typename EP>
        const typename tree_graph<V, VP, EP>::edge_type tree_graph<V, VP, EP>::add_vertex(
                const typename tree_graph<V, VP, EP>::vertex_type & vertex,
                const typename tree_graph<V, VP, EP>::vertex_type & neighbour)
        {
            bool was_added = this->graph.add_vertex(vertex);

            if(!was_added)
                throw std::invalid_argument("Vertex already exists");

            return this->graph.add_edge_between(vertex, neighbour);
        }

        template <typename V, typename VP, typename EP>
        const typename tree_graph<V, VP, EP>::edge_type tree_graph<V, VP, EP>::add_vertex(
                const typename tree_graph<V, VP, EP>::vertex_type & vertex,
                const typename tree_graph<V, VP, EP>::vertex_type & neighbour,
                const typename tree_graph<V, VP, EP>::vertex_property_type & vertex_property,
                const typename tree_graph<V, VP, EP>::edge_property_type & edge_property)
        {
            bool was_added = this->graph.add_vertex(vertex, vertex_property);

            if(!was_added)
                throw std::invalid_argument("Vertex already exists");

            return this->graph.add_edge_between(vertex, neighbour, edge_property);
        }
    }
}

#endif
