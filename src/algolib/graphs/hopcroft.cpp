// ALGORYTM HOPCROFTA-KARPA: SKOJARZENIA W GRAFIE DWUDZIELNYM
#include <cstdlib>
#include <cmath>
#include <vector>
#include <queue>

#include "hopcroft.hpp"

int bipartite_graph::match()
{
    int max_match_size = 0, match_added = 1;

    while(match_added > 0)
    {
        distances.clear();
        distances.resize(num_vertex+1, INF);
        is_visited.clear();
        is_visited.resize(num_vertex+1, false);
        bfs();
        match_added = augment_match();
        max_match_size += match_added;
    }

    return max_match_size;
}

void bipartite_graph::bfs()
{
    std::queue<int> vertex_queue;

    for(int w = 1; w <= num_vertex; ++w)
        if(is_first_set[w])
        {
            distances[w] = 0;
            vertex_queue.push(w);
        }

    while(!vertex_queue.empty())
    {
        int w = vertex_queue.front();

        vertex_queue.pop();

        for(int i = 0; i < graphrepr[w].size(); ++i)
        {
            int s = graphrepr[w][i];

            if(matchings[s] != NO_MATCH && distances[ matchings[s] ] == INF)
            {
                distances[ matchings[s] ] = distances[w]+1;
                vertex_queue.push(matchings[s]);
            }
        }
    }
}

int bipartite_graph::augment_match()
{
    int match_added = 0;

    for(int w = 1; w <= num_vertex; ++w)
        if( is_first_set[w] && dfs(w) )
            ++match_added;

    return match_added;
}

bool bipartite_graph::dfs(int vertex)
{
    is_visited[vertex] = true;

    for(int i = 0; i < graphrepr[vertex].size(); ++i)
    {
        int neighbour = graphrepr[vertex][i];

        if(matchings[neighbour] == NO_MATCH_)
        {
            matchings[vertex] = neighbour;
            matchings[neighbour] = vertex;

            return true;
        }
        else
        {
            int mtc = matchings[neighbour];

            if( distances[mtc] == distances[vertex]+1 && !is_visited[mtc] && dfs(mtc) )
            {
                matchings[vertex] = neighbour;
                matchings[neighbour] = vertex;

                return true;
            }
        }
    }

    return false;
}

