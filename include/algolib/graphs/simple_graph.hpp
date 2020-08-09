/*!
 * \file simple_graph.hpp
 * \brief Structure of simple graph
 */
#ifndef SIMPLE_GRAPH_HPP_
#define SIMPLE_GRAPH_HPP_

#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "edge.hpp"
#include "graph.hpp"

namespace internal
{
    namespace algr = algolib::graphs;

    template <typename V, typename E, typename VP, typename EP>
    class graph_representation
    {
    public:
        explicit graph_representation(const std::vector<V> & vertices = {})
        {
            for(const V & vertex : vertices)
                this->add_vertex(vertex);
        }

        ~graph_representation() = default;
        graph_representation(const graph_representation &) = default;
        graph_representation(graph_representation &&) = default;
        graph_representation & operator=(const graph_representation &) = default;
        graph_representation & operator=(graph_representation &&) = default;

        VP & operator[](const V & vertex)
        {
            this->validate(vertex);
            return this->vertex_properties[vertex];
        }

        const VP & operator[](const V & vertex) const
        {
            this->validate(vertex);

            auto it = this->vertex_properties.find(vertex);

            if(it == this->vertex_properties.end())
                return this->default_vertex_property;

            return it->second;
        }

        EP & operator[](const E & edge)
        {
            this->validate(edge, true);
            return this->edge_properties[edge];
        }

        const EP & operator[](const E & edge) const
        {
            this->validate(edge, true);

            auto it = this->edge_properties.find(edge);

            if(it == this->edge_properties.end())
                return this->default_edge_property;

            return it->second;
        }

        size_t size() const
        {
            return this->graph_map.size();
        }

        std::vector<V> vertices() const;
        std::vector<E> edges() const;
        std::vector<std::unordered_set<E>> edges_set() const;
        std::vector<E> adjacent_edges(const V & vertex) const;
        bool add_vertex(const V & vertex);
        void add_edge_to_source(const E & edge);
        void add_edge_to_destination(const E & edge);

    private:
        void validate(const V & vertex) const;
        void validate(const E & edge, bool existing) const;

        VP default_vertex_property;
        EP default_edge_property;
        std::unordered_map<V, std::unordered_set<E>> graph_map;
        std::unordered_map<V, VP> vertex_properties;
        std::unordered_map<E, EP> edge_properties;
    };

    template <typename V, typename E, typename VP, typename EP>
    std::vector<V> graph_representation<V, E, VP, EP>::vertices() const
    {
        std::vector<V> v;

        for(auto && it = this->graph_map.cbegin(); it != this->graph_map.cend(); ++it)
            v.push_back(it->first);

        return v;
    }

    template <typename V, typename E, typename VP, typename EP>
    std::vector<E> graph_representation<V, E, VP, EP>::edges() const
    {
        std::vector<E> v;

        for(auto && it = this->graph_map.cbegin(); it != this->graph_map.cend(); ++it)
            for(auto eit = it->second.cbegin(); eit != it->second.cend(); ++eit)
                v.push_back(*eit);

        return v;
    }

    template <typename V, typename E, typename VP, typename EP>
    std::vector<std::unordered_set<E>> graph_representation<V, E, VP, EP>::edges_set() const
    {
        std::vector<std::unordered_set<E>> v;

        for(auto && it = this->graph_map.cbegin(); it != this->graph_map.cend(); ++it)
            v.push_back(it->second);

        return v;
    }

    template <typename V, typename E, typename VP, typename EP>
    std::vector<E> graph_representation<V, E, VP, EP>::adjacent_edges(const V & vertex) const
    {
        std::vector<E> v;

        this->validate(vertex);

        for(auto && it = this->graph_map.at(vertex).cbegin();
            it != this->graph_map.at(vertex).cend(); ++it)
            v.push_back(*it);

        return v;
    }

    template <typename V, typename E, typename VP, typename EP>
    bool graph_representation<V, E, VP, EP>::add_vertex(const V & vertex)
    {
        return graph_map.emplace(vertex, std::unordered_set<E>()).second;
    }

    template <typename V, typename E, typename VP, typename EP>
    void graph_representation<V, E, VP, EP>::add_edge_to_source(const E & edge)
    {
        this->validate(edge, false);
        this->graph_map.at(edge.source()).insert(edge);
    }

    template <typename V, typename E, typename VP, typename EP>
    void graph_representation<V, E, VP, EP>::add_edge_to_destination(const E & edge)
    {
        this->validate(edge, false);
        this->graph_map.at(edge.destination()).insert(edge);
    }

    template <typename V, typename E, typename VP, typename EP>
    void graph_representation<V, E, VP, EP>::validate(const V & vertex) const
    {
        if(this->graph_map.find(vertex) == this->graph_map.end())
            throw std::invalid_argument("Vertex does not belong to the graph");
    }

    template <typename V, typename E, typename VP, typename EP>
    void graph_representation<V, E, VP, EP>::validate(const E & edge, bool existing) const
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
    template <typename V, typename VP, typename EP>
    class simple_graph : public virtual graph<V, VP, EP>
    {
    protected:
        using repr = internal::graph_representation<
                typename simple_graph<V, VP, EP>::vertex_type,
                typename simple_graph<V, VP, EP>::edge_type,
                typename simple_graph<V, VP, EP>::vertex_property_type,
                typename simple_graph<V, VP, EP>::edge_property_type>;

    public:
        explicit simple_graph(
                const std::vector<typename simple_graph<V, VP, EP>::vertex_type> & vertices = {})
            : representation{repr(vertices)}
        {
        }

        ~simple_graph() override = default;
        simple_graph(const simple_graph &) = default;
        simple_graph(simple_graph &&) = default;
        simple_graph & operator=(const simple_graph &) = default;
        simple_graph & operator=(simple_graph &&) = default;

