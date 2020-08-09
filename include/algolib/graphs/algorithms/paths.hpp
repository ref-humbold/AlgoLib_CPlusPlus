/**!
 * \file paths.hpp
 * \brief Algorithms for shortest paths in graph
 */
#ifndef PATHS_HPP_
#define PATHS_HPP_

#include <cstdlib>
#include <cmath>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include "algolib/graphs/directed_graph.hpp"

namespace internal
{
    namespace algr = algolib::graphs;

    template <typename P>
    struct dijkstra_cmp
    {
        bool operator()(const P & pair1, const P & pair2) const
        {
            return pair2.first < pair1.first;
        }
    };
}

namespace algolib::graphs
{
    /*!
     * \briefBellman-Ford algorithm.
     * \param graph a directed graph with weighted edges
     * \param source source vertex
     * \return map of vertices' distances
     */
    template <typename V, typename VP, typename EP>
    std::unordered_map<typename directed_graph<V, VP, EP>::vertex_type,
                       typename directed_graph<V, VP, EP>::edge_property_type::weight_type>
            bellman_ford(const directed_graph<V, VP, EP> & graph,
                         typename directed_graph<V, VP, EP>::vertex_type source)
    {
        std::unordered_map<typename directed_graph<V, VP, EP>::vertex_type,
                           typename directed_graph<V, VP, EP>::edge_property_type::weight_type>
                distances;

        for(auto && v : graph.vertices())
            distances.emplace(v, directed_graph<V, VP, EP>::edge_property_type::infinity);

        distances[source] = 0.0;

        for(size_t i = 0; i < graph.vertices_count() - 1; ++i)
            for(auto && vertex : graph.vertices())
                for(auto && edge : graph.adjacent_edges(vertex))
                    distances[edge.destination()] =
                            std::min(distances[edge.destination()],
                                     distances[vertex] + graph[edge].weight());

        for(auto && vertex : graph.vertices())
            for(auto && edge : graph.adjacent_edges(vertex))
                if(distances[vertex] < directed_graph<V, VP, EP>::edge_property_type::infinity
                   && distances[vertex] + graph[edge].weight() < distances[edge.destination()])
                    throw std::logic_error("Graph contains a negative cycle");

        return distances;
    }

    /*!
     * \brief Dijkstra algorithm.
     * \param graph_ a graph with weighted edges (weights are not negative)
     * \param source source vertex
     * \return map of vertices' distances
     */
    template <typename V, typename VP, typename EP>
    std::unordered_map<typename directed_graph<V, VP, EP>::vertex_type,
                       typename directed_graph<V, VP, EP>::edge_property_type::weight_type>
            dijkstra(const graph<V, VP, EP> & graph_, typename graph<V, VP, EP>::vertex_type source)
    {
        using weight_t = typename directed_graph<V, VP, EP>::edge_property_type::weight_type;
        using pair_wv = std::pair<weight_t, typename graph<V, VP, EP>::vertex_type>;

        std::unordered_map<typename directed_graph<V, VP, EP>::vertex_type, weight_t> distances;

        for(auto && edge : graph_.edges())
            if(graph_[edge].weight() < 0.0)
                throw std::logic_error("Graph contains an edge with negative weight");

        std::unordered_set<typename directed_graph<V, VP, EP>::vertex_type> visited;
        std::priority_queue<pair_wv, std::vector<pair_wv>, internal::dijkstra_cmp<pair_wv>>
                vertex_queue;

        for(auto && v : graph_.vertices())
            distances.emplace(v, directed_graph<V, VP, EP>::edge_property_type::infinity);

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
                    weight_t weight = graph_[edge].weight();

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
     * \brief Floyd-Warshall algorithm.
     * \param graph a directed graph with weighted edges
     * \return map of distances between all pairs of vertices
     */
    template <typename V, typename VP, typename EP>
    std::unordered_map<std::pair<typename directed_graph<V, VP, EP>::vertex_type,
                                 typename directed_graph<V, VP, EP>::vertex_type>,
                       double, typename directed_graph<V, VP, EP>::vertex_pair_hash>
            floyd_warshall(const directed_graph<V, VP, EP> & graph)
    {
        std::unordered_map<std::pair<typename directed_graph<V, VP, EP>::vertex_type,
                                     typename directed_graph<V, VP, EP>::vertex_type>,
                           double, typename directed_graph<V, VP, EP>::vertex_pair_hash>
                distances;

        for(auto && v : graph.vertices())
            for(auto && u : graph.vertices())
                distances.emplace(std::make_pair(v, u),
                                  v == u ? 0.0
                                         : directed_graph<V, VP, EP>::edge_property_type::infinity);

        for(auto && e : graph.edges())
            distances[std::make_pair(e.source(), e.destination())] = graph[e].weight();

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
