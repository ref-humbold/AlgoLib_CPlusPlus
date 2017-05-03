// ALGORYTMY WYLICZANIA NAJKRÓTSZYCH ŚCIEŻEK W GRAFIE WAŻONYM
#include "paths.hpp"

std::vector<weight_type> algolib::graphs::bellman_ford(const directed_weighted_graph & wgraph,
                                                    vertex_type source)
{
    std::vector<weight_type> distances(wgraph.get_vertices_number(), directed_weighted_graph::INF);

    distances[source] = 0.0;

    for(size_t i = 0; i <= wgraph.get_vertices_number() - 1; ++i)
        for(const auto & we : wgraph.get_weighted_edges())
        {
            vertex_type v, u;
            weight_type wg;

            std::tie(v, u, wg) = we;
            distances[u] = std::min(distances[u], distances[v] + wg);
        }

    for(const auto & we : wgraph.get_weighted_edges())
    {
        vertex_type v, u;
        weight_type wg;

        std::tie(v, u, wg) = we;

        if(distances[v] < directed_weighted_graph::INF && distances[v] + wg < distances[u])
            throw std::runtime_error("Graph contains a negative cycle.");
    }

    return distances;
}

std::vector<weight_type> algolib::graphs::dijkstra(const weighted_graph & wgraph, vertex_type source)
{
    std::vector<weight_type> distances(wgraph.get_vertices_number(), simple_graph::INF);
    std::vector<bool> is_visited(wgraph.get_vertices_number(), false);
    std::priority_queue< std::pair<weight_type, vertex_type> > vertex_queue;

    distances[source] = 0.0;
    vertex_queue.push(std::make_pair(0.0, source));

    while(!vertex_queue.empty())
    {
        vertex_type v = vertex_queue.top().second;

        vertex_queue.pop();

        if(!is_visited[v])
        {
            is_visited[v] = true;

            for(const auto & e : wgraph.get_weighted_neighbours(v))
            {
                vertex_type nb;
                weight_type wg;

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

std::vector< std::vector<weight_type> > algolib::graphs::floyd_warshall(
    const directed_weighted_graph & wgraph)
{
    std::vector<std::vector<weight_type>> distances(wgraph.get_vertices_number(),
        std::vector<weight_type>(wgraph.get_vertices_number(), directed_weighted_graph::INF));

    for(const auto & we : wgraph.get_weighted_edges())
            distances[std::get<0>(we)][std::get<1>(we)] = std::get<2>(we);

    for(const auto & w : wgraph.get_vertices())
        for(const auto & v : wgraph.get_vertices())
            for(const auto & u : wgraph.get_vertices())
                distances[w][v] = std::min(distances[w][v], distances[w][u] + distances[u][v]);

    return distances;
}
