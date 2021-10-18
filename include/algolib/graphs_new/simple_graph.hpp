/*!
 * \file simple_graph.hpp
 * \brief Structure of simple graph
 */
#ifndef SIMPLE_GRAPH_HPP_
#define SIMPLE_GRAPH_HPP_

#include <cstdlib>
#include <algorithm>
#include <exception>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "graph.hpp"

namespace internal
{
    namespace algr = algolib::graphs;

    template <typename Graph>
    class graph_representation
    {
    public:
        using vertex_id_type = typename Graph::vertex_id_type;
        using vertex_type = typename Graph::vertex_type;
        using edge_type = typename Graph::edge_type;
        using vertex_property_type = typename Graph::vertex_property_type;
        using edge_property_type = typename Graph::edge_property_type;

        explicit graph_representation(const std::vector<vertex_id_type> & vertex_ids = {})
        {
            for(const vertex_id_type & vertex_id : vertex_ids)
                this->graph_map.emplace(vertex_type(vertex_id), {});
        }

        ~graph_representation() = default;
        graph_representation(const graph_representation &) = default;
        graph_representation(graph_representation &&) = default;
        graph_representation & operator=(const graph_representation &) = default;
        graph_representation & operator=(graph_representation &&) = default;

        size_t size() const
        {
            return this->graph_map.size();
        }

        const vertex_type & operator[](const vertex_id_type & vertex_id);
        const edge_type & operator[](const std::pair<vertex_id_type, vertex_id_type> & vertex_ids);

        std::vector<vertex_type> vertices() const;
        std::vector<edge_type> edges() const;
        std::vector<std::unordered_set<edge_type>> edges_set() const;
        std::vector<edge_type> adjacent_edges(const vertex_type & vertex) const;
        vertex_property_type & property(const vertex_type & vertex);
        const vertex_property_type & property(const vertex_type & vertex) const;
        edge_property_type & property(const edge_type & edge);
        const edge_property_type & property(const edge_type & edge) const;
        bool add_vertex(const vertex_type & vertex);
        void add_edge_to_source(const edge_type & edge);
        void add_edge_to_destination(const edge_type & edge);

    private:
        void validate(const vertex_type & vertex) const;
        void validate(const edge_type & edge, bool existing) const;

        vertex_property_type default_vertex_property;
        edge_property_type default_edge_property;
        std::unordered_map<vertex_type, std::unordered_set<edge_type>> graph_map;
        std::unordered_map<vertex_type, vertex_property_type> vertex_properties;
        std::unordered_map<edge_type, edge_property_type> edge_properties;
    };

    template <typename Graph>
    const typename graph_representation<Graph>::vertex_type &
            graph_representation<Graph>::operator[](
                    const typename graph_representation<Graph>::vertex_id_type & vertex_id)
    {
        auto && it = std::find_if(this->graph_map.begin(), this->graph_map.end(),
                                  [&](auto && entry) { return entry.first.id == vertex_id; });

        if(it != this->graph_map.end())
            return it->first;

        throw std::out_of_range("Vertex not found");
    }

    template <typename Graph>
    const typename graph_representation<Graph>::edge_type & graph_representation<Graph>::operator[](
            const std::pair<typename graph_representation<Graph>::vertex_id_type,
                            typename graph_representation<Graph>::vertex_id_type> & vertex_ids)
    {
        vertex_id_type source_id = vertex_ids.first, destination_id = vertex_ids.second;

        auto && entry_it = std::find_if(this->graph_map.begin(), this->graph_map.end(),
                                        [&](auto && entry) { return entry.first.id == source_id; });

        if(entry_it != this->graph_map.end())
        {
            auto && edge_it = std::find_if(
                    std::begin(entry_it->second), std::end(entry_it->second), [&](auto && edge) {
                        edge.get_neighbour(entry_it->first).id == destination_id;
                    });

            if(edge_it != std::end(entry_it->second))
                return *edge_it;
        }

        throw std::out_of_range("Edge not found");
    }

