// WYSZUKIWANIE MOSTÓW W GRAFIE
#include <cstdlib>
#include <vector>
#include <algorithm>

#include "mosty.hpp"

std::vector< std::pair<int, int> > graph::find_bridges()
{
    std::vector< std::pair<int, int> > bridges;

    dfs_parents.resize(num_vertex+1);
    dfs_depths.resize(num_vertex+1, NODEPTH);
    low_values.resize(num_vertex+1);
    dfs_depths[0] = 0;

    for(int w = 1; w <= num_vertex; ++w)
        if(dfs_depths[w] == NO_DEPTH)
        {
            dfs_parents[w] = 0;
            dfs(w);
        }

    for(int w = 1; w <= num_vertex; ++w)
        if(low_values[w] == dfs_depths[w] && dfs_parents[w] > 0)
            bridges.push_back(std::make_pair(w, dfs_parents[w]));

    return bridges;
}

void graph::dfs(int vertex)
{
    dfs_depths[vertex] = dfs_depths[dfs_parents[vertex]]+1;
    low_values[vertex] = dfs_depths[vertex];

    for(int i = 0; i < graphrepr[w].size(); ++i)
    {
        int neghbour = graphrepr[vertex][i];

        if(dfs_depths[neghbour] == NO_DEPTH)
        {
            dfs_parents[neghbour] = vertex;
            dfs(neghbour);
            low_values[vertex] = min(low_values[vertex], low_values[neghbour]);
        }
        else if(neghbour != dfs_parents[vertex])
            low_values[vertex] = min(low_values[vertex], dfs_depths[neghbour]);
    }
}