        size_t vertices_count() const override
        {
            return this->representation.size();
        }

        std::vector<typename simple_graph<V, VP, EP>::vertex_type> vertices() const override
        {
            return this->representation.vertices();
        }

        typename simple_graph<V, VP, EP>::vertex_property_type &
                operator[](const typename simple_graph<V, VP, EP>::vertex_type & vertex) override
        {
            return this->representation[vertex];
        }

        const typename simple_graph<V, VP, EP>::vertex_property_type & operator[](
                const typename simple_graph<V, VP, EP>::vertex_type & vertex) const override
        {
            return this->representation[vertex];
        }

        typename simple_graph<V, VP, EP>::edge_property_type &
                operator[](const typename simple_graph<V, VP, EP>::edge_type & edge) override
        {
            return this->representation[edge];
        }

        const typename simple_graph<V, VP, EP>::edge_property_type &
                operator[](const typename simple_graph<V, VP, EP>::edge_type & edge) const override
        {
            return this->representation[edge];
        }

        std::vector<typename simple_graph<V, VP, EP>::edge_type> adjacent_edges(
                const typename simple_graph<V, VP, EP>::vertex_type & vertex) const override
        {
            return this->representation.adjacent_edges(vertex);
        }

        typename simple_graph<V, VP, EP>::edge_type get_edge(
                const typename simple_graph<V, VP, EP>::vertex_type & source,
                const typename simple_graph<V, VP, EP>::vertex_type & destination) const override;
        std::vector<typename simple_graph<V, VP, EP>::vertex_type> neighbours(
                const typename simple_graph<V, VP, EP>::vertex_type & vertex) const override;
        bool add_vertex(const typename simple_graph<V, VP, EP>::vertex_type & vertex);
        bool add_vertex(const typename simple_graph<V, VP, EP>::vertex_type & vertex,
                        const typename simple_graph<V, VP, EP>::vertex_property_type & property);
        typename simple_graph<V, VP, EP>::edge_type
                add_edge_between(const typename simple_graph<V, VP, EP>::vertex_type & source,
                                 const typename simple_graph<V, VP, EP>::vertex_type & destination);
        typename simple_graph<V, VP, EP>::edge_type add_edge_between(
                const typename simple_graph<V, VP, EP>::vertex_type & source,
                const typename simple_graph<V, VP, EP>::vertex_type & destination,
                const typename simple_graph<V, VP, EP>::edge_property_type & property);
        virtual typename simple_graph<V, VP, EP>::edge_type
                add_edge(const typename simple_graph<V, VP, EP>::edge_type & edge) = 0;
        virtual typename simple_graph<V, VP, EP>::edge_type
                add_edge(const typename simple_graph<V, VP, EP>::edge_type & edge,
                         const typename simple_graph<V, VP, EP>::edge_property_type & property) = 0;

    protected:
        repr representation;
    };

    template <typename V, typename VP, typename EP>
    typename simple_graph<V, VP, EP>::edge_type simple_graph<V, VP, EP>::get_edge(
            const typename simple_graph<V, VP, EP>::vertex_type & source,
            const typename simple_graph<V, VP, EP>::vertex_type & destination) const
    {
        auto adjacent = this->representation.adjacent_edges(source);
        auto pos = std::find_if(adjacent.begin(), adjacent.end(),
                                [&](const typename simple_graph<V, VP, EP>::edge_type & e) {
                                    return e.get_neighbour(source) == destination;
                                });

        if(pos == adjacent.end())
            throw std::out_of_range("No edge between the vertices");

        return *pos;
    }

    template <typename V, typename VP, typename EP>
    std::vector<typename simple_graph<V, VP, EP>::vertex_type> simple_graph<V, VP, EP>::neighbours(
            const typename simple_graph<V, VP, EP>::vertex_type & vertex) const
    {
        std::vector<typename simple_graph<V, VP, EP>::vertex_type> v;
        auto adjacent = this->representation.adjacent_edges(vertex);

        std::transform(adjacent.begin(), adjacent.end(), std::back_inserter(v),
                       [&](const typename simple_graph<V, VP, EP>::edge_type & e) {
                           return e.get_neighbour(vertex);
                       });
        return v;
    }

    template <typename V, typename VP, typename EP>
    bool simple_graph<V, VP, EP>::add_vertex(
            const typename simple_graph<V, VP, EP>::vertex_type & vertex)
    {
        return this->representation.add_vertex(vertex);
    }

    template <typename V, typename VP, typename EP>
    bool simple_graph<V, VP, EP>::add_vertex(
            const typename simple_graph<V, VP, EP>::vertex_type & vertex,
            const typename simple_graph<V, VP, EP>::vertex_property_type & property)
    {
        bool was_added = this->representation.add_vertex(vertex);

        if(was_added)
            this->representation[vertex] = property;

        return was_added;
    }

    template <typename V, typename VP, typename EP>
    typename simple_graph<V, VP, EP>::edge_type simple_graph<V, VP, EP>::add_edge_between(
            const typename simple_graph<V, VP, EP>::vertex_type & source,
            const typename simple_graph<V, VP, EP>::vertex_type & destination)
    {
        return this->add_edge(typename simple_graph<V, VP, EP>::edge_type(source, destination));
    }

    template <typename V, typename VP, typename EP>
    typename simple_graph<V, VP, EP>::edge_type simple_graph<V, VP, EP>::add_edge_between(
            const typename simple_graph<V, VP, EP>::vertex_type & source,
            const typename simple_graph<V, VP, EP>::vertex_type & destination,
            const typename simple_graph<V, VP, EP>::edge_property_type & property)
    {
        return this->add_edge(typename simple_graph<V, VP, EP>::edge_type(source, destination),
                              property);
    }
}

#endif
