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

namespace algolib::graphs
{
    template <typename VertexId = size_t, typename VertexProperty = no_prop,
              typename EdgeProperty = no_prop>
    class tree_graph : public virtual undirected_graph<VertexId, VertexProperty, EdgeProperty>
    {
    public:
        using vertex_id_type =
                typename undirected_graph<VertexId, VertexProperty, EdgeProperty>::vertex_id_type;
        using vertex_type =
                typename undirected_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type;
        using edge_type =
                typename undirected_graph<VertexId, VertexProperty, EdgeProperty>::edge_type;
        using vertex_property_type = typename undirected_graph<VertexId, VertexProperty,
                                                               EdgeProperty>::vertex_property_type;
        using edge_property_type = typename undirected_graph<VertexId, VertexProperty,
                                                             EdgeProperty>::edge_property_type;

    protected:
        using graph_t =
                undirected_simple_graph<vertex_id_type, vertex_property_type, edge_property_type>;

    public:
        explicit tree_graph(const vertex_id_type & vertex_id) : graph{graph_t({vertex_id})}
        {
        }

        ~tree_graph() override = default;
        tree_graph(const tree_graph &) = default;
        tree_graph(tree_graph &&) = default;
        tree_graph & operator=(const tree_graph &) = default;
        tree_graph & operator=(tree_graph &&) = default;

        const vertex_type & operator[](const vertex_id_type & vertex_id) const override
        {
            return this->graph[vertex_id];
        }

        const edge_type & operator[](
                const std::pair<vertex_id_type, vertex_id_type> & vertex_ids) const override
        {
            return this->graph[vertex_ids];
        }

        const edge_type &
                operator[](const std::pair<vertex_type, vertex_type> & vertices) const override
        {
            return this->graph[vertices];
        }

        typename graph<VertexId, VertexProperty, EdgeProperty>::graph_properties &
                properties() override
        {
            return this->graph.properties();
        }

        const typename graph<VertexId, VertexProperty, EdgeProperty>::graph_properties &
                properties() const override
        {
            return this->graph.properties();
        }

        size_t vertices_count() const override
        {
            return this->graph.vertices_count();
        }

        size_t edges_count() const override
        {
            return this->graph.edges_count();
        }

        std::vector<vertex_type> vertices() const override
        {
            return this->graph.vertices();
        }

        std::vector<edge_type> edges() const override
        {
            return this->graph.edges();
        }

        std::vector<edge_type> adjacent_edges(const vertex_type & vertex) const override
        {
            return this->graph.adjacent_edges(vertex);
        }

        std::vector<vertex_type> neighbours(const vertex_type & vertex) const override
        {
            return this->graph.neighbours(vertex);
        }

        size_t output_degree(const vertex_type & vertex) const override
        {
            return this->graph.output_degree(vertex);
        }

        size_t input_degree(const vertex_type & vertex) const override
        {
            return this->graph.input_degree(vertex);
        }

        directed_simple_graph<vertex_id_type, vertex_property_type, edge_property_type>
                as_directed() const
        {
            return this->graph.as_directed();
        }

        edge_type add_vertex(const vertex_id_type & vertex, const vertex_type & neighbour);
        edge_type add_vertex(const vertex_id_type & vertex, const vertex_type & neighbour,
                             const vertex_property_type & vertex_property,
                             const edge_property_type & edge_property);
        edge_type add_vertex(const vertex_type & vertex, const vertex_type & neighbour);
        edge_type add_vertex(const vertex_type & vertex, const vertex_type & neighbour,
                             const vertex_property_type & vertex_property,
                             const edge_property_type & edge_property);

    private:
        graph_t graph;
    };

    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    typename tree_graph<VertexId, VertexProperty, EdgeProperty>::edge_type
            tree_graph<VertexId, VertexProperty, EdgeProperty>::add_vertex(
                    const typename tree_graph<VertexId, VertexProperty,
                                              EdgeProperty>::vertex_id_type & vertex_id,
                    const typename tree_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type &
                            neighbour)
    {
        return this->add_vertex(vertex_type(vertex_id), neighbour);
    }

    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    typename tree_graph<VertexId, VertexProperty, EdgeProperty>::edge_type
            tree_graph<VertexId, VertexProperty, EdgeProperty>::add_vertex(
                    const typename tree_graph<VertexId, VertexProperty,
                                              EdgeProperty>::vertex_id_type & vertex_id,
                    const typename tree_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type &
                            neighbour,
                    const typename tree_graph<VertexId, VertexProperty,
                                              EdgeProperty>::vertex_property_type & vertex_property,
                    const typename tree_graph<VertexId, VertexProperty,
                                              EdgeProperty>::edge_property_type & edge_property)
    {
        return this->add_vertex(vertex_type(vertex_id), neighbour, vertex_property, edge_property);
    }

    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    typename tree_graph<VertexId, VertexProperty, EdgeProperty>::edge_type
            tree_graph<VertexId, VertexProperty, EdgeProperty>::add_vertex(
                    const typename tree_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type &
                            vertex,
                    const typename tree_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type &
                            neighbour)
    {
        vertex_type new_vertex = this->graph.add_vertex(vertex);

        return this->graph.add_edge_between(new_vertex, neighbour);
    }

    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    typename tree_graph<VertexId, VertexProperty, EdgeProperty>::edge_type
            tree_graph<VertexId, VertexProperty, EdgeProperty>::add_vertex(
                    const typename tree_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type &
                            vertex,
                    const typename tree_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type &
                            neighbour,
                    const typename tree_graph<VertexId, VertexProperty,
                                              EdgeProperty>::vertex_property_type & vertex_property,
                    const typename tree_graph<VertexId, VertexProperty,
                                              EdgeProperty>::edge_property_type & edge_property)
    {
        vertex_type new_vertex = this->graph.add_vertex(vertex, vertex_property);

        return this->graph.add_edge_between(new_vertex, neighbour, edge_property);
    }
}

#endif
