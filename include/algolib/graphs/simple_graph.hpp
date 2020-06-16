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
#include <initializer_list>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "edge.hpp"
#include "graph.hpp"

namespace internal
{
    namespace algr = algolib::graphs;

    template <typename Vertex = size_t, typename VertexProperty = algr::none,
              typename EdgeProperty = algr::none>
    class graph_representation
    {
    public:
        explicit graph_representation(const std::vector<Vertex> & vertices = {})
        {
            for(const Vertex & vertex : vertices)
                graph_map.emplace(vertex, std::unordered_set<algr::edge<Vertex>>());
        }

        ~graph_representation() = default;
        graph_representation(const graph_representation &) = default;
        graph_representation(graph_representation &&) = default;
        graph_representation & operator=(const graph_representation &) = default;
        graph_representation & operator=(graph_representation &&) = default;

        VertexProperty & operator[](const Vertex & vertex)
        {
            validate(vertex);
            return vertex_properties[vertex];
        }

        EdgeProperty & operator[](const algr::edge<Vertex> & edge)
        {
            validate(edge, true);
            return edge_properties[edge];
        }

        size_t size()
        {
            return graph_map.size();
        }

        std::vector<Vertex> vertices();
        std::vector<algr::edge<Vertex>> edges();
        std::vector<std::unordered_set<algr::edge<Vertex>>> edges_set();
        std::vector<algr::edge<Vertex>> adjacent_edges(const Vertex & vertex);
        bool add_vertex(const Vertex & vertex);
        void add_edge_to_source(const algr::edge<Vertex> & edge);
        void add_edge_to_destination(const algr::edge<Vertex> & edge);

    private:
        void validate(const Vertex & vertex);
        void validate(const algr::edge<Vertex> & edge, bool existing);

        std::unordered_map<Vertex, std::unordered_set<algr::edge<Vertex>>> graph_map;
        std::unordered_map<Vertex, VertexProperty> vertex_properties;
        std::unordered_map<algr::edge<Vertex>, EdgeProperty> edge_properties;
    };

    template <typename Vertex, typename VertexProperty, typename EdgeProperty>
    std::vector<Vertex> graph_representation<Vertex, VertexProperty, EdgeProperty>::vertices()
    {
        std::vector<Vertex> v;

        for(auto it = graph_map.cbegin(); it != graph_map.cend(); ++it)
            v.push_back(it->first);

        return v;
    }

    template <typename Vertex, typename VertexProperty, typename EdgeProperty>
    std::vector<algr::edge<Vertex>>
            graph_representation<Vertex, VertexProperty, EdgeProperty>::edges()
    {
        std::vector<algr::edge<Vertex>> v;

        for(auto it = graph_map.cbegin(); it != graph_map.cend(); ++it)
            for(auto eit = it->second.cbegin(); eit != it->second.cend(); ++eit)
                v.push_back(*eit);

        return v;
    }

    template <typename Vertex, typename VertexProperty, typename EdgeProperty>
    std::vector<std::unordered_set<algr::edge<Vertex>>>
            graph_representation<Vertex, VertexProperty, EdgeProperty>::edges_set()
    {
        std::vector<std::unordered_set<algr::edge<Vertex>>> v;

        for(auto it = graph_map.cbegin(); it != graph_map.cend(); ++it)
            v.push_back(it->second);

        return v;
    }

    template <typename Vertex, typename VertexProperty, typename EdgeProperty>
    std::vector<algr::edge<Vertex>>
            graph_representation<Vertex, VertexProperty, EdgeProperty>::adjacent_edges(
                    const Vertex & vertex)
    {
        std::vector<algr::edge<Vertex>> v;

        validate(vertex);

        for(auto it = graph_map.at(vertex).cbegin(); it != graph_map.at(vertex).cend(); ++it)
            v.push_back(*it);

        return v;
    }

    template <typename Vertex, typename VertexProperty, typename EdgeProperty>
    bool graph_representation<Vertex, VertexProperty, EdgeProperty>::add_vertex(
            const Vertex & vertex)
    {
        if(graph_map.find(vertex) == graph_map.end())
        {
            graph_map.emplace(vertex, std::unordered_set<algr::edge<Vertex>>());
            return true;
        }

        return false;
    }

    template <typename Vertex, typename VertexProperty, typename EdgeProperty>
    void graph_representation<Vertex, VertexProperty, EdgeProperty>::add_edge_to_source(
            const algr::edge<Vertex> & edge)
    {
        validate(edge, false);
        graph_map.at(edge.source()).insert(edge);
    }

    template <typename Vertex, typename VertexProperty, typename EdgeProperty>
    void graph_representation<Vertex, VertexProperty, EdgeProperty>::add_edge_to_destination(
            const algr::edge<Vertex> & edge)
    {
        validate(edge, false);
        graph_map.at(edge.destination()).insert(edge);
    }

