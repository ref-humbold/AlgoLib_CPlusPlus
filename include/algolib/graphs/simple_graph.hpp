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

    template <typename V = size_t, typename VP = algr::no_prop, typename EP = algr::no_prop>
    class graph_representation
    {
    public:
        explicit graph_representation(const std::vector<V> & vertices = {})
        {
            for(const V & vertex : vertices)
                graph_map.emplace(vertex, std::unordered_set<algr::edge<V>>());
        }

        ~graph_representation() = default;
        graph_representation(const graph_representation &) = default;
        graph_representation(graph_representation &&) = default;
        graph_representation & operator=(const graph_representation &) = default;
        graph_representation & operator=(graph_representation &&) = default;

        VP & operator[](const V & vertex)
        {
            validate(vertex);
            return vertex_properties[vertex];
        }

        EP & operator[](const algr::edge<V> & edge)
        {
            validate(edge, true);
            return edge_properties[edge];
        }

        size_t size()
        {
            return graph_map.size();
        }

        std::vector<V> vertices();
        std::vector<algr::edge<V>> edges();
        std::vector<std::unordered_set<algr::edge<V>>> edges_set();
        std::vector<algr::edge<V>> adjacent_edges(const V & vertex);
        bool add_vertex(const V & vertex);
        void add_edge_to_source(const algr::edge<V> & edge);
        void add_edge_to_destination(const algr::edge<V> & edge);

    private:
        void validate(const V & vertex);
        void validate(const algr::edge<V> & edge, bool existing);

        std::unordered_map<V, std::unordered_set<algr::edge<V>>> graph_map;
        std::unordered_map<V, VP> vertex_properties;
        std::unordered_map<algr::edge<V>, EP> edge_properties;
    };

    template <typename V, typename VP, typename EP>
    std::vector<V> graph_representation<V, VP, EP>::vertices()
    {
        std::vector<V> v;

        for(auto it = graph_map.cbegin(); it != graph_map.cend(); ++it)
            v.push_back(it->first);

        return v;
    }

    template <typename V, typename VP, typename EP>
    std::vector<algr::edge<V>> graph_representation<V, VP, EP>::edges()
    {
        std::vector<algr::edge<V>> v;

        for(auto it = graph_map.cbegin(); it != graph_map.cend(); ++it)
            for(auto eit = it->second.cbegin(); eit != it->second.cend(); ++eit)
                v.push_back(*eit);

        return v;
    }

    template <typename V, typename VP, typename EP>
    std::vector<std::unordered_set<algr::edge<V>>> graph_representation<V, VP, EP>::edges_set()
    {
        std::vector<std::unordered_set<algr::edge<V>>> v;

        for(auto it = graph_map.cbegin(); it != graph_map.cend(); ++it)
            v.push_back(it->second);

        return v;
    }

    template <typename V, typename VP, typename EP>
    std::vector<algr::edge<V>> graph_representation<V, VP, EP>::adjacent_edges(const V & vertex)
    {
        std::vector<algr::edge<V>> v;

        validate(vertex);

        for(auto it = graph_map.at(vertex).cbegin(); it != graph_map.at(vertex).cend(); ++it)
            v.push_back(*it);

        return v;
    }

    template <typename V, typename VP, typename EP>
    bool graph_representation<V, VP, EP>::add_vertex(const V & vertex)
    {
        if(graph_map.find(vertex) == graph_map.end())
        {
            graph_map.emplace(vertex, std::unordered_set<algr::edge<V>>());
            return true;
        }

        return false;
    }

    template <typename V, typename VP, typename EP>
    void graph_representation<V, VP, EP>::add_edge_to_source(const algr::edge<V> & edge)
    {
        validate(edge, false);
        graph_map.at(edge.source()).insert(edge);
    }

    template <typename V, typename VP, typename EP>
    void graph_representation<V, VP, EP>::add_edge_to_destination(const algr::edge<V> & edge)
    {
        validate(edge, false);
        graph_map.at(edge.destination()).insert(edge);
    }

    template <typename V, typename VP, typename EP>
    void graph_representation<V, VP, EP>::validate(const V & vertex)
    {
        if(graph_map.find(vertex) == graph_map.end())
            throw std::invalid_argument("V does not belong to the graph");
    }

    template <typename V, typename VP, typename EP>
    void graph_representation<V, VP, EP>::validate(const algr::edge<V> & edge, bool existing)
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
        template <typename V = size_t, typename VP = no_prop, typename EP = no_prop>
        class simple_graph : public virtual graph<V, VP, EP>
        {
        protected:
            using repr = internal::graph_representation<V, VP, EP>;

        public:
            explicit simple_graph(std::vector<V> vertices = {}) : representation{repr(vertices)}
            {
            }

            virtual ~simple_graph() = default;
            simple_graph(const simple_graph &) = default;
            simple_graph(simple_graph &&) = default;
            simple_graph & operator=(const simple_graph &) = default;
            simple_graph & operator=(simple_graph &&) = default;

            VP & operator[](const V & vertex)
            {
                return representation[vertex];
            }

            EP & operator[](const edge<V> & edge)
            {
                return representation[edge];
            }

            size_t vertices_count() const override
            {
                return representation.size();
            }

            std::vector<V> vertices() const override
            {
                return representation.vertices();
            }

            std::vector<edge<V>> adjacent_edges(const V & vertex) const override
            {
                return representation.adjacent_edges(vertex);
            }

            edge<V> get_edge(const V & source, const V & destination) const override;
            std::vector<V> neighbours(const V & vertex) const override;
            bool add_vertex(const V & vertex);
            bool add_vertex(const V & vertex, const VP & property);
            virtual edge<V> add_edge(const V & source, const V & destination);
            virtual edge<V> add_edge(const V & source, const V & destination, const EP & property);
            virtual edge<V> add_edge(const edge<V> & edge) = 0;
            virtual edge<V> add_edge(const edge<V> & edge, const EP & property) = 0;

        protected:
            repr representation;
        };

        template <typename V, typename VP, typename EP>
        edge<V> simple_graph<V, VP, EP>::get_edge(const V & source, const V & destination) const
        {
            std::vector<edge<V>> adjacent = representation.adjacent_edges(source);

            auto pos = std::find(adjacent.begin(), adjacent.end(),
                                 [&](const auto & e) { return e.get_neighbour(source); });

            if(pos == adjacent.end())
                throw std::out_of_range("No edge between the vertices");

            return *pos;
        }

        template <typename V, typename VP, typename EP>
        std::vector<V> simple_graph<V, VP, EP>::neighbours(const V & vertex) const
        {
            std::vector<V> v;
            std::vector<edge<V>> adjacent = representation.adjacent_edges(vertex);

            std::transform(adjacent.begin(), adjacent.end(), std::back_inserter(v),
                           [&](const auto & e) { return e.get_neighbour(vertex); });
            return v;
        }

        template <typename V, typename VP, typename EP>
        bool simple_graph<V, VP, EP>::add_vertex(const V & vertex)
        {
            return representation.add_vertex(vertex);
        }

        template <typename V, typename VP, typename EP>
        bool simple_graph<V, VP, EP>::add_vertex(const V & vertex, const VP & property)
        {
            bool was_added = representation.add_vertex(vertex);

            if(was_added)
                representation[vertex] = property;

            return was_added;
        }

        template <typename V, typename VP, typename EP>
        edge<V> simple_graph<V, VP, EP>::add_edge(const V & source, const V & destination)
        {
            return add_edge(edge<V>(source, destination));
        }

        template <typename V, typename VP, typename EP>
        edge<V> simple_graph<V, VP, EP>::add_edge(const V & source, const V & destination,
                                                  const EP & property)
        {
            return add_edge(edge<V>(source, destination), property);
        }
    }
}

#endif
