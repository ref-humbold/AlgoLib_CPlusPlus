/*!
 * \file graph.hpp
 * \brief Structure of basic graph
 */
#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <cstdlib>
#include <vector>
#include "edge.hpp"
#include "properties.hpp"
#include "vertex.hpp"

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

        virtual const vertex_type & operator[](const vertex_id_type & vertex_id) const = 0;

        virtual const edge_type &
                operator[](const std::pair<vertex_id_type, vertex_id_type> & vertex_ids) const = 0;

        virtual const edge_type &
                operator[](const std::pair<vertex_type, vertex_type> & vertices) const = 0;

        virtual graph_properties & properties() = 0;

        virtual const graph_properties & properties() const = 0;

        //! \return number of vertices
        virtual size_t vertices_count() const = 0;

        //! \return number of edges
        virtual size_t edges_count() const = 0;

        //! \return vector of vertices
        virtual std::vector<vertex_type> vertices() const = 0;

        //! \return vector of edges
        virtual std::vector<edge_type> edges() const = 0;

        /*!
         * \param vertex vertex from the graph
         * \return vector of neighbouring vertices
         */
        virtual std::vector<vertex_type> neighbours(const vertex_type & vertex) const = 0;

        /*!
         * \param vertex vertex from the graph
         * \return vector of edges adjacent to given vertex
         */
        virtual std::vector<edge<VertexId>> adjacent_edges(const vertex_type & vertex) const = 0;

        /*!
         * \param vertex vertex from the graph
         * \return the output degree of given vertex
         */
        virtual size_t output_degree(const vertex_type & vertex) const = 0;

        /*!
         * \param vertex vertex from the graph
         * \return the input degree of given vertex
         */
        virtual size_t input_degree(const vertex_type & vertex) const = 0;
    };

    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    struct graph<VertexId, VertexProperty, EdgeProperty>::graph_properties
    {
        virtual graph<VertexId, VertexProperty, EdgeProperty>::vertex_property_type & operator[](
                const graph<VertexId, VertexProperty, EdgeProperty>::vertex_type & vertex) = 0;

        virtual const graph<VertexId, VertexProperty, EdgeProperty>::vertex_property_type &
                operator[](const graph<VertexId, VertexProperty, EdgeProperty>::vertex_type &
                                   vertex) const = 0;

        virtual graph<VertexId, VertexProperty, EdgeProperty>::edge_property_type & operator[](
                const graph<VertexId, VertexProperty, EdgeProperty>::edge_type & edge) = 0;

        virtual const graph<VertexId, VertexProperty, EdgeProperty>::edge_property_type &
                operator[](const graph<VertexId, VertexProperty, EdgeProperty>::edge_type & edge)
                        const = 0;
    };
}

#endif
