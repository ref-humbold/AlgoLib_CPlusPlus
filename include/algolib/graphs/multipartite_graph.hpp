/*!
 * \file multipartite_graph.hpp
 * \brief Structure of multipartite graph
 */
#ifndef MULTIPARTITE_GRAPH_HPP_
#define MULTIPARTITE_GRAPH_HPP_

#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <string>
#include <vector>
#include "undirected_graph.hpp"

using namespace std::string_literals;

namespace algolib
{
    namespace graphs
    {
        class graph_partition_error : std::logic_error
        {
        public:
            explicit graph_partition_error(const std::string & what_arg)
                : std::logic_error(what_arg)
            {
            }
        };

        template <size_t N, typename V = size_t, typename VP = no_prop, typename EP = no_prop>
        class multipartite_graph : public virtual undirected_graph<V, VP, EP>
        {
        protected:
            using graph_t = undirected_simple_graph<
                    typename multipartite_graph<N, V, VP, EP>::vertex_type,
                    typename multipartite_graph<N, V, VP, EP>::vertex_property_type,
                    typename multipartite_graph<N, V, VP, EP>::edge_property_type>;

        public:
            explicit multipartite_graph(
                    std::vector<std::vector<typename multipartite_graph<N, V, VP, EP>::vertex_type>>
                            vertices)
            {
                if(vertices.size() > N)
                    throw graph_partition_error(
                            "Cannot add vertices to group "s + std::to_string(vertices.size())
                            + ", graph contains only "s + std::to_string(N) + " groups"s);

                int i = 0;

                for(auto && group_vertices : vertices)
                {
                    for(auto && vertex : group_vertices)
                        this->add_vertex(i, vertex);

                    ++i;
                }
            }

            ~multipartite_graph() override = default;
            multipartite_graph(const multipartite_graph &) = default;
            multipartite_graph(multipartite_graph &&) = default;
            multipartite_graph & operator=(const multipartite_graph &) = default;
            multipartite_graph & operator=(multipartite_graph &&) = default;

            size_t vertices_count() const
            {
                return this->graph.vertices_count();
            }

            size_t edges_count() const override
            {
                return this->graph.edges_count();
            }

            std::vector<typename multipartite_graph<N, V, VP, EP>::vertex_type> vertices() const
            {
                return this->graph.vertices();
            }

            std::vector<typename multipartite_graph<N, V, VP, EP>::edge_type> edges() const override
            {
                return this->graph.edges();
            }

            typename multipartite_graph<N, V, VP, EP>::vertex_property_type & operator[](
                    const typename multipartite_graph<N, V, VP, EP>::vertex_type & vertex) override
            {
                return this->graph[vertex];
            }

            const typename multipartite_graph<N, V, VP, EP>::vertex_property_type & operator[](
                    const typename multipartite_graph<N, V, VP, EP>::vertex_type & vertex)
                    const override
            {
                return this->graph[vertex];
            }

            typename multipartite_graph<N, V, VP, EP>::edge_property_type & operator[](
                    const typename multipartite_graph<N, V, VP, EP>::edge_type & edge) override
            {
                return this->graph[edge];
            }

            const typename multipartite_graph<N, V, VP, EP>::edge_property_type &
                    operator[](const typename multipartite_graph<N, V, VP, EP>::edge_type & edge)
                            const override
            {
                return this->graph[edge];
            }

            typename multipartite_graph<N, V, VP, EP>::edge_type
                    get_edge(const typename multipartite_graph<N, V, VP, EP>::vertex_type & source,
                             const typename multipartite_graph<N, V, VP, EP>::vertex_type &
                                     destination) const override
            {
                return this->graph.get_edge(source, destination);
            }

            std::vector<typename multipartite_graph<N, V, VP, EP>::edge_type> adjacent_edges(
                    const typename multipartite_graph<N, V, VP, EP>::vertex_type & vertex)
                    const override
            {
                return this->graph.adjacent_edges(vertex);
            }

            std::vector<typename multipartite_graph<N, V, VP, EP>::vertex_type> neighbours(
                    const typename multipartite_graph<N, V, VP, EP>::vertex_type & vertex)
                    const override
            {
                return this->graph.neighbours(vertex);
            }

            size_t output_degree(const typename multipartite_graph<N, V, VP, EP>::vertex_type &
                                         vertex) const override
            {
                return this->graph.output_degree(vertex);
            }

            size_t input_degree(const typename multipartite_graph<N, V, VP, EP>::vertex_type &
                                        vertex) const override
            {
                return graph.input_degree(vertex);
            }

