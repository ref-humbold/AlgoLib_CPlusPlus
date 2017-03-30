// ALGORYTMY WYLICZANIA NAJKRÓTSZYCH ŚCIEŻEK W GRAFIE WAŻONYM
#include "paths.hpp"

std::vector<weight_t> algolib::graphs::bellman_ford(const weighted_graph & wgraph, vertex_t source)
{
    std::vector<weight_t> distances(wgraph.get_vertices_number(), weighted_graph::INF);

    distances[source] = 0.0;

    for(size_t u = 1; u < wgraph.get_vertices_number()-1; ++u)
        for(const auto & v : wgraph.get_vertices())
            for(const auto & e : wgraph.get_weighted_neighbours(v))
            {
                vertex_t nb;
                weight_t wg;

                std::tie(nb, wg) = e;
                distances[nb] = std::min(distances[nb], distances[v]+wg);
            }

    for(const auto & v : wgraph.get_vertices())
        for(const auto & e : wgraph.get_weighted_neighbours(v))
        {
            vertex_t nb;
            weight_t wg;

            std::tie(nb, wg) = e;

            if(distances[v] < weighted_graph::INF && distances[v]+wg < distances[nb])
                throw std::runtime_error("Graph contains a negative cycle.");
        }

    return distances;
}

std::vector<weight_t> algolib::graphs::dijkstra(const weighted_graph & wgraph, vertex_t source)
{
    std::vector<weight_t> distances(wgraph.get_vertices_number(), weighted_graph::INF);
    std::vector<bool> is_visited(wgraph.get_vertices_number(), false);
    std::priority_queue< std::pair<weight_t, vertex_t> > vertex_queue;

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

                if(distances[v]+wg < distances[nb])
                {
                    distances[nb] = distances[v]+wg;
                    vertex_queue.push(std::make_pair(-distances[nb], nb));
                }
            }
        }
    }

    return distances;
}

std::vector< std::vector<weight_t> > algolib::graphs::floyd_warshall(const weighted_graph & wgraph)
{
    std::vector< std::vector<weight_t> > distances = wgraph.get_adjacency_matrix();

    for(const vertex_t & w : wgraph.get_vertices())
        for(const vertex_t & v : wgraph.get_vertices())
            for(const vertex_t & u : wgraph.get_vertices())
                distances[w][v] = std::min(distances[w][v], distances[w][u]+distances[u][v]);

    return distances;
}
