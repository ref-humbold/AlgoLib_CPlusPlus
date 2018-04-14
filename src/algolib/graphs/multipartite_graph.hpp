// STRUKTURY GRAFÓW WIELODZIELNYCH
#ifndef _MULTIPARTITE_GRAPH_HPP_
#define _MULTIPARTITE_GRAPH_HPP_

#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <vector>

#include "directed_graph.hpp"
#include "undirected_graph.hpp"

namespace algolib
{
    namespace graphs
    {
        class graph_partition_exception : public std::logic_error
        {
        public:
            explicit graph_partition_exception(const std::string & what_arg)
                : std::logic_error(what_arg)
            {
            }

            explicit graph_partition_exception(const char * what_arg = "")
                : std::logic_error(what_arg)
            {
            }
        };

        class multipartite_graph : public virtual undirected_graph
        {
            /// Struktura grafu wielodzielnego.
            undirected_simple_graph graph;

            /// Maksymalna liczba grup wierzchołków.
            size_t groups_number;

            /// Numery grup wierzchołków.
            std::vector<size_t> groups;

        public:
            multipartite_graph(int n, size_t group)
                : graph{undirected_simple_graph(n)}, groups_number{group}
            {
                groups.resize(1, this->graph.get_vertices_number());
            }

            virtual ~multipartite_graph() = default;
            multipartite_graph(const multipartite_graph & g) = default;
            multipartite_graph(multipartite_graph && g) = default;
            multipartite_graph & operator=(const multipartite_graph & g) = default;
            multipartite_graph & operator=(multipartite_graph && g) = default;

            size_t get_groups_number() const
            {
                return this->groups_number;
            }

            size_t get_vertices_number() const override
            {
                return graph.get_vertices_number();
            }

            std::vector<vertex_t> get_vertices() const override
            {
                return get_vertices(0);
            }

            /**
             * @param group numer grupy wierzchołków
             * @return generator wierzchołków z zadanej grupy
             */
            std::vector<vertex_t> get_vertices(size_t group) const;

            vertex_t add_vertex() override
            {
                return add_vertex(1);
            }

            /**
             * Dodawanie nowego wierzchołka do zadanej grupy.
             * @param group: numer grupy
             * @return oznaczenie wierzchołka
             */
            vertex_t add_vertex(size_t group);

            size_t get_edges_number() const override
            {
                return graph.get_edges_number();
            }

            std::vector<edge_t> get_edges() const override
            {
                return graph.get_edges();
            }

            void add_edge(vertex_t vertex1, vertex_t vertex2) override;

            std::vector<vertex_t> get_neighbours(vertex_t vertex) const override
            {
                return get_neighbours(vertex, 0);
            }

            /**
             * @param vertex: numer wierzchołka
             * @param group: numer grupy sąsiadów
             * @return generator sąsiadów wierzchołka z zadanej grupy
             */
            std::vector<vertex_t> get_neighbours(vertex_t vertex, size_t group) const;

            size_t get_outdegree(vertex_t vertex) const override
            {
                return graph.get_outdegree(vertex);
            }

            size_t get_indegree(vertex_t vertex) const override
            {
                return graph.get_indegree(vertex);
            }

            directed_graph * as_directed() const override
            {
                return graph.as_directed();
            }

            /**
             * Sprawdzanie, czy wierzchołek nalezy do zadanej grupy.
             * @param vertex wierzchołek
             * @param group numer grupy
             * @return czy wierzchołek jest w grupie
             */
            bool is_in_group(vertex_t vertex, size_t group) const;

            /**
             * Sprawdzanie, czy wierzchołki należą do tej samej grupy.
             * @param vertex1 pierwszy wierzchołek
             * @param vertex2 drugi wierzchołek
             * @return czy wierzchołki są w jednej grupie
             */
            bool is_same_group(vertex_t vertex1, vertex_t vertex2) const;
        };
    }
}

#endif
