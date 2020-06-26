/*!
 * \file directed_graph.hpp
 * \brief Structure of directed graph
 */
#ifndef DIRECTED_GRAPH_HPP_
#define DIRECTED_GRAPH_HPP_

#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <unordered_set>
#include <vector>
#include <numeric>
#include "simple_graph.hpp"

namespace algolib
{
    namespace graphs
    {
        template <typename V, typename VP, typename EP>
        struct directed_graph : public virtual graph<V, VP, EP>
        {
            //! Reverses directions of edges in this graph.
            virtual void reverse() = 0;

            //! \return the copy of this graph with reversed directions of edges
            virtual directed_graph<V, VP, EP> * reversed_copy() = 0;
        };

        template <typename V = size_t, typename VP = no_prop, typename EP = no_prop>
        class directed_simple_graph : public simple_graph<V, VP, EP>,
                                      public virtual directed_graph<V, VP, EP>
        {
        public:
            using vertex_type = typename simple_graph<V, VP, EP>::vertex_type;
            using edge_type = typename simple_graph<V, VP, EP>::edge_type;
            using vertex_property_type = typename simple_graph<V, VP, EP>::vertex_property_type;
            using edge_property_type = typename simple_graph<V, VP, EP>::edge_property_type;

        protected:
            using repr = typename simple_graph<V, VP, EP>::repr;

        public:
            explicit directed_simple_graph(const std::vector<vertex_type> & vertices = {})
                : simple_graph<V, VP, EP>(vertices)
            {
            }

            ~directed_simple_graph() override = default;
            directed_simple_graph(const directed_simple_graph &) = default;
            directed_simple_graph(directed_simple_graph &&) = default;
            directed_simple_graph & operator=(const directed_simple_graph &) = default;
            directed_simple_graph & operator=(directed_simple_graph &&) = default;

            size_t edges_count() const override
            {
                std::vector<std::unordered_set<edge_type>> edges_set =
                        this->representation.edges_set();

                return std::accumulate(edges_set.begin(), edges_set.end(), 0,
                                       [](size_t acc, std::unordered_set<edge_type> edges) {
                                           return acc + edges.size();
                                       });
            }

            std::vector<edge_type> edges() const override
            {
                return this->representation.edges();
            }

            size_t output_degree(const vertex_type & vertex) const override
            {
                return this->representation.adjacent_edges(vertex).size();
            }

            size_t input_degree(const vertex_type & vertex) const override;
            edge_type add_edge(const edge_type & edge) override;
            edge_type add_edge(const edge_type & edge,
                               const edge_property_type & property) override;
            void reverse() override;
            directed_graph<V, VP, EP> * reversed_copy() override;
        };

        template <typename V, typename VP, typename EP>
        size_t directed_simple_graph<V, VP, EP>::input_degree(const vertex_type & vertex) const
        {
            size_t degree = 0;

            for(const auto & edges : this->representation.edges_set())
                degree += std::count_if(edges.begin(), edges.end(), [&](const edge_type & edge) {
                    return edge.destination() == vertex;
                });

            return degree;
        }

        template <typename V, typename VP, typename EP>
        typename directed_simple_graph<V, VP, EP>::edge_type
                directed_simple_graph<V, VP, EP>::add_edge(
                        const typename directed_simple_graph<V, VP, EP>::edge_type & edge)
        try
        {
            return this->get_edge(edge.source(), edge.destination());
        }
        catch(const std::out_of_range &)
        {
            this->representation.add_edge_to_source(edge);
            return edge;
        }

        template <typename V, typename VP, typename EP>
        typename directed_simple_graph<V, VP, EP>::edge_type
                directed_simple_graph<V, VP, EP>::add_edge(
                        const typename directed_simple_graph<V, VP, EP>::edge_type & edge,
                        const typename directed_simple_graph<V, VP, EP>::edge_property_type &
                                property)
        try
        {
            return this->get_edge(edge.source(), edge.destination());
        }
        catch(const std::out_of_range &)
        {
            this->representation.add_edge_to_source(edge);
            this->representation[edge] = property;
            return edge;
        }

        template <typename V, typename VP, typename EP>
        void directed_simple_graph<V, VP, EP>::reverse()
        {
            repr new_representation = repr(this->vertices());

            for(const vertex_type & vertex : this->vertices())
                new_representation[vertex] = this->representation[vertex];

            for(const edge_type & e : edges())
            {
                edge_type new_edge = e.reversed();
                new_representation.add_edge_to_source(new_edge);
                new_representation[new_edge] = this->representation[e];
            }

            this->representation = new_representation;
        }

        template <typename V, typename VP, typename EP>
        directed_graph<V, VP, EP> * directed_simple_graph<V, VP, EP>::reversed_copy()
        {
            directed_graph<V, VP, EP> * reversed_graph =
                    new directed_simple_graph<V, VP, EP>(*this);

            reversed_graph->reverse();
            return reversed_graph;
        }
    }
}

#endif
