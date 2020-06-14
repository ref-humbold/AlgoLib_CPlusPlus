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
        template <typename V, typename VP, typename EP>
        struct graph
        {
            virtual ~graph() = default;

            //! \return number of vertices
            virtual size_t get_vertices_count() const = 0;

            //! \return number of edges
            virtual size_t get_edges_count() const = 0;

            //! \return vector of vertices
            virtual std::vector<V> get_vertices() const = 0;

            //! \return vector of edges
            virtual std::vector<edge<V>> get_edges() const = 0;

            /*!
             * \param vertex a vertex from this graph
             * \return vector of neighbouring vertices
             */
            virtual std::vector<V> get_neighbours(V vertex) const = 0;

            /*!
             * \param vertex a vertex from this graph
             * \return vector of edges adjacent to given vertex
             */
            virtual std::vector<edge<V>> get_adjacent_edges(V vertex) const = 0;

            /*!
             * \param vertex a vertex from this graph
             * \return the output degree of given vertex
             */
            virtual size_t get_output_degree(V vertex) const = 0;

            /*!
             * \param vertex a vertex from this graph
             * \return the input degree of given vertex
             */
            virtual size_t get_input_degree(V vertex) const = 0;
        };
    }
}

#endif