            std::vector<typename multipartite_graph<N, V, VP, EP>::vertex_type>
                    vertices_from_group(size_t group_number) const;
            bool add_vertex(size_t group_number,
                            const typename multipartite_graph<N, V, VP, EP>::vertex_type & vertex);
            bool add_vertex(size_t group_number,
                            const typename multipartite_graph<N, V, VP, EP>::vertex_type & vertex,
                            const typename multipartite_graph<N, V, VP, EP>::vertex_property_type &
                                    property);
            typename multipartite_graph<N, V, VP, EP>::edge_type add_edge_between(
                    const typename multipartite_graph<N, V, VP, EP>::vertex_type & source,
                    const typename multipartite_graph<N, V, VP, EP>::vertex_type & destination);
            typename multipartite_graph<N, V, VP, EP>::edge_type add_edge_between(
                    const typename multipartite_graph<N, V, VP, EP>::vertex_type & source,
                    const typename multipartite_graph<N, V, VP, EP>::vertex_type & destination,
                    const typename multipartite_graph<N, V, VP, EP>::edge_property_type & property);
            typename multipartite_graph<N, V, VP, EP>::edge_type
                    add_edge(const typename multipartite_graph<N, V, VP, EP>::edge_type & edge);
            typename multipartite_graph<N, V, VP, EP>::edge_type add_edge(
                    const typename multipartite_graph<N, V, VP, EP>::edge_type & edge,
                    const typename multipartite_graph<N, V, VP, EP>::edge_property_type & property);

        private:
            bool are_in_same_group(
                    const typename multipartite_graph<N, V, VP, EP>::vertex_type & vertex1,
                    const typename multipartite_graph<N, V, VP, EP>::vertex_type & vertex2) const
            {
                return this->vertex_group_map.at(vertex1) == this->vertex_group_map.at(vertex2);
            }

            void validate_group(size_t group_number) const
            {
                if(group_number >= N)
                    throw std::out_of_range("Invalid group number "s + std::to_string(group_number)
                                            + ", graph contains only " + std::to_string(N)
                                            + " groups"s);
            }

            graph_t graph;
            std::unordered_map<typename multipartite_graph<N, V, VP, EP>::vertex_type, size_t>
                    vertex_group_map;
        };

        template <size_t N, typename V, typename VP, typename EP>
        std::vector<typename multipartite_graph<N, V, VP, EP>::vertex_type>
                multipartite_graph<N, V, VP, EP>::vertices_from_group(size_t group_number) const
        {
            std::vector<typename multipartite_graph<N, V, VP, EP>::vertex_type> group_vertices;

            this->validate_group(group_number);

            for(auto && p : this->vertex_group_map)
                if(p.second == group_number)
                    group_vertices.push_back(p.first);

            return group_vertices;
        }

        template <size_t N, typename V, typename VP, typename EP>
        bool multipartite_graph<N, V, VP, EP>::add_vertex(
                size_t group_number,
                const typename multipartite_graph<N, V, VP, EP>::vertex_type & vertex)
        {
            this->validate_group(group_number);

            bool was_added = this->graph.add_vertex(vertex);

            if(was_added)
                this->vertex_group_map.emplace(vertex, group_number);

            return was_added;
        }

        template <size_t N, typename V, typename VP, typename EP>
        bool multipartite_graph<N, V, VP, EP>::add_vertex(
                size_t group_number,
                const typename multipartite_graph<N, V, VP, EP>::vertex_type & vertex,
                const typename multipartite_graph<N, V, VP, EP>::vertex_property_type & property)
        {
            this->validate_group(group_number);

            bool was_added = this->graph.add_vertex(vertex, property);

            if(was_added)
                this->vertex_group_map.emplace(vertex, group_number);

            return was_added;
        }

        template <size_t N, typename V, typename VP, typename EP>
        typename multipartite_graph<N, V, VP, EP>::edge_type
                multipartite_graph<N, V, VP, EP>::add_edge_between(
                        const typename multipartite_graph<N, V, VP, EP>::vertex_type & source,
                        const typename multipartite_graph<N, V, VP, EP>::vertex_type & destination)
        {
            return this->add_edge(
                    typename multipartite_graph<N, V, VP, EP>::edge_type(source, destination));
        }

        template <size_t N, typename V, typename VP, typename EP>
        typename multipartite_graph<N, V, VP, EP>::edge_type
                multipartite_graph<N, V, VP, EP>::add_edge_between(
                        const typename multipartite_graph<N, V, VP, EP>::vertex_type & source,
                        const typename multipartite_graph<N, V, VP, EP>::vertex_type & destination,
                        const typename multipartite_graph<N, V, VP, EP>::edge_property_type &
                                property)
        {
            return this->add_edge(
                    typename multipartite_graph<N, V, VP, EP>::edge_type(source, destination),
                    property);
        }

        template <size_t N, typename V, typename VP, typename EP>
        typename multipartite_graph<N, V, VP, EP>::edge_type
                multipartite_graph<N, V, VP, EP>::add_edge(
                        const typename multipartite_graph<N, V, VP, EP>::edge_type & edge)
        {
            if(this->are_in_same_group(edge.source(), edge.destination()))
                throw graph_partition_error(
                        "Cannot create an edge between vertices in the same group"s);

            return this->graph.add_edge(edge);
        }

        template <size_t N, typename V, typename VP, typename EP>
        typename multipartite_graph<N, V, VP, EP>::edge_type
                multipartite_graph<N, V, VP, EP>::add_edge(
                        const typename multipartite_graph<N, V, VP, EP>::edge_type & edge,
                        const typename multipartite_graph<N, V, VP, EP>::edge_property_type &
                                property)
        {
            if(this->are_in_same_group(edge.source(), edge.destination()))
                throw graph_partition_error(
                        "Cannot create an edge between vertices in the same group"s);

            return this->graph.add_edge(edge, property);
        }
    }
}

#endif
