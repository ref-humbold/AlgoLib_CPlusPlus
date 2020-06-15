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
        struct none
        {
        };

        template <typename Vertex = size_t, typename VertexProperty = none,
                  typename EdgeProperty = none>
        struct graph
        {
            virtual ~graph() = default;

            //! \return number of vertices
            virtual size_t vertices_count() const = 0;

            //! \return number of edges
            virtual size_t edges_count() const = 0;

            //! \return vector of vertices
            virtual std::vector<Vertex> vertices() const = 0;

            //! \return vector of edges
            virtual std::vector<edge<Vertex>> edges() const = 0;

            /*!
             * \param vertex a vertex from this graph
             * \return vector of neighbouring vertices
             */
            virtual std::vector<Vertex> neighbours(Vertex vertex) const = 0;

            /*!
             * \param vertex a vertex from this graph
             * \return vector of edges adjacent to given vertex
             */
            virtual std::vector<edge<Vertex>> adjacent_edges(Vertex vertex) const = 0;

            /*!
             * \param vertex a vertex from this graph
             * \return the output degree of given vertex
             */
            virtual size_t output_degree(Vertex vertex) const = 0;

            /*!
             * \param vertex a vertex from this graph
             * \return the input degree of given vertex
             */
            virtual size_t input_degree(Vertex vertex) const = 0;
        };
    }
}

#endif
