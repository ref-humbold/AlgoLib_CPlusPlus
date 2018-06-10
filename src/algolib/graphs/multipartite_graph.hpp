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

        template <size_t N>
        class multipartite_graph : public virtual undirected_graph
        {
            /// Struktura grafu wielodzielnego.
            undirected_simple_graph graph;

            /// Numery grup wierzchołków.
            std::vector<size_t> groups;

        public:
            explicit multipartite_graph(int n) : graph{undirected_simple_graph(n)}
            {
                groups.resize(n, 1);
            }

            virtual ~multipartite_graph() = default;
            multipartite_graph(const multipartite_graph & g) = default;
            multipartite_graph(multipartite_graph && g) = default;
            multipartite_graph & operator=(const multipartite_graph & g) = default;
            multipartite_graph & operator=(multipartite_graph && g) = default;

            /**
             * @param group numer grupy wierzchołków
             * @return liczba wierzchołków z zadanej grupy
             */
            size_t get_vertices_number(size_t group = 0) const
            {
                if(group == 0)
                    return graph.get_vertices_number();

                int num = 0;

                for(const auto & v : graph.get_vertices())
                    if(groups[v] == group)
                        ++num;

                return num;
            }

            /**
             * @param group numer grupy wierzchołków
             * @return numery wierzchołków z zadanej grupy
             */
            std::vector<vertex_t> get_vertices(size_t group = 0) const
            {
                std::vector<vertex_t> vertices;

                if(group == 0)
                    return graph.get_vertices();

                for(const auto & v : graph.get_vertices())
                    if(groups[v] == group)
                        vertices.push_back(v);

                return vertices;
            }

            /**
             * Dodawanie nowego wierzchołka do zadanej grupy.
             * @param group: numer grupy
             * @return oznaczenie wierzchołka
             */
            vertex_t add_vertex(size_t group)
            {
                groups.push_back(group);

                return graph.add_vertex();
            }

            size_t get_edges_number() const override
            {
                return graph.get_edges_number();
            }

            std::vector<edge_t> get_edges() const override
            {
                return graph.get_edges();
            }

            void add_edge(vertex_t vertex1, vertex_t vertex2) override
            {
                if(vertex1 >= get_vertices_number())
                    throw no_such_vertex_exception(std::to_string(vertex1));

                if(vertex2 >= get_vertices_number())
                    throw no_such_vertex_exception(std::to_string(vertex2));

                if(is_same_group(vertex1, vertex2))
                    throw graph_partition_exception();

                graph.add_edge(vertex1, vertex2);
            }

            /**
             * @param vertex: numer wierzchołka
             * @param group: numer grupy sąsiadów
             * @return generator sąsiadów wierzchołka z zadanej grupy
             */
            std::vector<vertex_t> get_neighbours(vertex_t vertex, size_t group = 0) const
            {
                std::vector<vertex_t> vertices;

                if(vertex >= get_vertices_number())
                    throw no_such_vertex_exception(std::to_string(vertex));

                if(group == 0)
                    return graph.get_neighbours(vertex);

                for(const auto & v : graph.get_neighbours(vertex))
                    if(groups[v] == group)
                        vertices.push_back(v);

                return vertices;
            }

            size_t get_outdegree(vertex_t vertex) const override
            {
                return graph.get_outdegree(vertex);
            }

            size_t get_indegree(vertex_t vertex) const override
            {
                return graph.get_indegree(vertex);
            }

            directed_simple_graph * as_directed() const override
            {
                return graph.as_directed();
            }

            /**
             * Sprawdzanie, czy wierzchołek nalezy do zadanej grupy.
             * @param vertex wierzchołek
             * @param group numer grupy
             * @return czy wierzchołek jest w grupie
             */
            bool is_in_group(vertex_t vertex, size_t group) const
            {
                if(vertex >= get_vertices_number())
                    throw no_such_vertex_exception(std::to_string(vertex));

                return groups[vertex] == group;
            }

            /**
             * Sprawdzanie, czy wierzchołki należą do tej samej grupy.
             * @param vertex1 pierwszy wierzchołek
             * @param vertex2 drugi wierzchołek
             * @return czy wierzchołki są w jednej grupie
             */
            bool is_same_group(vertex_t vertex1, vertex_t vertex2) const
            {
                if(vertex1 >= get_vertices_number())
                    throw no_such_vertex_exception(std::to_string(vertex1));

                if(vertex2 >= get_vertices_number())
                    throw no_such_vertex_exception(std::to_string(vertex2));

                return groups[vertex1] == groups[vertex2];
            }
        };
    }
}

#endif
