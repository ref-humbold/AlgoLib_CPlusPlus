/*!
 * \file graph.hpp
 * \brief Structure of basic graph.
 */
#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <cstdlib>
#include <vector>
#include "algolib/graphs/edge.hpp"
#include "algolib/graphs/properties.hpp"
#include "algolib/graphs/vertex.hpp"

namespace algolib::graphs
{
    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    struct graph
    {
        using vertex_id_type = VertexId;
        using vertex_type = vertex<vertex_id_type>;
        using edge_type = edge<vertex_id_type>;
        using vertex_property_type = VertexProperty;
        using edge_property_type = EdgeProperty;

        struct graph_properties;

        virtual ~graph() = default;

        /*!
         * \brief Gets the vertex from this graph with given identifier.
         * \param vertex_id the vertex identifier
         * \return the vertex with the identifier
         * \throw std::out_of_range if no such vertex exists
         */
        virtual const vertex_type & operator[](const vertex_id_type & vertex_id) const = 0;

        /*!
         * \brief Gets the edge between vertices of given identifiers.
         * \param vertex_ids the identifiers of source and destination vertices
         * \return the edge between the vertices
         * \throw std::out_of_range if no such edge exists
         */
        virtual const edge_type & operator[](
                const std::pair<vertex_id_type, vertex_id_type> & vertex_ids) const = 0;

        /*!
         * Gets the edge between given vertices.
         * \param vertices the source and destination vertices
         * \return the edge between the vertices
         * \throw std::out_of_range if no such edge exists
         */
        virtual const edge_type & operator[](
                const std::pair<vertex_type, vertex_type> & vertices) const = 0;

        virtual graph_properties & properties() = 0;

        virtual const graph_properties & properties() const = 0;

        /*!
         * \brief Gets the number of vertices in this graph.
         * \return the number of vertices
         */
        virtual size_t vertices_count() const = 0;

        /*!
         * \brief Gets the number of edges in this graph.
         * \return the number of edges
         */
        virtual size_t edges_count() const = 0;

        /*!
         * \brief Gets all vertices in this graph.
         * \return all vertices
         */
        virtual std::vector<vertex_type> vertices() const = 0;

        /*!
         * \brief Gets all edges in this graph.
         * \return all edges
         */
        virtual std::vector<edge_type> edges() const = 0;

        /*!
         * \brief Gets the neighbours of given vertex.
         * \param vertex the vertex from this graph
         * \return the neighbouring vertices
         */
        virtual std::vector<vertex_type> neighbours(const vertex_type & vertex) const = 0;

        /*!
         * \brief Gets the adjacent edges of given vertex.
         * \param vertex the vertex from this graph
         * \return the edges adjacent to the vertex
         */
        virtual std::vector<edge<VertexId>> adjacent_edges(const vertex_type & vertex) const = 0;

        /*!
         * \brief Gets the output degree of given vertex.
         * \param vertex the vertex from the graph
         * \return the output degree of the vertex
         */
        virtual size_t output_degree(const vertex_type & vertex) const = 0;

        /*!
         * \brief Gets the input degree of given vertex.
         * \param vertex the vertex from the graph
         * \return the input degree of the vertex
         */
        virtual size_t input_degree(const vertex_type & vertex) const = 0;
    };

    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    struct graph<VertexId, VertexProperty, EdgeProperty>::graph_properties
    {
        /*!
         * \brief Gets or sets the property of given vertex.
         * \param vertex the vertex from this graph
         * \return the property of the vertex
         */
        virtual graph<VertexId, VertexProperty, EdgeProperty>::vertex_property_type & operator[](
                const graph<VertexId, VertexProperty, EdgeProperty>::vertex_type & vertex) = 0;

        /*!
         * \brief Gets or sets the property of given vertex.
         * \param vertex the vertex from this graph
         * \return the property of the vertex
         * \throw std::out_of_range if no such property
         */
        virtual graph<VertexId, VertexProperty, EdgeProperty>::vertex_property_type & at(
                const graph<VertexId, VertexProperty, EdgeProperty>::vertex_type & vertex) = 0;

        /*!
         * \brief Gets the property of given vertex.
         * \param vertex the vertex from this graph
         * \return the property of the vertex
         * \throw std::out_of_range if no such property
         */
        virtual const graph<VertexId, VertexProperty, EdgeProperty>::vertex_property_type & at(
                const graph<VertexId, VertexProperty, EdgeProperty>::vertex_type & vertex)
                const = 0;

        /*!
         * \brief Gets or sets the property of given edge.
         * \param edge the edge from this graph
         * \return the property of the edge
         */
        virtual graph<VertexId, VertexProperty, EdgeProperty>::edge_property_type & operator[](
                const graph<VertexId, VertexProperty, EdgeProperty>::edge_type & edge) = 0;

        /*!
         * \brief Gets or sets the property of given edge.
         * \param edge the edge from this graph
         * \return the property of the edge
         * \throw std::out_of_range if no such property
         */
        virtual graph<VertexId, VertexProperty, EdgeProperty>::edge_property_type & at(
                const graph<VertexId, VertexProperty, EdgeProperty>::edge_type & edge) = 0;

        /*!
         * \brief Gets the property of given edge.
         * \param edge the edge from this graph
         * \return the property of the edge
         * \throw std::out_of_range if no such property
         */
        virtual const graph<VertexId, VertexProperty, EdgeProperty>::edge_property_type & at(
                const graph<VertexId, VertexProperty, EdgeProperty>::edge_type & edge) const = 0;
    };
}

#endif
