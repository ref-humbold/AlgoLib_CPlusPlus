/*!
 * \file graph.hpp
 * \brief Structure of basic graph
 */
#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <cstdlib>
#include <vector>
#include "edge.hpp"

namespace algolib
{
    namespace graphs
    {
        struct no_prop
        {
        };

        template <typename V, typename VP, typename EP>
        struct graph
        {
            using vertex_type = V;
            using edge_type = edge<vertex_type>;
            using vertex_property_type = VP;
            using edge_property_type = EP;

            virtual ~graph() = default;

            //! \return number of vertices
            virtual size_t vertices_count() const = 0;

            //! \return number of edges
            virtual size_t edges_count() const = 0;

            //! \return vector of vertices
            virtual std::vector<vertex_type> vertices() const = 0;

            //! \return vector of edges
            virtual std::vector<edge_type> edges() const = 0;

            virtual vertex_property_type & operator[](const vertex_type & vertex) = 0;

            virtual edge_property_type & operator[](const edge_type & edge) = 0;

            /*!
             * \param source source vertex
             * \param destination destination vertex
             * \return the edge between the vertices
             * \throw out_of_range if no edge
             */
            virtual edge_type get_edge(const vertex_type & source,
                                       const vertex_type & destination) const = 0;

            /*!
             * \param vertex a vertex from this graph
             * \return vector of neighbouring vertices
             */
            virtual std::vector<vertex_type> neighbours(const vertex_type & vertex) const = 0;

            /*!
             * \param vertex a vertex from this graph
             * \return vector of edges adjacent to given vertex
             */
            virtual std::vector<edge<V>> adjacent_edges(const vertex_type & vertex) const = 0;

            /*!
             * \param vertex a vertex from this graph
             * \return the output degree of given vertex
             */
            virtual size_t output_degree(const vertex_type & vertex) const = 0;

            /*!
             * \param vertex a vertex from this graph
             * \return the input degree of given vertex
             */
            virtual size_t input_degree(const vertex_type & vertex) const = 0;
        };
    }
}

#endif
