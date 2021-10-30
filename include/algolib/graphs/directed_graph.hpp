/*!
 * \file directed_graph.hpp
 * \brief Structure of directed graph
 */
#ifndef DIRECTED_GRAPH_HPP_
#define DIRECTED_GRAPH_HPP_

#include <cstdlib>
#include <algorithm>
#include <exception>
#include <numeric>
#include <stdexcept>
#include <unordered_set>
#include <vector>
#include "algolib/graphs/simple_graph.hpp"

namespace algolib::graphs
{
    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    struct directed_graph : public virtual graph<VertexId, VertexProperty, EdgeProperty>
    {
        using vertex_id_type =
                typename graph<VertexId, VertexProperty, EdgeProperty>::vertex_id_type;
        using vertex_type = typename graph<VertexId, VertexProperty, EdgeProperty>::vertex_type;
        using edge_type = typename graph<VertexId, VertexProperty, EdgeProperty>::edge_type;
        using vertex_property_type =
                typename graph<VertexId, VertexProperty, EdgeProperty>::vertex_property_type;
        using edge_property_type =
                typename graph<VertexId, VertexProperty, EdgeProperty>::edge_property_type;

        ~directed_graph() override = default;

        //! Reverses directions of edges in the graph.
        virtual void reverse() = 0;
    };

    template <typename VertexId = size_t, typename VertexProperty = no_prop,
              typename EdgeProperty = no_prop>
    class directed_simple_graph
        : public simple_graph<VertexId, VertexProperty, EdgeProperty>,
          public virtual directed_graph<VertexId, VertexProperty, EdgeProperty>
    {
    public:
        using vertex_id_type =
                typename simple_graph<VertexId, VertexProperty, EdgeProperty>::vertex_id_type;
        using vertex_type =
                typename simple_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type;
        using edge_type = typename simple_graph<VertexId, VertexProperty, EdgeProperty>::edge_type;
        using vertex_property_type =
                typename simple_graph<VertexId, VertexProperty, EdgeProperty>::vertex_property_type;
        using edge_property_type =
                typename simple_graph<VertexId, VertexProperty, EdgeProperty>::edge_property_type;

    protected:
        using repr = typename simple_graph<VertexId, VertexProperty, EdgeProperty>::repr;

    public:
        explicit directed_simple_graph(const std::vector<vertex_id_type> & vertex_ids = {})
            : simple_graph<VertexId, VertexProperty, EdgeProperty>(vertex_ids)
        {
        }

        ~directed_simple_graph() override = default;
        directed_simple_graph(const directed_simple_graph &) = default;
        directed_simple_graph(directed_simple_graph &&) = default;
        directed_simple_graph & operator=(const directed_simple_graph &) = default;
        directed_simple_graph & operator=(directed_simple_graph &&) = default;

        size_t edges_count() const override
        {
            auto edges_set = this->representation.edges_set();

            return std::accumulate(edges_set.begin(), edges_set.end(), 0,
                                   [](size_t acc, const std::unordered_set<edge_type> & edges) {
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
        edge_type add_edge(const edge_type & edge, const edge_property_type & property) override;
        void reverse() override;

        //! \return the copy of the graph with reversed directions of edges
        directed_simple_graph<vertex_id_type, vertex_property_type, edge_property_type>
                reversed_copy() const;
    };

    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    size_t directed_simple_graph<VertexId, VertexProperty, EdgeProperty>::input_degree(
            const typename directed_simple_graph<VertexId, VertexProperty,
                                                 EdgeProperty>::vertex_type & vertex) const
    {
        size_t degree = 0;

        for(auto && edges : this->representation.edges_set())
            degree += std::count_if(edges.begin(), edges.end(),
                                    [&](auto && edge) { return edge.destination() == vertex; });

        return degree;
    }

    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    typename directed_simple_graph<VertexId, VertexProperty, EdgeProperty>::edge_type
            directed_simple_graph<VertexId, VertexProperty, EdgeProperty>::add_edge(
                    const typename directed_simple_graph<VertexId, VertexProperty,
                                                         EdgeProperty>::edge_type & edge)
    try
    {
        this->operator[](std::make_pair(edge.source(), edge.destination()));
        throw std::invalid_argument("Edge already exists");
    }
    catch(const std::out_of_range &)
    {
        this->representation.add_edge_to_source(edge);
        return edge;
    }

    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    typename directed_simple_graph<VertexId, VertexProperty, EdgeProperty>::edge_type
            directed_simple_graph<VertexId, VertexProperty, EdgeProperty>::add_edge(
                    const typename directed_simple_graph<VertexId, VertexProperty,
                                                         EdgeProperty>::edge_type & edge,
                    const typename directed_simple_graph<
                            VertexId, VertexProperty, EdgeProperty>::edge_property_type & property)
    try
    {
        this->operator[](std::make_pair(edge.source(), edge.destination()));
        throw std::invalid_argument("Edge already exists");
    }
    catch(const std::out_of_range &)
    {
        this->representation.add_edge_to_source(edge);
        this->representation.property(edge) = property;
        return edge;
    }

    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    void directed_simple_graph<VertexId, VertexProperty, EdgeProperty>::reverse()
    {
        std::vector<vertex_type> all_vertices = this->vertices();
        std::vector<vertex_id_type> vertex_ids;

        std::transform(std::begin(all_vertices), std::end(all_vertices),
                       std::back_inserter(vertex_ids), [](auto && vertex) { return vertex.id(); });

        repr new_representation(vertex_ids);

        for(auto && vertex : all_vertices)
            new_representation.property(vertex) = this->representation.property(vertex);

        for(auto && edge : edges())
        {
            edge_type new_edge = edge.reversed();

            new_representation.add_edge_to_source(new_edge);
            new_representation.property(new_edge) = this->representation.property(edge);
        }

        this->representation = new_representation;
    }

    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    directed_simple_graph<
            typename directed_simple_graph<VertexId, VertexProperty, EdgeProperty>::vertex_id_type,
            typename directed_simple_graph<VertexId, VertexProperty,
                                           EdgeProperty>::vertex_property_type,
            typename directed_simple_graph<VertexId, VertexProperty,
                                           EdgeProperty>::edge_property_type>
            directed_simple_graph<VertexId, VertexProperty, EdgeProperty>::reversed_copy() const
    {
        directed_simple_graph<vertex_id_type, vertex_property_type, edge_property_type>
                reversed_graph = *this;

        reversed_graph.reverse();
        return reversed_graph;
    }
}

#endif
