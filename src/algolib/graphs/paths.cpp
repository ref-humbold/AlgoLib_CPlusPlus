// ALGORYTMY WYLICZANIA NAJKRÓTSZYCH ŚCIEŻEK W GRAFIE WAŻONYM
#include "paths.hpp"

namespace details = algolib::detail;

std::vector<double> algolib::bellman_ford(const weighted_graph & wgraph, int source)
{
    std::vector<double> distances(wgraph.get_vertices_number(), details::INF);

    distances[source] = 0.0;

    for(size_t u = 1; u < wgraph.get_vertices_number()-1; ++u)
        for(const int & v : wgraph.get_vertices())
            for( const auto & e : wgraph.get_weighted_neighbours(v) )
            {
                int nb;
                double wg;

                std::tie(nb, wg) = e;
                distances[nb] = std::min(distances[nb], distances[v]+wg);
            }

    for(const int & v : wgraph.get_vertices())
        for( const auto & e : wgraph.get_weighted_neighbours(v) )
        {
            int nb;
            double wg;

            std::tie(nb, wg) = e;

            if(distances[v] < details::INF && distances[v]+wg < distances[nb])
                throw std::runtime_error("Graph contains a negative cycle.");
        }

    return distances;
}

std::vector<double> algolib::dijkstra(const weighted_graph & wgraph, int source)
{
    std::vector<double> distances(wgraph.get_vertices_number(), details::INF);
    std::vector<bool> is_visited(wgraph.get_vertices_number(), false);
    std::priority_queue< std::pair<double, int> > vertex_queue;

    distances[source] = 0.0;
    vertex_queue.push( std::make_pair(0.0, source) );

    while(!vertex_queue.empty())
    {
        int v = vertex_queue.top().second;

        vertex_queue.pop();

        if(!is_visited[v])
        {
            is_visited[v] = true;

            for( const auto & e : wgraph.get_weighted_neighbours(v) )
            {
                int nb;
                double wg;

                std::tie(nb, wg) = e;

                if(wg < 0)
                    throw std::runtime_error("Graph contains a negative weighted edge.");

                if(distances[v]+wg < distances[nb])
                {
                    distances[nb] = distances[v]+wg;
                    vertex_queue.push( std::make_pair(-distances[nb], nb) );
                }
            }
        }
    }

    return distances;
}

std::vector< std::vector<double> > algolib::floyd_warshall(const weighted_graph & wgraph)
{
    std::vector< std::vector<double> > distances = wgraph.get_adjacency_matrix();

    for(const int & w : wgraph.get_vertices())
        for(const int & v : wgraph.get_vertices())
            for(const int & u : wgraph.get_vertices())
                distances[w][v] = std::min(distances[w][v], distances[w][u]+distances[u][v]);

    return distances;
}
