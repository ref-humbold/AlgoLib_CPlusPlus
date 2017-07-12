// ALGORYTMY WYLICZANIA NAJKRÓTSZYCH ŚCIEŻEK W GRAFIE WAŻONYM
#include "paths.hpp"

namespace algr = algolib::graphs;

std::vector<weight_t> algr::bellman_ford(const directed_weighted_graph & diwgraph, vertex_t source)
{
    std::vector<weight_t> distances(diwgraph.get_vertices_number(),
                                    directed_weighted_simple_graph::INF);

    distances[source] = 0.0;

    for(size_t i = 0; i <= diwgraph.get_vertices_number() - 1; ++i)
        for(const auto & we : diwgraph.get_weighted_edges())
        {
            vertex_t v, u;
            weight_t wg;

            std::tie(v, u, wg) = we;
            distances[u] = std::min(distances[u], distances[v] + wg);
        }

    for(const auto & we : diwgraph.get_weighted_edges())
    {
        vertex_t v, u;
        weight_t wg;

        std::tie(v, u, wg) = we;

        if(distances[v] < directed_weighted_simple_graph::INF && distances[v] + wg < distances[u])
            throw std::runtime_error("Graph contains a negative cycle.");
    }

    return distances;
}

std::vector<weight_t> algr::dijkstra(const weighted_graph & wgraph, vertex_t source)
{
    std::vector<weight_t> distances(wgraph.get_vertices_number(), simple_graph::INF);
    std::vector<bool> is_visited(wgraph.get_vertices_number(), false);
    std::priority_queue<std::pair<weight_t, vertex_t>> vertex_queue;

    distances[source] = 0.0;
    vertex_queue.push(std::make_pair(0.0, source));

    while(!vertex_queue.empty())
    {
        vertex_t v = vertex_queue.top().second;

        vertex_queue.pop();

        if(!is_visited[v])
        {
            is_visited[v] = true;

            for(const auto & e : wgraph.get_weighted_neighbours(v))
            {
                vertex_t nb;
                weight_t wg;

                std::tie(nb, wg) = e;

                if(wg < 0)
                    throw std::runtime_error("Graph contains a negative weighted edge.");

                if(distances[v] + wg < distances[nb])
                {
                    distances[nb] = distances[v] + wg;
                    vertex_queue.push(std::make_pair(-distances[nb], nb));
                }
            }
        }
    }

    return distances;
}

std::vector<std::vector<weight_t>> algr::floyd_warshall(const directed_weighted_graph & diwgraph)
{
    std::vector<std::vector<weight_t>> distances(
        diwgraph.get_vertices_number(),
        std::vector<weight_t>(diwgraph.get_vertices_number(), directed_weighted_simple_graph::INF));

    for(const auto & we : diwgraph.get_weighted_edges())
        distances[std::get<0>(we)][std::get<1>(we)] = std::get<2>(we);

    for(const auto & w : diwgraph.get_vertices())
        for(const auto & v : diwgraph.get_vertices())
            for(const auto & u : diwgraph.get_vertices())
                distances[w][v] = std::min(distances[w][v], distances[w][u] + distances[u][v]);

    return distances;
}
