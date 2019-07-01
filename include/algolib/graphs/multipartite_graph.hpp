//! STRUKTURY GRAFÓW WIELODZIELNYCH
#ifndef MULTIPARTITE_GRAPH_HPP_
#define MULTIPARTITE_GRAPH_HPP_

#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <vector>
#include "directed_graph.hpp"
#include "undirected_graph.hpp"

using namespace std::string_literals;

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
        };

        template <size_t N>
        class multipartite_graph : public undirected_graph
        {
        public:
            explicit multipartite_graph(int n) : graph{undirected_simple_graph(n)}
            {
                groups.resize(n, 1);
            }

            virtual ~multipartite_graph() = default;
            multipartite_graph(const multipartite_graph &) = default;
            multipartite_graph(multipartite_graph &&) = default;
            multipartite_graph & operator=(const multipartite_graph &) = default;
            multipartite_graph & operator=(multipartite_graph &&) = default;

            /**!
             * \param group numer grupy wierzchołków
             * \return liczba wierzchołków z zadanej grupy
             */
            size_t get_vertices_number(size_t group = 0) const;

            /**!
             * \param group numer grupy wierzchołków
             * \return numery wierzchołków z zadanej grupy
             */
            std::vector<vertex_t> get_vertices(size_t group = 0) const;

            /**!
             * \brief Dodawanie nowego wierzchołka do zadanej grupy.
             * \param group numer grupy
             * \param neighbours sąsiedzi nowego wierzchołka
             * \return oznaczenie wierzchołka
             */
            vertex_t add_vertex(size_t group, const std::vector<vertex_t> & neighbours);

            vertex_t add_vertex(const std::vector<vertex_t> & neighbours) override
            {
                return add_vertex(1, neighbours);
            }

            size_t get_edges_number() const override
            {
                return graph.get_edges_number();
            }

            std::vector<edge_t> get_edges() const override
            {
                return graph.get_edges();
            }

            void add_edge(vertex_t vertex1, vertex_t vertex2) override;

            /**!
             * \param vertex: numer wierzchołka
             * \param group: numer grupy sąsiadów
             * \return generator sąsiadów wierzchołka z zadanej grupy
             */
            std::vector<vertex_t> get_neighbours(vertex_t vertex, size_t group = 0) const;

            size_t get_outdegree(vertex_t vertex) const override
            {
                return graph.get_outdegree(vertex);
            }

            size_t get_indegree(vertex_t vertex) const override
            {
                return graph.get_indegree(vertex);
            }

            /**!
             * \brief Sprawdzanie, czy wierzchołek nalezy do zadanej grupy.
             * \param vertex wierzchołek
             * \param group numer grupy
             * \return czy wierzchołek jest w grupie
             */
            bool is_in_group(vertex_t vertex, size_t group) const;

            /**!
             * \brief Sprawdzanie, czy wierzchołki należą do tej samej grupy.
             * \param vertex1 pierwszy wierzchołek
             * \param vertex2 drugi wierzchołek
             * \return czy wierzchołki są w jednej grupie
             */
            bool is_same_group(vertex_t vertex1, vertex_t vertex2) const;

        private:
            undirected_simple_graph graph;  //!< Struktura grafu wielodzielnego.
            std::vector<size_t> groups;  //!< Numery grup wierzchołków.
        };

        template <size_t N>
        size_t multipartite_graph<N>::get_vertices_number(size_t group) const
        {
            if(group == 0)
                return graph.get_vertices_number();

            int num = 0;

            for(const auto & v : graph.get_vertices())
                if(groups[v] == group)
                    ++num;

            return num;
        }

        template <size_t N>
        std::vector<vertex_t> multipartite_graph<N>::get_vertices(size_t group) const
        {
            std::vector<vertex_t> vertices;

            if(group == 0)
                return graph.get_vertices();

            for(const auto & v : graph.get_vertices())
                if(groups[v] == group)
                    vertices.push_back(v);

            return vertices;
        }

        template <size_t N>
        vertex_t multipartite_graph<N>::add_vertex(size_t group,
                                                   const std::vector<vertex_t> & neighbours)
        {
            if(group == 0)
                throw std::invalid_argument("Cannot add vertex to group 0");

            vertex_t v = graph.add_vertex(neighbours);

            groups.push_back(group);

            return v;
        }

        template <size_t N>
        void multipartite_graph<N>::add_edge(vertex_t vertex1, vertex_t vertex2)
        {
            if(vertex1 >= get_vertices_number())
                throw no_such_vertex_exception(std::to_string(vertex1));

            if(vertex2 >= get_vertices_number())
                throw no_such_vertex_exception(std::to_string(vertex2));

            if(is_same_group(vertex1, vertex2))
                throw graph_partition_exception("Vertices in the same part."s);

            graph.add_edge(vertex1, vertex2);
        }

        template <size_t N>
        std::vector<vertex_t> multipartite_graph<N>::get_neighbours(vertex_t vertex,
                                                                    size_t group) const
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

        template <size_t N>
        bool multipartite_graph<N>::is_in_group(vertex_t vertex, size_t group) const
        {
            if(vertex >= get_vertices_number())
                throw no_such_vertex_exception(std::to_string(vertex));

            return groups[vertex] == group;
        }

        template <size_t N>
        bool multipartite_graph<N>::is_same_group(vertex_t vertex1, vertex_t vertex2) const
        {
            if(vertex1 >= get_vertices_number())
                throw no_such_vertex_exception(std::to_string(vertex1));

            if(vertex2 >= get_vertices_number())
                throw no_such_vertex_exception(std::to_string(vertex2));

            return groups[vertex1] == groups[vertex2];
        }
    }
}

#endif
