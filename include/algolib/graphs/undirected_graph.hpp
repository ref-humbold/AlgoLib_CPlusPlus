/*!
 * \file undirected_graph.hpp
 * \brief Structure of undirected graph
 */
#ifndef UNDIRECTED_GRAPH_HPP_
#define UNDIRECTED_GRAPH_HPP_

#include <cstdlib>
#include <algorithm>
#include <exception>
#include <stdexcept>
#include <unordered_set>
#include <vector>
#include "algolib/graphs/directed_graph.hpp"
#include "algolib/graphs/simple_graph.hpp"

namespace algolib::graphs
{
    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    struct undirected_graph : public virtual graph<VertexId, VertexProperty, EdgeProperty>
    {
        using vertex_id_type =
                typename graph<VertexId, VertexProperty, EdgeProperty>::vertex_id_type;
        using vertex_type = typename graph<VertexId, VertexProperty, EdgeProperty>::vertex_type;
        using edge_type = typename graph<VertexId, VertexProperty, EdgeProperty>::edge_type;
        using vertex_property_type =
                typename graph<VertexId, VertexProperty, EdgeProperty>::vertex_property_type;
        using edge_property_type =
                typename graph<VertexId, VertexProperty, EdgeProperty>::edge_property_type;

        ~undirected_graph() override = default;
    };

    template <typename VertexId = size_t, typename VertexProperty = no_prop,
              typename EdgeProperty = no_prop>
    class undirected_simple_graph
        : public simple_graph<VertexId, VertexProperty, EdgeProperty>,
          public virtual undirected_graph<VertexId, VertexProperty, EdgeProperty>
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
        explicit undirected_simple_graph(const std::vector<vertex_id_type> & vertex_ids = {})
            : simple_graph<VertexId, VertexProperty, EdgeProperty>(vertex_ids)
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
        edge_type add_edge(const edge_type & edge, const edge_property_type & property) override;
        directed_simple_graph<vertex_id_type, vertex_property_type, edge_property_type>
                as_directed() const;
    };

    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    size_t undirected_simple_graph<VertexId, VertexProperty, EdgeProperty>::edges_count() const
    {
        auto edges_set = this->representation.edges_set();
        std::unordered_set<edge_type> all_edges;

        std::for_each(edges_set.begin(), edges_set.end(), [&](auto && edge_set) {
            std::copy(edge_set.begin(), edge_set.end(), std::inserter(all_edges, all_edges.end()));
        });

        return all_edges.size();
    }

    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    std::vector<typename undirected_simple_graph<VertexId, VertexProperty, EdgeProperty>::edge_type>
            undirected_simple_graph<VertexId, VertexProperty, EdgeProperty>::edges() const
    {
        auto && edges_set = this->representation.edges_set();
        std::unordered_set<edge_type> all_edges;

        std::for_each(edges_set.begin(), edges_set.end(), [&](auto && edge_set) {
            std::copy(edge_set.begin(), edge_set.end(), std::inserter(all_edges, all_edges.end()));
        });

        return std::vector<edge_type>(all_edges.begin(), all_edges.end());
    }

    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    typename undirected_simple_graph<VertexId, VertexProperty, EdgeProperty>::edge_type
            undirected_simple_graph<VertexId, VertexProperty, EdgeProperty>::add_edge(
                    const typename undirected_simple_graph<VertexId, VertexProperty,
                                                           EdgeProperty>::edge_type & edge)
    try
    {
        this->operator[](std::make_pair(edge.source(), edge.destination()));
        throw std::invalid_argument("Edge already exists");
    }
    catch(const std::out_of_range &)
    {
        this->representation.add_edge_to_source(edge);
        this->representation.add_edge_to_destination(edge);
        return edge;
    }

    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    typename undirected_simple_graph<VertexId, VertexProperty, EdgeProperty>::edge_type
            undirected_simple_graph<VertexId, VertexProperty, EdgeProperty>::add_edge(
                    const typename undirected_simple_graph<VertexId, VertexProperty,
                                                           EdgeProperty>::edge_type & edge,
                    const typename undirected_simple_graph<
                            VertexId, VertexProperty, EdgeProperty>::edge_property_type & property)
    try
    {
        this->operator[](std::make_pair(edge.source(), edge.destination()));
        throw std::invalid_argument("Edge already exists");
    }
    catch(const std::out_of_range &)
    {
        this->representation.add_edge_to_source(edge);
        this->representation.add_edge_to_destination(edge);
        this->representation.property(edge) = property;
        return edge;
    }

    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    directed_simple_graph<typename undirected_simple_graph<VertexId, VertexProperty,
                                                           EdgeProperty>::vertex_id_type,
                          typename undirected_simple_graph<VertexId, VertexProperty,
                                                           EdgeProperty>::vertex_property_type,
                          typename undirected_simple_graph<VertexId, VertexProperty,
                                                           EdgeProperty>::edge_property_type>
            undirected_simple_graph<VertexId, VertexProperty, EdgeProperty>::as_directed() const
    {
        std::vector<vertex_type> all_vertices = this->vertices();
        std::vector<vertex_id_type> vertex_ids;

        std::transform(all_vertices.begin(), all_vertices.end(), std::back_inserter(vertex_ids),
                       [](const vertex_type & vertex) { return vertex.id(); });

        directed_simple_graph<vertex_id_type, vertex_property_type, edge_property_type> graph(
                vertex_ids);

        for(auto && vertex : all_vertices)
            graph.properties()[vertex] = this->properties()[vertex];

        for(auto && edge : this->edges())
        {
            graph.add_edge(edge, this->properties()[edge]);

            if(edge.source() != edge.destination())
                graph.add_edge(edge.reversed(), this->properties()[edge]);
        }

        return graph;
    }
}

#endif
