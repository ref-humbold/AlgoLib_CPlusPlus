/*!
 * \file multipartite_graph.hpp
 * \brief Structure of multipartite graph.
 */
#ifndef MULTIPARTITE_GRAPH_HPP_
#define MULTIPARTITE_GRAPH_HPP_

#include <cstdlib>
#include <algorithm>
#include <exception>
#include <stdexcept>
#include <string>
#include <vector>
#include "algolib/graphs/undirected_graph.hpp"

using namespace std::string_literals;

namespace algolib::graphs
{
    class graph_partition_error : std::logic_error
    {
    public:
        explicit graph_partition_error(const std::string & what_arg) : std::logic_error(what_arg)
        {
        }
    };

    template <
            size_t N,
            typename VertexId = size_t,
            typename VertexProperty = std::nullptr_t,
            typename EdgeProperty = std::nullptr_t>
    class multipartite_graph
        : public virtual undirected_graph<VertexId, VertexProperty, EdgeProperty>
    {
    public:
        using vertex_id_type =
                typename undirected_graph<VertexId, VertexProperty, EdgeProperty>::vertex_id_type;
        using vertex_type =
                typename undirected_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type;
        using edge_type =
                typename undirected_graph<VertexId, VertexProperty, EdgeProperty>::edge_type;
        using vertex_property_type =
                typename undirected_graph<VertexId, VertexProperty, EdgeProperty>::
                        vertex_property_type;
        using edge_property_type =
                typename undirected_graph<VertexId, VertexProperty, EdgeProperty>::
                        edge_property_type;

    protected:
        using graph_t =
                undirected_simple_graph<vertex_id_type, vertex_property_type, edge_property_type>;

    public:
        explicit multipartite_graph(std::array<std::vector<vertex_id_type>, N> vertex_ids)
        {
            int i = 0;

            for(auto && group_vertex_ids : vertex_ids)
            {
                for(auto && vertex_id : group_vertex_ids)
                    this->add_vertex(i, vertex_id);

                ++i;
            }
        }

        ~multipartite_graph() override = default;
        multipartite_graph(const multipartite_graph &) = default;
        multipartite_graph(multipartite_graph &&) = default;
        multipartite_graph & operator=(const multipartite_graph &) = default;
        multipartite_graph & operator=(multipartite_graph &&) = default;

        const vertex_type & operator[](const vertex_id_type & vertex_id) const override
        {
            return this->graph[vertex_id];
        }

        const edge_type & operator[](
                const std::pair<vertex_id_type, vertex_id_type> & vertex_ids) const override
        {
            return this->graph[vertex_ids];
        }

        const edge_type &
                operator[](const std::pair<vertex_type, vertex_type> & vertices) const override
        {
            return this->graph[vertices];
        }

        typename graph<VertexId, VertexProperty, EdgeProperty>::graph_properties &
                properties() override
        {
            return this->graph.properties();
        }

        const typename graph<VertexId, VertexProperty, EdgeProperty>::graph_properties &
                properties() const override
        {
            return this->graph.properties();
        }

        size_t vertices_count() const override
        {
            return this->graph.vertices_count();
        }

        size_t edges_count() const override
        {
            return this->graph.edges_count();
        }

        std::vector<vertex_type> vertices() const override
        {
            return this->graph.vertices();
        }

        std::vector<edge_type> edges() const override
        {
            return this->graph.edges();
        }

        std::vector<edge_type> adjacent_edges(const vertex_type & vertex) const override
        {
            return this->graph.adjacent_edges(vertex);
        }

        std::vector<vertex_type> neighbours(const vertex_type & vertex) const override
        {
            return this->graph.neighbours(vertex);
        }

        size_t output_degree(const vertex_type & vertex) const override
        {
            return this->graph.output_degree(vertex);
        }

        size_t input_degree(const vertex_type & vertex) const override
        {
            return graph.input_degree(vertex);
        }

        /*!
         * \brief Gets the vertices of given group.
         * \param group_number the group number
         * \return the vertices that belong to the group
         */
        std::vector<vertex_type> vertices_from_group(size_t group_number) const;

        /*!
         * \brief Adds new vertex to given group in this graph.
         *
         * \param group_number the group number
         * \param vertex_id the identifier of new vertex
         * \return the created vertex
         */
        vertex_type add_vertex(size_t group_number, const vertex_id_type & vertex_id);

        /*!
         * \brief Adds new vertex with given property to given group in this graph.
         *
         * \param group_number the group number
         * \param vertex_id the identifier of new vertex
         * \param property te vertex property
         * \return the created vertex
         */
        vertex_type add_vertex(
                size_t group_number,
                const vertex_id_type & vertex_id,
                const vertex_property_type & property);

        /*!
         * \brief Adds new vertex to given group in this graph.
         * \param group_number the group number
         * \param vertex the new vertex
         * \return the created vertex
         */
        vertex_type add_vertex(size_t group_number, const vertex_type & vertex);

        /*!
         * \brief Adds new vertex with given property to given group in this graph.
         * \param group_number the group number
         * \param vertex the new vertex
         * \param property the vertex property
         * \return the created vertex
         */
        vertex_type add_vertex(
                size_t group_number,
                const vertex_type & vertex,
                const vertex_property_type & property);

        /*!
         * \brief Adds new edge between given vertices to this graph.
         * \param source the source vertex
         * \param destination the destination vertex
         * \return the created edge
         * \throw graph_partition_error exception if the vertices belong to the same group
         */
        edge_type add_edge_between(const vertex_type & source, const vertex_type & destination);

        /*!
         * \brief Adds new edge between given vertices with given property to this graph.
         * \param source the source vertex
         * \param destination the destination vertex
         * \param property the edge property
         * \return the created edge
         * \throw graph_partition_error if the vertices belong to the same group
         */
        edge_type add_edge_between(
                const vertex_type & source,
                const vertex_type & destination,
                const edge_property_type & property);

        /*!
         * \brief Adds new edge to this graph.
         * \param edge the new edge
         * \return the created edge
         * \throw graph_partition_error if the edge connects vertices from the same group
         */
        edge_type add_edge(const edge_type & edge);

        /*!
         * \brief Adds new edge with given property to this graph.
         * \param edge the new edge
         * \param property the edge property
         * \return the created edge
         * \throw graph_partition_error if the edge connects vertices from the same group
         */
        edge_type add_edge(const edge_type & edge, const edge_property_type & property);

    private:
        bool are_in_same_group(const vertex_type & vertex1, const vertex_type & vertex2) const
        {
            return this->vertex_group_map.at(vertex1) == this->vertex_group_map.at(vertex2);
        }

        void validate_group(size_t group_number) const
        {
            if(group_number >= N)
                throw std::out_of_range(
                        "Invalid group number "s + std::to_string(group_number)
                        + ", graph contains only " + std::to_string(N) + " groups"s);
        }

        graph_t graph;
        std::unordered_map<vertex_type, size_t> vertex_group_map;
    };

