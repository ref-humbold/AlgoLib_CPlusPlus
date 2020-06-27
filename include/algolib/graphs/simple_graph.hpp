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
                graph_map.emplace(vertex, std::unordered_set<E>());
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

        EP & operator[](const E & edge)
        {
            validate(edge, true);
            return edge_properties[edge];
        }

        const VP & property(const V & vertex) const
        {
            validate(vertex);

            auto it = vertex_properties.find(vertex);

            if(it == vertex_properties.end())
                throw std::out_of_range("Property for vertex not found");

            return it->second;
        }

        const EP & property(const E & edge) const
        {
            validate(edge, true);

            auto it = edge_properties.find(edge);

            if(it == edge_properties.end())
                throw std::out_of_range("Property for edge not found");

            return it->second;
        }

        bool has_property(const V & vertex) const
        {
            validate(vertex);
            return vertex_properties.find(vertex) != vertex_properties.end();
        }

        bool has_property(const E & edge) const
        {
            validate(edge, true);
            return edge_properties.find(edge) != edge_properties.end();
        }

        size_t size() const
        {
            return graph_map.size();
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

        std::unordered_map<V, std::unordered_set<E>> graph_map;
        std::unordered_map<V, VP> vertex_properties;
        std::unordered_map<E, EP> edge_properties;
    };

    template <typename V, typename E, typename VP, typename EP>
    std::vector<V> graph_representation<V, E, VP, EP>::vertices() const
    {
        std::vector<V> v;

        for(auto it = graph_map.cbegin(); it != graph_map.cend(); ++it)
            v.push_back(it->first);

        return v;
    }

    template <typename V, typename E, typename VP, typename EP>
    std::vector<E> graph_representation<V, E, VP, EP>::edges() const
    {
        std::vector<E> v;

        for(auto it = graph_map.cbegin(); it != graph_map.cend(); ++it)
            for(auto eit = it->second.cbegin(); eit != it->second.cend(); ++eit)
                v.push_back(*eit);

        return v;
    }

    template <typename V, typename E, typename VP, typename EP>
    std::vector<std::unordered_set<E>> graph_representation<V, E, VP, EP>::edges_set() const
    {
        std::vector<std::unordered_set<E>> v;

        for(auto it = graph_map.cbegin(); it != graph_map.cend(); ++it)
            v.push_back(it->second);

        return v;
    }

    template <typename V, typename E, typename VP, typename EP>
    std::vector<E> graph_representation<V, E, VP, EP>::adjacent_edges(const V & vertex) const
    {
        std::vector<E> v;

        validate(vertex);

        for(auto it = graph_map.at(vertex).cbegin(); it != graph_map.at(vertex).cend(); ++it)
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
        validate(edge, false);
        graph_map.at(edge.source()).insert(edge);
    }

    template <typename V, typename E, typename VP, typename EP>
    void graph_representation<V, E, VP, EP>::add_edge_to_destination(const E & edge)
    {
        validate(edge, false);
        graph_map.at(edge.destination()).insert(edge);
    }

    template <typename V, typename E, typename VP, typename EP>
    void graph_representation<V, E, VP, EP>::validate(const V & vertex) const
    {
        if(graph_map.find(vertex) == graph_map.end())
            throw std::invalid_argument("V does not belong to the graph");
    }

    template <typename V, typename E, typename VP, typename EP>
    void graph_representation<V, E, VP, EP>::validate(const E & edge, bool existing) const
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
        template <typename V, typename VP, typename EP>
        class simple_graph : public virtual graph<V, VP, EP>
        {
        public:
            using vertex_type = typename graph<V, VP, EP>::vertex_type;
            using edge_type = typename graph<V, VP, EP>::edge_type;
            using vertex_property_type = typename graph<V, VP, EP>::vertex_property_type;
            using edge_property_type = typename graph<V, VP, EP>::edge_property_type;

        protected:
            using repr = internal::graph_representation<vertex_type, edge_type,
                                                        vertex_property_type, edge_property_type>;

        public:
            explicit simple_graph(const std::vector<vertex_type> & vertices = {})
                : representation{repr(vertices)}
            {
            }

            virtual ~simple_graph() = default;
            simple_graph(const simple_graph &) = default;
            simple_graph(simple_graph &&) = default;
            simple_graph & operator=(const simple_graph &) = default;
            simple_graph & operator=(simple_graph &&) = default;

            vertex_property_type & operator[](const vertex_type & vertex) override
            {
                return this->representation[vertex];
            }

            edge_property_type & operator[](const edge_type & edge) override
            {
                return this->representation[edge];
            }

            const vertex_property_type & property(const vertex_type & vertex) const override
            {
                return this->representation.property(vertex);
            }

            const edge_property_type & property(const edge_type & edge) const override
            {
                return this->representation.property(edge);
            }

            bool has_property(const vertex_type & vertex) const override
            {
                return this->representation.has_property(vertex);
            }

            bool has_property(const edge_type & edge) const override
            {
                return this->representation.has_property(edge);
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

            edge_type get_edge(const vertex_type & source,
                               const vertex_type & destination) const override;
            std::vector<vertex_type> neighbours(const vertex_type & vertex) const override;
            bool add_vertex(const vertex_type & vertex);
            bool add_vertex(const vertex_type & vertex, const vertex_property_type & property);
            edge_type add_edge_between(const vertex_type & source, const vertex_type & destination);
            edge_type add_edge_between(const vertex_type & source, const vertex_type & destination,
                                       const edge_property_type & property);
            virtual edge_type add_edge(const edge_type & edge) = 0;
            virtual edge_type add_edge(const edge_type & edge,
                                       const edge_property_type & property) = 0;

        protected:
            repr representation;
        };

        template <typename V, typename VP, typename EP>
        typename simple_graph<V, VP, EP>::edge_type simple_graph<V, VP, EP>::get_edge(
                const typename simple_graph<V, VP, EP>::vertex_type & source,
                const typename simple_graph<V, VP, EP>::vertex_type & destination) const
        {
            std::vector<edge_type> adjacent = this->representation.adjacent_edges(source);

            auto pos = std::find_if(adjacent.begin(), adjacent.end(), [&](const edge_type & e) {
                return e.get_neighbour(source) == destination;
            });

            if(pos == adjacent.end())
                throw std::out_of_range("No edge between the vertices");

            return *pos;
        }

        template <typename V, typename VP, typename EP>
        std::vector<typename simple_graph<V, VP, EP>::vertex_type>
                simple_graph<V, VP, EP>::neighbours(
                        const typename simple_graph<V, VP, EP>::vertex_type & vertex) const
        {
            std::vector<vertex_type> v;
            std::vector<edge_type> adjacent = this->representation.adjacent_edges(vertex);

            std::transform(adjacent.begin(), adjacent.end(), std::back_inserter(v),
                           [&](const auto & e) { return e.get_neighbour(vertex); });
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
            return this->add_edge(edge_type(source, destination));
        }

        template <typename V, typename VP, typename EP>
        typename simple_graph<V, VP, EP>::edge_type simple_graph<V, VP, EP>::add_edge_between(
                const typename simple_graph<V, VP, EP>::vertex_type & source,
                const typename simple_graph<V, VP, EP>::vertex_type & destination,
                const typename simple_graph<V, VP, EP>::edge_property_type & property)
        {
            return this->add_edge(edge_type(source, destination), property);
        }
    }
}

#endif