    template <typename Graph>
    std::vector<typename graph_representation<Graph>::vertex_type>
            graph_representation<Graph>::vertices() const
    {
        std::vector<vertex_type> result;

        std::transform(this->graph_map.begin(), this->graph_map.end(), std::back_inserter(result),
                       [](auto && entry) { return entry.first; });
        return result;
    }

    template <typename Graph>
    std::vector<typename graph_representation<Graph>::edge_type>
            graph_representation<Graph>::edges() const
    {
        std::vector<edge_type> result;

        std::for_each(this->graph_map.begin(), this->graph_map.end(), [&](auto && entry) {
            std::copy(entry->second.begin(), entry->second.end(), std::back_inserter(result));
        });
        return result;
    }

    template <typename Graph>
    std::vector<std::unordered_set<typename graph_representation<Graph>::edge_type>>
            graph_representation<Graph>::edges_set() const
    {
        std::vector<std::unordered_set<typename graph_representation<Graph>::edge_type>> result;

        std::transform(this->graph_map.begin(), this->graph_map.end(), std::back_inserter(result),
                       [](auto && entry) { return entry.second; });
        return result;
    }

    template <typename Graph>
    std::vector<typename graph_representation<Graph>::edge_type>
            graph_representation<Graph>::adjacent_edges(
                    const typename graph_representation<Graph>::vertex_type & vertex) const
    {
        std::vector<typename graph_representation<Graph>::edge_type> result;

        this->validate(vertex);
        std::copy(this->graph_map.at(vertex).begin(), this->graph_map.at(vertex).end(),
                  std::back_inserter(result));
        return result;
    }

    template <typename Graph>
    typename graph_representation<Graph>::vertex_property_type &
            graph_representation<Graph>::property(
                    const typename graph_representation<Graph>::vertex_type & vertex)
    {
        this->validate(vertex);
        return this->vertex_properties[vertex];
    }

    template <typename Graph>
    const typename graph_representation<Graph>::vertex_property_type &
            graph_representation<Graph>::property(
                    const typename graph_representation<Graph>::vertex_type & vertex) const
    {
        this->validate(vertex);

        auto && it = this->vertex_properties.find(vertex);

        return it == this->vertex_properties.end() ? this->default_vertex_property : it->second;
    }

    template <typename Graph>
    typename graph_representation<Graph>::edge_property_type &
            graph_representation<Graph>::property(
                    const typename graph_representation<Graph>::edge_type & edge)
    {
        this->validate(edge, true);
        return this->edge_properties[edge];
    }

    template <typename Graph>
    const typename graph_representation<Graph>::edge_property_type &
            graph_representation<Graph>::property(
                    const typename graph_representation<Graph>::edge_type & edge) const
    {
        this->validate(edge, true);

        auto && it = this->edge_properties.find(edge);

        return it == this->edge_properties.end() ? this->default_edge_property : it->second;
    }

    template <typename Graph>
    bool graph_representation<Graph>::add_vertex(
            const typename graph_representation<Graph>::vertex_type & vertex)
    {
        return graph_map.emplace(vertex, std::unordered_set<edge_type>()).second;
    }

    template <typename Graph>
    void graph_representation<Graph>::add_edge_to_source(
            const typename graph_representation<Graph>::edge_type & edge)
    {
        this->validate(edge, false);
        this->graph_map.at(edge.source()).insert(edge);
    }

    template <typename Graph>
    void graph_representation<Graph>::add_edge_to_destination(
            const typename graph_representation<Graph>::edge_type & edge)
    {
        this->validate(edge, false);
        this->graph_map.at(edge.destination()).insert(edge);
    }

    template <typename Graph>
    void graph_representation<Graph>::validate(
            const typename graph_representation<Graph>::vertex_type & vertex) const
    {
        if(this->graph_map.find(vertex) == this->graph_map.end())
            throw std::invalid_argument("Vertex does not belong to the graph");
    }

