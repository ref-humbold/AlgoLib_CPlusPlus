/**!
 * \file shortest_paths.hpp
 * \brief Algorithms for shortest paths in a graph.
 */
#ifndef SHORTEST_PATHS_HPP_
#define SHORTEST_PATHS_HPP_

#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <exception>
#include <queue>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include "algolib/graphs/directed_graph.hpp"

namespace internal
{
    namespace algr = algolib::graphs;

    template <typename Argument>
    struct dijkstra_cmp
    {
        bool operator()(const Argument & pair1, const Argument & pair2) const
        {
            return pair2.first < pair1.first;
        }
    };
}

namespace algolib::graphs
{
    /*!
     * \brief Computes shortest paths in given directed graph from given vertex using Bellman-Ford algorithm.
     * \param graph the directed weighted graph
     * \param source the source vertex
     * \return the map of distances to each vertex
     */
    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    std::unordered_map<
            typename directed_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type,
            typename directed_graph<VertexId, VertexProperty, EdgeProperty>::edge_property_type::
                    weight_type>
            bellman_ford(
                    const directed_graph<VertexId, VertexProperty, EdgeProperty> & graph,
                    typename directed_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type
                            source)
    {
        std::unordered_map<
                typename directed_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type,
                typename directed_graph<
                        VertexId, VertexProperty, EdgeProperty>::edge_property_type::weight_type>
                distances;

        for(auto && v : graph.vertices())
            distances.emplace(
                    v,
                    directed_graph<
                            VertexId, VertexProperty, EdgeProperty>::edge_property_type::infinity);

        distances[source] = 0.0;

        for(size_t i = 0; i < graph.vertices_count() - 1; ++i)
            for(auto && vertex : graph.vertices())
                for(auto && edge : graph.adjacent_edges(vertex))
                    distances[edge.destination()] = std::min(
                            distances[edge.destination()],
                            distances[vertex] + graph.properties().at(edge).weight());

        for(auto && vertex : graph.vertices())
            for(auto && edge : graph.adjacent_edges(vertex))
                if(distances[vertex] < directed_graph<
                           VertexId, VertexProperty, EdgeProperty>::edge_property_type::infinity
                   && distances[vertex] + graph.properties().at(edge).weight()
                              < distances[edge.destination()])
                    throw std::logic_error("Graph contains a negative cycle");

        return distances;
    }

    /*!
     * \brief Computes shortest paths in given graph from given vertex using Dijkstra algorithm.
     * \param graph_ the weighted graph with non-negative weights
     * \param source the source vertex
     * \return the map of distances to each vertex
     */
    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    std::unordered_map<
            typename directed_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type,
            typename directed_graph<VertexId, VertexProperty, EdgeProperty>::edge_property_type::
                    weight_type>
            dijkstra(
                    const graph<VertexId, VertexProperty, EdgeProperty> & graph_,
                    typename graph<VertexId, VertexProperty, EdgeProperty>::vertex_type source)
    {
        using weight_t = typename directed_graph<
                VertexId, VertexProperty, EdgeProperty>::edge_property_type::weight_type;
        using pair_wv = std::pair<
                weight_t, typename graph<VertexId, VertexProperty, EdgeProperty>::vertex_type>;

        std::unordered_map<
                typename directed_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type,
                weight_t>
                distances;
        std::vector<typename directed_graph<VertexId, VertexProperty, EdgeProperty>::edge_type>
                edges = graph_.edges();

        if(std::any_of(
                   edges.begin(), edges.end(),
                   [&](auto && edge) { return graph_.properties().at(edge).weight() < 0.0; }))
            throw std::logic_error("Graph contains an edge with negative weight");

        std::unordered_set<
                typename directed_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type>
                visited;
        std::priority_queue<pair_wv, std::vector<pair_wv>, internal::dijkstra_cmp<pair_wv>>
                vertex_queue;

        for(auto && v : graph_.vertices())
            distances.emplace(
                    v,
                    directed_graph<
                            VertexId, VertexProperty, EdgeProperty>::edge_property_type::infinity);

        distances[source] = 0.0;
        vertex_queue.push(std::make_pair(0.0, source));

        while(!vertex_queue.empty())
        {
            auto vertex = vertex_queue.top().second;

            vertex_queue.pop();

            auto insert_result = visited.insert(vertex);

            if(insert_result.second)
                for(auto && edge : graph_.adjacent_edges(vertex))
                {
                    auto neighbour = edge.get_neighbour(vertex);
                    weight_t weight = graph_.properties().at(edge).weight();

                    if(distances[vertex] + weight < distances[neighbour])
                    {
                        distances[neighbour] = distances[vertex] + weight;
                        vertex_queue.push(std::make_pair(distances[neighbour], neighbour));
                    }
                }
        }

        return distances;
    }

    /*!
     * \brief Computes shortest paths in given directed graph between all vertices using Floyd-Warshall algorithm.
     * \param graph the directed weighted graph
     * \return the map of distances between each pair of vertices
     */
    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    std::unordered_map<
            std::pair<
                    typename directed_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type,
                    typename directed_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type>,
            double>
            floyd_warshall(const directed_graph<VertexId, VertexProperty, EdgeProperty> & graph)
    {
        std::unordered_map<
                std::pair<
                        typename directed_graph<
                                VertexId, VertexProperty, EdgeProperty>::vertex_type,
                        typename directed_graph<
                                VertexId, VertexProperty, EdgeProperty>::vertex_type>,
                double>
                distances;

        for(auto && v : graph.vertices())
            for(auto && u : graph.vertices())
                distances.emplace(
                        std::make_pair(v, u),
                        v == u ? 0.0
                               : directed_graph<VertexId, VertexProperty, EdgeProperty>::
                                        edge_property_type::infinity);

        for(auto && edge : graph.edges())
            distances[std::make_pair(edge.source(), edge.destination())] =
                    graph.properties().at(edge).weight();

        for(auto && w : graph.vertices())
            for(auto && v : graph.vertices())
                for(auto && u : graph.vertices())
                    distances[std::make_pair(v, u)] = std::min(
                            distances[std::make_pair(v, u)],
                            distances[std::make_pair(v, w)] + distances[std::make_pair(w, u)]);

        return distances;
    }
}

#endif