    template <size_t N, typename VertexId, typename VertexProperty, typename EdgeProperty>
    std::vector<typename multipartite_graph<N, VertexId, VertexProperty, EdgeProperty>::vertex_type>
            multipartite_graph<N, VertexId, VertexProperty, EdgeProperty>::vertices_from_group(
                    size_t group_number) const
    {
        std::vector<vertex_type> result;
        std::vector<std::pair<vertex_type, size_t>> group_vertices;

        this->validate_group(group_number);

        std::copy(
                this->vertex_group_map.begin(), this->vertex_group_map.end(),
                std::back_inserter(group_vertices));
        group_vertices.erase(
                std::remove_if(
                        group_vertices.begin(), group_vertices.end(),
                        [&](auto && p) { return p.second != group_number; }),
                group_vertices.end());
        std::transform(
                group_vertices.begin(), group_vertices.end(), std::back_inserter(result),
                [](auto && p) { return p.first; });
        return result;
    }

    template <size_t N, typename VertexId, typename VertexProperty, typename EdgeProperty>
    typename multipartite_graph<N, VertexId, VertexProperty, EdgeProperty>::vertex_type
            multipartite_graph<N, VertexId, VertexProperty, EdgeProperty>::add_vertex(
                    size_t group_number,
                    const typename multipartite_graph<N, VertexId, VertexProperty, EdgeProperty>::
                            vertex_id_type & vertex_id)
    {
        return this->add_vertex(group_number, vertex_type(vertex_id));
    }

    template <size_t N, typename VertexId, typename VertexProperty, typename EdgeProperty>
    typename multipartite_graph<N, VertexId, VertexProperty, EdgeProperty>::vertex_type
            multipartite_graph<N, VertexId, VertexProperty, EdgeProperty>::add_vertex(
                    size_t group_number,
                    const typename multipartite_graph<N, VertexId, VertexProperty, EdgeProperty>::
                            vertex_id_type & vertex_id,
                    const typename multipartite_graph<N, VertexId, VertexProperty, EdgeProperty>::
                            vertex_property_type & property)
    {
        return this->add_vertex(group_number, vertex_type(vertex_id), property);
    }

