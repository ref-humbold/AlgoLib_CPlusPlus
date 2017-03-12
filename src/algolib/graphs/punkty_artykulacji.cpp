// WYSZUKIWANIE PUNKTÓW ARTYKULACJI W GRAFIE
#include <cstdlib>
#include <vector>
#include <algorithm>

#include "punkty_artykulacji.hpp"

std::vector<int> graph::find_vertex_separator()
{
    std::vector<int> separators;

    dfs_parents.resize(num_vertex+1);
    dfs_depths.resize(num_vertex+1, NODEPTH);
    low_values.resize(num_vertex+1);
    dfs_depths[0] = 0;

    for(int w = 1; w <= num_vertex; ++w)
        if(dfs_depths[w] == NO_DEPTH)
            dfs(w, 0);

    auto is_sepearator = [=](int vertex)
        {
            if(dfs_depths[vertex] == 1)
                return dfs_childs[vertex].size() > 1;

            for(int i = 0; i < dfs_childs[vertex].size(); ++i)
                if(low_values[ dfs_childs[vertex][i] ] >= dfs_depths[vertex])
                    return true;

            return false;
        };

    for(int w = 1; w <= num_vertex; ++w)
        if( is_separator(w) )
            separators.push_back(w);

    return separators;
}

void graph::dfs(int vertex, int parent)
{
    dfs_depths[vertex] = dfs_depths[parent]+1;
    low_values[vertex] = dfs_depths[vertex];

    for(int i = 0; i < graphrepr[vertex].size(); ++i)
    {
        int neighbour = graphrepr[vertex][i];

        if(dfs_depths[neighbour] == NO_DEPTH)
        {
            dfs_childs[vertex].push_back(neighbour);
            dfs(neighbour, vertex);
            low_values[vertex] = min(low_values[vertex], low_values[neighbour]);
        }
        else if(neighbour != parent)
            low_values[vertex] = min(low_values[vertex], dfs_depths[neighbour]);
    }
}