    template <typename Vertex, typename VertexProperty, typename EdgeProperty>
    void graph_representation<Vertex, VertexProperty, EdgeProperty>::validate(const Vertex & vertex)
    {
        if(graph_map.find(vertex) == graph_map.end())
            throw std::invalid_argument("Vertex does not belong to the graph");
    }

    template <typename Vertex, typename VertexProperty, typename EdgeProperty>
    void graph_representation<Vertex, VertexProperty, EdgeProperty>::validate(
            const algr::edge<Vertex> & edge, bool existing)
    {
        if(graph_map.find(edge.source()) == graph_map.end()
           || graph_map.find(edge.destination()) == graph_map.end())
            throw std::invalid_argument("Edge does not belong to the graph");

        if(existing && graph_map.at(edge.source()).find(edge) == graph_map.at(edge.source()).end()
           && graph_map.at(edge.destination()).find(edge) == graph_map.at(edge.destination()).end())
            throw std::invalid_argument("Edge does not belong to the graph");
    }
}

namespace algolib
{
    namespace graphs
    {
        template <typename Vertex = size_t, typename VertexProperty = none,
                  typename EdgeProperty = none>
        class simple_graph : public virtual graph<Vertex, VertexProperty, EdgeProperty>
        {
        private:
            using repr = internal::graph_representation<Vertex, VertexProperty, EdgeProperty>;

        public:
            explicit simple_graph(std::initializer_list<Vertex> vertices)
                : representation{repr(vertices)}
            {
            }

            virtual ~simple_graph() = default;
            simple_graph(const simple_graph &) = default;
            simple_graph(simple_graph &&) = default;
            simple_graph & operator=(const simple_graph &) = default;
            simple_graph & operator=(simple_graph &&) = default;

            size_t vertices_count() const override
            {
                return representation.size();
            }

            std::vector<Vertex> vertices() const override
            {
                return representation.vertices();
            }

            std::vector<edge<Vertex>> adjacent_edges(const Vertex & vertex) const override
            {
                return representation.adjacent_edges(vertex);
            }

            edge<Vertex> get_edge(const Vertex & source, const Vertex & destination) const;
            std::vector<Vertex> neighbours(const Vertex & vertex) const override;

            bool add_vertex(const Vertex & vertex);

            bool add_vertex(const Vertex & vertex, const VertexProperty & property);

            virtual edge<Vertex> add_edge(const Vertex & source, const Vertex & destination) = 0;

            virtual edge<Vertex> add_edge(const Vertex & source, const Vertex & destination,
                                          const EdgeProperty & property) = 0;

            virtual edge<Vertex> add_edge(const edge<Vertex> & edge) = 0;

            virtual edge<Vertex> add_edge(const edge<Vertex> & edge,
                                          const EdgeProperty & property) = 0;

        private:
            repr representation;
        };

        template <typename Vertex, typename VertexProperty, typename EdgeProperty>
        edge<Vertex> simple_graph<Vertex, VertexProperty, EdgeProperty>::get_edge(
                const Vertex & source, const Vertex & destination) const
        {
            std::vector<edge<Vertex>> adjacent = representation.adjacent_edges(source);

            auto pos = std::find(adjacent.begin(), adjacent.end(),
                                 [&](const auto & e) { return e.get_neighbour(source); });

            if(pos == adjacent.end())
                throw std::out_of_range("No edge between the vertices");

            return *pos;
        }

        template <typename Vertex, typename VertexProperty, typename EdgeProperty>
        std::vector<Vertex> simple_graph<Vertex, VertexProperty, EdgeProperty>::neighbours(
                const Vertex & vertex) const
        {
            std::vector<Vertex> v;
            std::vector<edge<Vertex>> adjacent = representation.adjacent_edges(vertex);

            std::transform(adjacent.begin(), adjacent.end(), std::back_inserter(v),
                           [&](const auto & e) { return e.get_neighbour(vertex); });
            return v;
        }

        template <typename Vertex, typename VertexProperty, typename EdgeProperty>
        bool simple_graph<Vertex, VertexProperty, EdgeProperty>::add_vertex(const Vertex & vertex)
        {
            return representation.add_vertex(vertex);
        }

        template <typename Vertex, typename VertexProperty, typename EdgeProperty>
        bool simple_graph<Vertex, VertexProperty, EdgeProperty>::add_vertex(
                const Vertex & vertex, const VertexProperty & property)
        {
            bool was_added = representation.add_vertex(vertex);

            if(was_added)
                representation[vertex] = property;

            return was_added;
        }
    }
}

#endif