    template <size_t N, typename VertexId, typename VertexProperty, typename EdgeProperty>
    typename multipartite_graph<N, VertexId, VertexProperty, EdgeProperty>::vertex_type
            multipartite_graph<N, VertexId, VertexProperty, EdgeProperty>::add_vertex(
                    size_t group_number,
                    const typename multipartite_graph<N, VertexId, VertexProperty, EdgeProperty>::
                            vertex_type & vertex)
    {
        this->validate_group(group_number);

        vertex_type new_vertex = this->graph.add_vertex(vertex);

        this->vertex_group_map.emplace(new_vertex, group_number);
        return new_vertex;
    }

    template <size_t N, typename VertexId, typename VertexProperty, typename EdgeProperty>
    typename multipartite_graph<N, VertexId, VertexProperty, EdgeProperty>::vertex_type
            multipartite_graph<N, VertexId, VertexProperty, EdgeProperty>::add_vertex(
                    size_t group_number,
                    const typename multipartite_graph<N, VertexId, VertexProperty, EdgeProperty>::
                            vertex_type & vertex,
                    const typename multipartite_graph<N, VertexId, VertexProperty, EdgeProperty>::
                            vertex_property_type & property)
    {
        this->validate_group(group_number);

        vertex_type new_vertex = this->graph.add_vertex(vertex, property);

        this->vertex_group_map.emplace(new_vertex, group_number);
        return new_vertex;
    }

    template <size_t N, typename VertexId, typename VertexProperty, typename EdgeProperty>
    typename multipartite_graph<N, VertexId, VertexProperty, EdgeProperty>::edge_type
            multipartite_graph<N, VertexId, VertexProperty, EdgeProperty>::add_edge_between(
                    const typename multipartite_graph<N, VertexId, VertexProperty, EdgeProperty>::
                            vertex_type & source,
                    const typename multipartite_graph<N, VertexId, VertexProperty, EdgeProperty>::
                            vertex_type & destination)
    {
        return this->add_edge(edge_type(source, destination));
    }

    template <size_t N, typename VertexId, typename VertexProperty, typename EdgeProperty>
    typename multipartite_graph<N, VertexId, VertexProperty, EdgeProperty>::edge_type
            multipartite_graph<N, VertexId, VertexProperty, EdgeProperty>::add_edge_between(
                    const typename multipartite_graph<N, VertexId, VertexProperty, EdgeProperty>::
                            vertex_type & source,
                    const typename multipartite_graph<N, VertexId, VertexProperty, EdgeProperty>::
                            vertex_type & destination,
                    const typename multipartite_graph<N, VertexId, VertexProperty, EdgeProperty>::
                            edge_property_type & property)
    {
        return this->add_edge(edge_type(source, destination), property);
    }

    template <size_t N, typename VertexId, typename VertexProperty, typename EdgeProperty>
    typename multipartite_graph<N, VertexId, VertexProperty, EdgeProperty>::edge_type
            multipartite_graph<N, VertexId, VertexProperty, EdgeProperty>::add_edge(
                    const typename multipartite_graph<N, VertexId, VertexProperty, EdgeProperty>::
                            edge_type & edge)
    {
        if(this->are_in_same_group(edge.source(), edge.destination()))
            throw graph_partition_error(
                    "Cannot create an edge between vertices in the same group"s);

        return this->graph.add_edge(edge);
    }

    template <size_t N, typename VertexId, typename VertexProperty, typename EdgeProperty>
    typename multipartite_graph<N, VertexId, VertexProperty, EdgeProperty>::edge_type
            multipartite_graph<N, VertexId, VertexProperty, EdgeProperty>::add_edge(
                    const typename multipartite_graph<N, VertexId, VertexProperty, EdgeProperty>::
                            edge_type & edge,
                    const typename multipartite_graph<N, VertexId, VertexProperty, EdgeProperty>::
                            edge_property_type & property)
    {
        if(this->are_in_same_group(edge.source(), edge.destination()))
            throw graph_partition_error(
                    "Cannot create an edge between vertices in the same group"s);

        return this->graph.add_edge(edge, property);
    }
}

#endif
