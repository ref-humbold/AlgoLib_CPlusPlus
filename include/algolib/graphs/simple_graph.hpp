/*!
 * \file simple_graph.hpp
 * \brief Structure of simple graph
 */
#ifndef SIMPLE_GRAPH_HPP_
#define SIMPLE_GRAPH_HPP_

#include <cstdlib>
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
            return vertex_properties[vertex];
        }

        EdgeProperty & operator[](const algr::edge<Vertex> & edge)
        {
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

            ~simple_graph() = default;
            simple_graph(const simple_graph &) = default;
            simple_graph(simple_graph &&) = default;
            simple_graph & operator=(const simple_graph &) = default;
            simple_graph & operator=(simple_graph &&) = default;

        private:
            repr representation;
        };
    }
}

#endif