    template <typename Graph>
    void graph_representation<Graph>::validate(
            const typename graph_representation<Graph>::edge_type & edge, bool existing) const
    {
        if(this->graph_map.find(edge.source()) == this->graph_map.end()
           || this->graph_map.find(edge.destination()) == this->graph_map.end())
            throw std::invalid_argument("Edge does not belong to the graph");

        if(existing
           && this->graph_map.at(edge.source()).find(edge)
                      == this->graph_map.at(edge.source()).end()
           && this->graph_map.at(edge.destination()).find(edge)
                      == this->graph_map.at(edge.destination()).end())
            throw std::invalid_argument("Edge does not belong to the graph");
    }
}

namespace algolib::graphs
{
    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    class simple_graph : public virtual graph<VertexId, VertexProperty, EdgeProperty>
    {
    public:
        using vertex_id_type =
                typename graph<VertexId, VertexProperty, EdgeProperty>::vertex_id_type;
        using vertex_type = typename graph<VertexId, VertexProperty, EdgeProperty>::vertex_type;
        using edge_type = typename graph<VertexId, VertexProperty, EdgeProperty>::edge_type;
        using vertex_property_type =
                typename graph<VertexId, VertexProperty, EdgeProperty>::vertex_property_type;
        using edge_property_type =
                typename graph<VertexId, VertexProperty, EdgeProperty>::edge_property_type;

    protected:
        using repr = internal::graph_representation<
                simple_graph<VertexId, VertexProperty, EdgeProperty>>;

    private:
        class graph_properties_impl;

    public:
        explicit simple_graph(const std::vector<vertex_id_type> & vertex_ids = {})
            : representation{repr(vertex_ids)}, graph_properties_{graph_properties_impl(*this)}
        {
        }

        ~simple_graph() override = default;
        simple_graph(const simple_graph &) = default;
        simple_graph(simple_graph &&) = default;
        simple_graph & operator=(const simple_graph &) = default;
        simple_graph & operator=(simple_graph &&) = default;

        typename graph<VertexId, VertexProperty, EdgeProperty>::graph_properties &
                properties() override
        {
            return this->graph_properties_;
        }

        const typename graph<VertexId, VertexProperty, EdgeProperty>::graph_properties &
                properties() const override
        {
            return this->graph_properties_;
        }

        const vertex_type & operator[](const vertex_id_type & vertex_id) const override
        {
            return this->representation[vertex_id];
        }

        const edge_type & operator[](
                const std::pair<vertex_id_type, vertex_id_type> & vertices) const override
        {
            return this->representation[vertices];
        }

        size_t vertices_count() const override
        {
            return this->representation.size();
        }

        std::vector<vertex_type> vertices() const override
        {
            return this->representation.vertices();
        }

        std::vector<edge_type> adjacent_edges(const vertex_type & vertex) const override
        {
            return this->representation.adjacent_edges(vertex);
        }

        std::vector<vertex_type> neighbours(const vertex_type & vertex) const override;

        vertex_type add_vertex(const vertex_id_type & vertex_id);
        vertex_type add_vertex(const vertex_id_type & vertex_id,
                               const vertex_property_type & property);
        vertex_type add_vertex(const vertex_type & vertex);
        vertex_type add_vertex(const vertex_type & vertex, const vertex_property_type & property);

        edge_type add_edge_between(const vertex_type & source, const vertex_type & destination);
        edge_type add_edge_between(const vertex_type & source, const vertex_type & destination,
                                   const edge_property_type & property);

        virtual edge_type add_edge(const edge_type & edge) = 0;
        virtual edge_type add_edge(const edge_type & edge, const edge_property_type & property) = 0;

    protected:
        repr representation;

    private:
        graph_properties_impl graph_properties_;
    };

    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    std::vector<typename simple_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type>
            simple_graph<VertexId, VertexProperty, EdgeProperty>::neighbours(
                    const typename simple_graph<VertexId, VertexProperty,
                                                EdgeProperty>::vertex_type & vertex) const
    {
        std::vector<vertex_type> result;
        auto adjacent = this->representation.adjacent_edges(vertex);

        std::transform(adjacent.begin(), adjacent.end(), std::back_inserter(result),
                       [&](auto && edge) { return edge.get_neighbour(vertex); });
        return result;
    }

    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    typename simple_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type
            simple_graph<VertexId, VertexProperty, EdgeProperty>::add_vertex(
                    const typename simple_graph<VertexId, VertexProperty,
                                                EdgeProperty>::vertex_id_type & vertex_id)
    {
        return this->add_vertex(vertex_type(vertex_id));
    }

    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    typename simple_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type
            simple_graph<VertexId, VertexProperty, EdgeProperty>::add_vertex(
                    const typename simple_graph<VertexId, VertexProperty,
                                                EdgeProperty>::vertex_id_type & vertex_id,
                    const typename simple_graph<VertexId, VertexProperty,
                                                EdgeProperty>::vertex_property_type & property)
    {
        return this->add_vertex(vertex_type(vertex_id), property);
    }

    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    typename simple_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type
            simple_graph<VertexId, VertexProperty, EdgeProperty>::add_vertex(
                    const typename simple_graph<VertexId, VertexProperty,
                                                EdgeProperty>::vertex_type & vertex)
    {
        bool was_added = this->representation.add_vertex(vertex);

        if(was_added)
            return vertex;

        throw std::invalid_argument("Vertex already exists");
    }

    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    typename simple_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type
            simple_graph<VertexId, VertexProperty, EdgeProperty>::add_vertex(
                    const typename simple_graph<VertexId, VertexProperty,
                                                EdgeProperty>::vertex_type & vertex,
                    const typename simple_graph<VertexId, VertexProperty,
                                                EdgeProperty>::vertex_property_type & property)
    {
        bool was_added = this->representation.add_vertex(vertex);

        if(was_added)
        {
            this->representation.property(vertex) = property;
            return vertex;
        }

        throw std::invalid_argument("Vertex already exists");
    }

    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    typename simple_graph<VertexId, VertexProperty, EdgeProperty>::edge_type
            simple_graph<VertexId, VertexProperty, EdgeProperty>::add_edge_between(
                    const typename simple_graph<VertexId, VertexProperty,
                                                EdgeProperty>::vertex_type & source,
                    const typename simple_graph<VertexId, VertexProperty,
                                                EdgeProperty>::vertex_type & destination)
    {
        return this->add_edge(edge_type(source, destination));
    }

    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    typename simple_graph<VertexId, VertexProperty, EdgeProperty>::edge_type
            simple_graph<VertexId, VertexProperty, EdgeProperty>::add_edge_between(
                    const typename simple_graph<VertexId, VertexProperty,
                                                EdgeProperty>::vertex_type & source,
                    const typename simple_graph<VertexId, VertexProperty,
                                                EdgeProperty>::vertex_type & destination,
                    const typename simple_graph<VertexId, VertexProperty,
                                                EdgeProperty>::edge_property_type & property)
    {
        return this->add_edge(edge_type(source, destination), property);
    }

    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    class simple_graph<VertexId, VertexProperty, EdgeProperty>::graph_properties_impl
        : public virtual graph<VertexId, VertexProperty, EdgeProperty>::graph_properties
    {
    public:
        explicit graph_properties_impl(simple_graph<VertexId, VertexProperty, EdgeProperty> & graph)
            : graph{graph}
        {
        }

        simple_graph<VertexId, VertexProperty, EdgeProperty>::vertex_property_type & operator[](
                const simple_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type & vertex)
                override
        {
            return graph.representation.property(vertex);
        }

        const simple_graph<VertexId, VertexProperty, EdgeProperty>::vertex_property_type &
                operator[](const simple_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type &
                                   vertex) const override
        {
            return graph.representation.property(vertex);
        }

        simple_graph<VertexId, VertexProperty, EdgeProperty>::edge_property_type & operator[](
                const simple_graph<VertexId, VertexProperty, EdgeProperty>::edge_type & edge)
                override
        {
            return graph.representation.property(edge);
        }

        const simple_graph<VertexId, VertexProperty, EdgeProperty>::edge_property_type & operator[](
                const simple_graph<VertexId, VertexProperty, EdgeProperty>::edge_type & edge)
                const override
        {
            return graph.representation.property(edge);
        }

    private:
        simple_graph<VertexId, VertexProperty, EdgeProperty> & graph;
    };
}

#endif
