/**
 * @file matching.cpp
 * ALGORYTM HOPCROFTA-KARPA WYZNACZANIA SKOJARZEŃ W GRAFIE DWUDZIELNYM
 */
#include "algolib/graphs/matching.hpp"

namespace algr = algolib::graphs;

constexpr int detail::match_augmenter::NO_MATCH;

std::vector<std::pair<int, int>> algr::match(const multipartite_graph<2> & partgraph)
{
    detail::match_augmenter augmenter(partgraph);

    while(augmenter.augment_match())
    {
    }

    std::vector<int> matching = augmenter.get_matching();
    std::vector<std::pair<int, int>> match_pairs;

    for(int v : partgraph.get_vertices(1))
        match_pairs.push_back(std::make_pair(v, matching[v]));

    return match_pairs;
}

bool detail::match_augmenter::augment_match()
{
    bool match_added = false;

    distances.resize(graph.get_vertices_number(), algolib::graphs::graph::INF);
    is_visited.resize(graph.get_vertices_number(), false);

    bfs();

    for(int v : graph.get_vertices(1))
        match_added = dfs(v) || match_added;

    return match_added;
}

void detail::match_augmenter::bfs()
{
    std::queue<int> vertex_queue;

    for(int v : graph.get_vertices(1))
    {
        distances[v] = 0.0;
        vertex_queue.push(v);
    }

    while(!vertex_queue.empty())
    {
        int v = vertex_queue.front();

        vertex_queue.pop();

        for(int nb : graph.get_neighbours(v))
            if(matching[nb] != NO_MATCH && distances[matching[nb]] == algolib::graphs::graph::INF)
            {
                distances[matching[nb]] = distances[v] + 1;
                vertex_queue.push(matching[nb]);
            }
    }
}

bool detail::match_augmenter::dfs(int vertex)
{
    is_visited[vertex] = true;

    for(int neighbour : graph.get_neighbours(vertex))
        if(matching[neighbour] == NO_MATCH)
        {
            matching[vertex] = neighbour;
            matching[neighbour] = vertex;

            return true;
        }
        else
        {
            int mtc = matching[neighbour];

            if(distances[mtc] == distances[vertex] + 1 && !is_visited[mtc] && dfs(mtc))
            {
                matching[vertex] = neighbour;
                matching[neighbour] = vertex;

                return true;
            }
        }

    return false;
}
